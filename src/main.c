// 3dcam
// With huge help from :
// @NicolasNoble : https://discord.com/channels/642647820683444236/646765703143227394/796876392670429204
// @Lameguy64
// @Impiaa
// @paul        
 /*        PSX screen coordinate system 
 *
 *                           Z+
 *                          /
 *                         /
 *                        +------X+
 *                       /|
 *                      / |
 *                     /  Y+
 *                   eye        */
// Blender debug mode
// bpy. app. debug = True 
#include <psx.h>
#include <pad.h>
#include <math.h>
#include <camera.h>
#include <physics.h>
#include <graphics.h>
#include <space.h>
#include <sound.h>
//~ #include "../thirdparty/nugget/common/syscalls/syscalls.h"
//~ #define printf ramsyscall_printf
#define USECD

// START OVERLAY
extern u_long load_all_overlays_here;
extern u_long __lvl0_end;
extern u_long __lvl1_end;
extern u_long __lvl2_end;

u_long overlaySize = 0;

#include "../levels/level0.h"
#include "../levels/level1.h"
#include "../levels/level2.h"

// Levels
u_char level = 2;
u_short levelWas = 2;
u_short levelHasChanged = 0;

u_short MAX_LEVELS = 2; // Number of levels

// Overlay
static char* overlayFile;
// Display and draw environments, double buffered
DISPENV disp[2];
DRAWENV draw[2];
//~ // OT for BG/FG discrimination
u_long otdisc[2][OT2LEN] = {0};
// Main OT
u_long      ot[2][OTLEN]  = {0};                // Ordering table (contains addresses to primitives)
char    primbuff[2][PRIMBUFFLEN] = {0};         // Primitive list // That's our prim buffer
int         primcnt=0;                      // Primitive counter
char * nextpri = primbuff[0];                   // Primitive counter
char            db  = 0;                        // Current buffer counter
// Lighting
CVECTOR BGc = {128, 128, 128, 0};               // Default Far color - This can be set in each level.
VECTOR BKc = {128, 128, 128, 0};                // Back color   
VECTOR FC = FOG_COLOR;                     // Far (Fog) color   
SVECTOR lgtang = {0, 0, 0};
MATRIX rotlgt, light;
short vs;
CAMERA camera = {0};
// Physics
u_long time = 0;
u_long timeS = 0;
//Pads
Controller_Buffer controllers[2];   // Buffers for reading controllers
Controller_Data theControllers[8];  // Processed controller data
int pressed = 0;
u_short timer = 0;
// Cam stuff 
int camMode = ACTOR;                // Cam mode, see defines.h, l.6
VECTOR angle     = {250,0,0,0};
VECTOR angleCam  = {0,0,0,0};
VECTOR posToActor    = {0, 0, 0, 0};      // position of camera relative to actor    
VECTOR * camAngleToAct;      // rotation angles for the camera to point at actor
int dist      = 150; 
int lerping    = 0;
short curCamAngle = 0;
// Actor's forward vector (used for dualshock)
VECTOR fVecActor;
u_long triCount = 0;
LEVEL curLvl;
LEVEL * loadLvl;
// Actor start position
VECTOR actorStartPos = {0};
VECTOR actorStartRot = {0};
NODE * actorStartNode;
// Prop start position
VECTOR propStartPos = {0};
VECTOR propStartRot = {0};
NODE * propStartNode;
// Callback function is used for pads
void callback();
// variable FPS 
long oldTime = 0;
long dt = 0;
// Physics/collisions
short physics = 1;
VECTOR col = {0};
// Animation timing
// time % timediv == animation time
// Time divisor
short timediv = 1;
// Animation time, see l.206
int atime = 0;
// Sound
// VAG playback
// Memory management table ; allow MALLOC_MAX calls to SpuMalloc() - libref47.pdf p.1044
char spu_malloc_rec[SPU_MALLOC_RECSIZ * (2 + MALLOC_MAX + 1)]; 
// SPU settings
SpuCommonAttr spuSettings;          // structure for changing common voice attributes
SpuVoiceAttr  voiceAttributes ;          // structure for changing individual voice attributes
// Keep track of XA Sample currently playing
int sample = -1;

int main() {
    // Set matrices pointers to scratchpad 
    camera.mat = dc_camMat;
    camera.pos = dc_camPos;
    camera.rot = dc_camRot;
    camAngleToAct = dc_actorRot;
    // Load level file according to level, l.39
    if ( level == 0 ){
        overlayFile = "\\level0.bin;1";
        overlaySize = __lvl0_end;
        loadLvl     = &level0;
    } else if ( level == 1) {
        overlayFile = "\\level1.bin;1";
        overlaySize = __lvl1_end;
        //~ loadLvl     = &level1;
    } else if (level == 2) {
        overlayFile = "\\level2.bin;1";
        overlaySize = __lvl2_end;
    }
    // Load overlay from cd
    #ifdef USECD
        CdInit();
        // Load level
        LoadLevelCD(overlayFile, &load_all_overlays_here);
    #endif
    // TODO : Add switch case to get the correct pointers
    // Get needed pointers from level file
    if ( level == 0 ) {
        LvlPtrSet( &curLvl, &level0);
    } else if ( level == 1) {
        LvlPtrSet( &curLvl, &level1);
    } else if ( level == 2) {
        LvlPtrSet( &curLvl, &level2);
    }
    levelWas = level;
    // Copy light matrices / vector to scratchpad
    setDCLightEnv(curLvl.cmat, curLvl.lgtmat, &lgtang);
    // Init dislay, Gte..
    init(disp, draw, db, curLvl.BGc, curLvl.BKc, &FC);
    // Init Pads
    InitPAD(controllers[0].pad, 34, controllers[1].pad, 34);
    StartPAD();
    // Generate Cos table
    generateTable();
    // Set function 'callback' on v-sync
    VSyncCallback(callback);
    // Load textures
    for (int k = 0; k < *curLvl.meshes_length ; k++){
        // Check data exists
        if (curLvl.meshes[k]->tim_data){
            LoadTexture(curLvl.meshes[k]->tim_data, curLvl.meshes[k]->tim);
        }
    }
    // Load current BG if exists, and set cam mode accordingly
    if (curLvl.camPtr->tim_data){
        // Switch to proper cam mode and angle
        camMode = FIXED;
        curCamAngle = 1;
        LoadTexture(curLvl.camPtr->tim_data, curLvl.camPtr->BGtim);
    }
    // Polycount
    for (int k = 0; k < *curLvl.meshes_length; k++){
            triCount += curLvl.meshes[k]->tmesh->len;
    }
    // Save actor starting pos
    copyVector(&actorStartPos, &curLvl.actorPtr->body->position);
    copyVector(&actorStartRot, &curLvl.actorPtr->rot);
    actorStartNode = curLvl.curNode;
    // Save prop starting pos
    copyVector(&propStartPos, &curLvl.propPtr->body->position);
    copyVector(&propStartRot, &curLvl.propPtr->rot);
    propStartNode = curLvl.propPtr->node;
    // Set camera starting pos
    setCameraPos(&camera, &curLvl.camPtr->campos->pos, &curLvl.camPtr->campos->rot);
    // Time counter
    oldTime = GetRCnt(RCntCNT1);
    // Sound
    SpuInit();    
    // Load level's VAGs to SPU
    setLvlVAG(&curLvl, &spuSettings, &voiceAttributes, spu_malloc_rec);
    // Set XA sample
    sample = 0;
    setLvlXA(&curLvl, sample);
    // Main loop
    //~ while ( VSync(VSYNC) ) {
    while ( 1 ) {
        printf("Let's go!");
        dt = GetRCnt(RCntCNT1) - oldTime;
        oldTime = GetRCnt(RCntCNT1);
        // XA playback (keep track of playback and loop XA)
        XAplayback(&curLvl, sample, dt);
        // Check if level has changed
        // TODO : Proper level system / loader
        if ( levelWas != level ){
            // If so, load other level
            switch ( level ){
                case 0:
                    overlayFile = "\\level0.bin;1";
                    overlaySize = __lvl0_end;
                    loadLvl     = &level0;
                    // Copy light matrices / vector to scratchpad
                    break;
                case 1:
                    overlayFile = "\\level1.bin;1";
                    overlaySize = __lvl1_end;
                    //~ loadLvl     = &level1;
                    // Copy light matrices / vector to scratchpad
                    break;
                case 2:
                    overlayFile = "\\level2.bin;1";
                    overlaySize = __lvl2_end;
                    break;
                default:
                    overlayFile = "\\level0.bin;1";
                    loadLvl     = &level0;
                    break;
            }
            #ifdef USECD
              LoadLevelCD( overlayFile, &load_all_overlays_here );
            #endif
            SwitchLevel( &curLvl, loadLvl);
            // Save actor starting pos
            copyVector(&actorStartPos, &curLvl.actorPtr->body->position);
            copyVector(&actorStartRot, &curLvl.actorPtr->rot);
            actorStartNode = curLvl.curNode;
            // Save prop starting pos
            copyVector(&propStartPos, &curLvl.propPtr->body->position);
            copyVector(&propStartRot, &curLvl.propPtr->rot);
            propStartNode = curLvl.propPtr->node;
            // Set level lighting
            setLightEnv(draw, curLvl.BGc, curLvl.BKc);
            levelWas = level;
            // Load level's VAGs to SPU
            setLvlVAG(&curLvl, &spuSettings, &voiceAttributes, spu_malloc_rec);
            // Set 
            setLvlXA(&curLvl, sample);
        }
        //~ FntPrint("Ovl:%s\nLvl : %x\nLvl: %d %d \n%x", overlayFile, &level, level, levelWas, loadLvl);
        // atime is used for animations timing
        timediv = 2;
        // If timediv is > 1, animation time will be slower 
        if (time++ % timediv == 0){
            atime ++;
        }
        // Reset player/prop pos
        if(curLvl.actorPtr->pos.vy >= curLvl.levelPtr->body->max.vy + 200){
            playSFX(&voiceAttributes,  curLvl.levelSounds->sounds[6]->VAGsample, curLvl.levelSounds->sounds[6]->volumeL, curLvl.levelSounds->sounds[6]->volumeR);
            respawnMesh(&curLvl, curLvl.actorPtr, &actorStartRot, &actorStartPos, actorStartNode );
        }        
        if(curLvl.propPtr->pos.vy >= curLvl.levelPtr->body->max.vy + 200){
            playSFX(&voiceAttributes,  curLvl.levelSounds->sounds[3]->VAGsample, curLvl.levelSounds->sounds[3]->volumeL, curLvl.levelSounds->sounds[3]->volumeR);
            respawnMesh(&curLvl, curLvl.propPtr, &propStartRot, &propStartPos, propStartNode );
        }
    // Spatialize Sound 
    setSFXdist(&curLvl, &camera, camMode);
    // Spatial partitioning
        if (curLvl.curNode){
            for ( int msh = 0; msh < curLvl.curNode->siblings->index; msh ++ ) {
                // Set Actor node
                // If actor is out of plane's X,Z coordinates...
                if ( !getIntCollision( *curLvl.actorPtr->body , *curLvl.curNode->siblings->list[msh]->plane->body).vx &&
                     !getIntCollision( *curLvl.actorPtr->body , *curLvl.curNode->siblings->list[msh]->plane->body).vz )
                {
                    // if current node is not already pointing to a sibling 
                    if ( curLvl.curNode != curLvl.curNode->siblings->list[msh] ) {
                        // make it point to siblings
                        curLvl.curNode = curLvl.curNode->siblings->list[msh];
                        // set current plane
                        curLvl.levelPtr = curLvl.curNode->plane;
                    }
                }
                // Set Prop node
                if ( !getIntCollision( *curLvl.propPtr->body , *curLvl.curNode->plane->body).vx &&
                     !getIntCollision( *curLvl.propPtr->body , *curLvl.curNode->plane->body).vz ) {
                    curLvl.propPtr->node = curLvl.curNode;
                }
            }
        }
    // Physics
        if ( physics ) {
             u_char canMove = 1;
             for ( int k = 0; k < *curLvl.meshes_length; k ++ ) {
                 if ( curLvl.meshes[k]->isRigidBody == 1 ) {
                    applyAcceleration( curLvl.meshes[k]->body, dt);
                     // Get col between props and level
                    if ( curLvl.meshes[k]->isProp ){
                        checkBodyCol( curLvl.meshes[k]->body , curLvl.meshes[k]->node->plane->body );
                        for (short obj=0; obj < curLvl.curNode->objects->index; obj++){
                            // If isWall, check collision
                            if ( curLvl.curNode->objects->list[obj]->isWall ){
                                if( getExtCollision( *curLvl.meshes[k]->body, *curLvl.curNode->objects->list[obj]->body ).vz &&
                                    getExtCollision( *curLvl.meshes[k]->body, *curLvl.curNode->objects->list[obj]->body ).vx) {
                                    curLvl.meshes[k]->body->position.vz = curLvl.meshes[k]->body->position.vz - curLvl.meshes[k]->body->velocity.vz ;
                                    curLvl.meshes[k]->body->position.vx = curLvl.meshes[k]->body->position.vx - curLvl.meshes[k]->body->velocity.vx ;
                                    canMove = 0;
                                }
                            }
                        }
                    }
                    // Get col between actor and level
                    if ( curLvl.meshes[k]->isActor ){
                        // Check col
                        VECTOR colLvl = checkBodyCol( curLvl.meshes[k]->body , curLvl.levelPtr->body );
                        FntPrint("ColLvl: %d %d %d\n", colLvl.vz, colLvl.vx, colLvl.vy);  
                        // Get col between actor and current node's walls
                        // Loop on current node's objects
                        for (short obj=0; obj < curLvl.curNode->objects->index; obj++){
                            VECTOR col = getExtCollision( *curLvl.meshes[k]->body, *curLvl.curNode->objects->list[obj]->body );
                            // If isWall, check collision
                            //~ if ( curLvl.curNode->objects->list[obj]->isWall){
                                //~ if( col.vz && col.vx) {
                                    //~ curLvl.meshes[k]->body->position.vz = curLvl.meshes[k]->body->position.vz - curLvl.meshes[k]->body->velocity.vz ;
                                    //~ curLvl.meshes[k]->body->position.vx = curLvl.meshes[k]->body->position.vx - curLvl.meshes[k]->body->velocity.vx ;
                                //~ }
                            //~ }
                            if ( curLvl.curNode->objects->list[obj]->isStaticBody ){
                                FntPrint("Col   : %d %d %d\n", col.vz, col.vx, col.vy);  
                                if( col.vz && col.vx && col.vy ) {
                                    if (!colLvl.vy) {
                                        curLvl.meshes[k]->body->position.vz = curLvl.meshes[k]->body->position.vz - curLvl.meshes[k]->body->velocity.vz ;
                                        curLvl.meshes[k]->body->position.vx = curLvl.meshes[k]->body->position.vx - curLvl.meshes[k]->body->velocity.vx ;
                                    }
                                    curLvl.meshes[k]->body->position.vy = curLvl.meshes[k]->body->position.vy - curLvl.meshes[k]->body->velocity.vy ;
                                }
                            }                            
                        }
                    }
                   
                    // Only evaluate collision if actor is on same plane as prop
                    if ( curLvl.curNode == curLvl.propPtr->node ){
                        // Get col between actor and props
                        VECTOR col = getExtCollision( *curLvl.meshes[k]->body, *curLvl.propPtr->body );
                        if (col.vx && col.vz && col.vy && canMove == 1 ) {
                            setVector( &curLvl.propPtr->body->velocity,
                                       curLvl.meshes[k]->body->velocity.vx,
                                       0,
                                       curLvl.meshes[k]->body->velocity.vz
                                      );
                            // If prop is spherical, make it roll
                            applyAngMom(curLvl);
                        }
                        
                    }
                    // Synchronize mesh to body position
                    copyVector(&curLvl.meshes[k]->pos, &curLvl.meshes[k]->body->position);
                }
                setVector(&curLvl.meshes[k]->body->velocity, 0, 0, 0);
            }
        }

    // Clear the main OT
        ClearOTagR(otdisc[db], OT2LEN);
    // Clear Secondary OT
        ClearOTagR(ot[db], OTLEN);
    // Set camera according to mode
        setCameraMode(&curLvl, &camera, &posToActor, &angle, &angleCam, &curCamAngle, camMode, &lerping);
    // Render scene
        renderScene(&curLvl, &camera, &camMode, &nextpri, ot[db], otdisc[db], &db, &draw[db], curCamAngle, atime);
    // Set camera
        // Get position of cam relative to actor
        addVector2(&curLvl.actorPtr->pos, camera.pos, &posToActor);
        // Angle between camera and actor
        applyVector( dc_actorRot,
                     (patan(dist, posToActor.vy) >> 4 ) - 256,
                     (patan(-posToActor.vx, -posToActor.vz) / 16) + 1024,
                     0,
                     =
                   );
        // Point camera at actor unless camMode == FIXED
        if (camMode != FIXED){ copyVector(dc_camRot, dc_actorRot); }
        // 
        applyCamera(&camera);
        
    // Find Actor's forward vector
        setVector(  &fVecActor,
                    curLvl.actorPtr->pos.vx + (nsin(curLvl.actorPtr->rot.vy/2)),
                    curLvl.actorPtr->pos.vy, 
                    curLvl.actorPtr->pos.vz - (ncos(curLvl.actorPtr->rot.vy/2))
                );
        curLvl.levelPtr->body->normal = curLvl.levelPtr->tmesh->n[0];
        
    // Add secondary OT to main OT
        AddPrims(otdisc[db], ot[db] + OTLEN - 1, ot[db]);
        
        FntPrint("\n#Tri     : %d\n", triCount);
        FntPrint("#RCnt    : %d %d\n", VSync(-1), dt);
        //~ FntPrint("Dt    : %d %d %d\n", 400/(dt+1), (XA_CDSPEED)/((400/(dt+1))+1), (curLvl.XA->samples[sample].end - curLvl.XA->samples[sample].start)<<12);
        //~ FntPrint("XA    : %d\n", (XA_CDSPEED)/((400/(dt+1))+1) );
        //~ FntPrint("XA    : %d\n", curLvl.XA->samples[sample].cursor );
        FntPrint("CamAngle : %d\n", curCamAngle );
        FntPrint("fVector : %d %d %d\n", fVecActor.vx, fVecActor.vy, fVecActor.vz );
        //~ FntPrint("XA: %x\n", curLvl.XA);
        //~ FntPrint("Ofst: %d\n", curLvl.XA->banks[0]->offset);
        //~ FntPrint("Vol: %d %d\n", curLvl.levelSounds->sounds[0]->volumeL, curLvl.levelSounds->sounds[0]->volumeR );
        FntPrint("Curanim : %x\n", curLvl.meshes[1]->currentAnim);
        FntPrint("Gforce: %d", curLvl.actorPtr->body->gForce.vy);
        //~ FntPrint("Anims : %x %x", curLvl.meshes[1]->anim_tracks->strips[3], curLvl.meshes[1]->anim_tracks->strips[4]);
        FntFlush(-1);
        display( &disp[db], &draw[db], otdisc[db], primbuff[db], &nextpri, &db);
      
    }
    return 0;
}
void callback() {
    // Pad 1
    read_controller( &theControllers[0], &controllers[0].pad[0], 0 );  // Read controllers
    // Pad 2
    read_controller( &theControllers[1], &controllers[1].pad[0], 1 );
    
    u_short PAD = ~*((u_short*)(&theControllers[0].button1));

    static u_short lastPad;
    static int lerpValues[4096 >> 7];
    static short cursor = 0;
    static short angleCamTimer = 0;
    //~ static short forceApplied = 0;
    int div = 32;

    if( !lerpValues[0] ) {
        for ( long long i = 0; i < div ; i++ ){
            lerpValues[(div-1)-i] = lerp(-24, -264, easeIn(i));
        }
    }
    if( timer ) {
        timer--;
    }    
    if (!timer){
        curLvl.actorPtr->body->gForce.vy = 0;
    }
    if( cursor ) {
        cursor--;
    }
    if (angleCam.vy > 2048 || angleCam.vy < -2048) {
        angleCam.vy = 0;
    }
    if ( PAD & PadShldR1 && !(lastPad & PadShldR1) ) {
        // Change camera angle switching mode if using pre-calculated BGs
        if (!curLvl.camPtr->tim_data){
            if(camMode < 5){ 
                    camMode ++;
                    lerping = 0;
            } else {
                setCameraPos(&camera, &curLvl.camPtr->campos->pos, &curLvl.camPtr->campos->rot);
                curLvl.camPath->cursor = 0;
                camMode = 0;
                lerping = 0;
            }
        } else {
            if (curCamAngle > 4) {
                curCamAngle = 0;
            }
            if (curCamAngle < 5) {
                curCamAngle++;
                curLvl.camPtr = curLvl.camAngles[ curCamAngle ];
                LoadTexture(curLvl.camPtr->tim_data, curLvl.camPtr->BGtim);
            } 
        }
        lastPad = PAD;
    }
    if ( !(PAD & PadShldR1) && lastPad & PadShldR1 ) {
        lastPad = PAD;
    }
    if ( PAD & PadShldL2 ) {
        dc_lgtangp->vy += 32;
    }
    if ( PAD & PadShldL1 ) {
        dc_lgtangp->vz += 32;
    }
    if ( PAD & Triangle && !( lastPad & Triangle ) ){
        if (curLvl.actorPtr->isPrism){
            curLvl.actorPtr->isPrism = 0;
        } else {
            curLvl.actorPtr->isPrism = 1;
        }
        playSFX(&voiceAttributes,  curLvl.levelSounds->sounds[0]->VAGsample, curLvl.levelSounds->sounds[0]->volumeL, curLvl.levelSounds->sounds[0]->volumeR );
        //~ timer = 10;
        lastPad = PAD;
    }
    if ( !(PAD & Triangle) && lastPad & Triangle ) {
        lastPad = PAD;
    }
    if ( PAD & Square && !( lastPad & Square ) ){
        playSFX(&voiceAttributes,  curLvl.levelSounds->sounds[7]->VAGsample, curLvl.levelSounds->sounds[7]->volumeL, curLvl.levelSounds->sounds[7]->volumeR);
        if ( curLvl.meshes[1]->currentAnim == 0 ||
             curLvl.meshes[1]->currentAnim == curLvl.meshes[1]->anim_tracks->strips[0]
            ){
            if (curLvl.meshes[1]->anim_tracks->index > 1) {
                curLvl.meshes[1]->currentAnim = curLvl.meshes[1]->anim_tracks->strips[4];
            }
        } else {
            //~ curLvl.meshes[1]->anim_tracks->strips[0]->interpolate = 1;
            curLvl.meshes[1]->currentAnim = curLvl.meshes[1]->anim_tracks->strips[0];
        }
        //~ sample = 0;
        //~ setXAsample(&XABank.samples[sample], &filter);
        lastPad = PAD;
    }
    if ( !(PAD & Square) && lastPad & Square ) {
        lastPad = PAD;
    }
    if ( PAD & Cross && !(lastPad & Cross) ){
        //~ if (curLvl.actorPtr->body->gForce.vy == 0 && (curLvl.actorPtr->body->position.vy - curLvl.actorPtr->body->min.vy) == curLvl.levelPtr->body->min.vy ){
        if (curLvl.actorPtr->body->gForce.vy == 0){
            // Use delta to find jump force
            curLvl.actorPtr->body->gForce.vy = -300;
        }
        timer = 10;
        playSFX(&voiceAttributes,  curLvl.levelSounds->sounds[4]->VAGsample, curLvl.levelSounds->sounds[4]->volumeL, curLvl.levelSounds->sounds[4]->volumeR );
        lastPad = PAD;
    }
    if ( !(PAD & Cross) && lastPad & Cross ) {
        lastPad = PAD;
    }
    if ( PAD & Circle && !(PAD & lastPad) ){
        playSFX(&voiceAttributes,  curLvl.levelSounds->sounds[5]->VAGsample, curLvl.levelSounds->sounds[5]->volumeL, curLvl.levelSounds->sounds[5]->volumeR );
        lastPad = PAD;
    }
    if ( !(PAD & Circle) && lastPad & Circle ) {
        lastPad = PAD;
    }
    //~ if ( PAD & PadLeft && !(lastPad & PadLeft) ) {

        //~ lastPad = PAD;
    //~ }
    //~ if ( !(PAD & PadLeft) && lastPad & PadLeft ) {
        //~ lastPad = PAD;
    //~ }
    if (theControllers[0].type == 0x73){
        // Analog stick L up
        if ( theControllers[0].analog3 >= 0 && theControllers[0].analog3 < (128 - DS_DZ/2)) {
            curLvl.actorPtr->body->gForce.vz = getVectorTo(fVecActor, curLvl.actorPtr->pos).vz *  (128 - theControllers[0].analog3 ) >> 13 ;
            curLvl.actorPtr->body->gForce.vx = -getVectorTo(fVecActor, curLvl.actorPtr->pos).vx * (128 - theControllers[0].analog3 ) >> 13 ;
        }
        // Analog stick L down
        if ( theControllers[0].analog3 > (128 + DS_DZ/2) && theControllers[0].analog3 <= 255 ) {
            curLvl.actorPtr->body->gForce.vz = -getVectorTo(fVecActor, curLvl.actorPtr->pos).vz *  ( theControllers[0].analog3 - 128 ) >> 13 ;
            curLvl.actorPtr->body->gForce.vx = getVectorTo(fVecActor, curLvl.actorPtr->pos).vx * ( theControllers[0].analog3 - 128 ) >> 13 ;
        }
        // Analog stick L dead zone
        if ( theControllers[0].analog3 > (128 - DS_DZ/2) && theControllers[0].analog3 < (128 + DS_DZ/2) ) {
            curLvl.actorPtr->body->gForce.vz = 0;
            curLvl.actorPtr->body->gForce.vx = 0;
        }
        // Analog stick L left
        if ( theControllers[0].analog2 >= 0 && theControllers[0].analog2 < (128 - DS_DZ/2) ) {
            curLvl.actorPtr->rot.vy -= ( 64 * ( 128 - theControllers[0].analog2 ) ) >> 8 ;
        }
        // Analog stick L right
        if ( theControllers[0].analog2 > (128 + DS_DZ/2) && theControllers[0].analog2 <= 255 ) {
            curLvl.actorPtr->rot.vy += ( 64 * ( theControllers[0].analog2 - 128 ) ) >> 8 ;
        }
    }
    if ( PAD & PadUp ) {
        curLvl.actorPtr->body->gForce.vz = getVectorTo(fVecActor, curLvl.actorPtr->pos).vz >> 6 ;
        curLvl.actorPtr->body->gForce.vx = -getVectorTo(fVecActor, curLvl.actorPtr->pos).vx >> 6;
        lastPad = PAD;
    }
    if ( !(PAD & PadUp) && lastPad & PadUp) {
        curLvl.actorPtr->body->gForce.vz = 0;
        curLvl.actorPtr->body->gForce.vx = 0;
        lastPad = PAD;
    }
    if ( PAD & PadDown ) {
        curLvl.actorPtr->body->gForce.vz = -getVectorTo(fVecActor, curLvl.actorPtr->pos).vz >> 6 ;
        curLvl.actorPtr->body->gForce.vx = getVectorTo(fVecActor, curLvl.actorPtr->pos).vx >> 6 ;
        lastPad = PAD;
    }
    if ( !( PAD & PadDown ) && lastPad & PadDown) {
        curLvl.actorPtr->body->gForce.vz = 0;
        curLvl.actorPtr->body->gForce.vx = 0;
        lastPad = PAD;
    }
    if ( PAD & PadLeft ) {
        curLvl.actorPtr->rot.vy -= 64;
        lastPad = PAD;
    }
    if ( PAD & PadRight ) {
        curLvl.actorPtr->rot.vy += 64;
        lastPad = PAD;
    }
    if ( PAD & PadSelect && !(lastPad & PadSelect) ) {
        //~ if (!levelHasChanged){
        #ifndef USECD
            printf("load:%p:%08x:%s", &load_all_overlays_here, &level, overlayFile);
        //~ PCload( &load_all_overlays_here, &levelHasChanged, overlayFile );
        #endif
        #ifdef USECD
            level += 1;
            if (level > MAX_LEVELS){
                level = 0;
            };
            //~ levelHasChanged = 1;
        #endif
        //~ }
        timer = 30;
        lastPad = PAD;
    }
    if ( !(PAD & PadSelect) && lastPad & PadSelect ) {
        lastPad = PAD;
    }
    if( theControllers[0].type == 0x73 && camMode == ACTOR){
        // Cam control - horizontal
        if ( theControllers[0].analog0 >= 0 && theControllers[0].analog0 < (128 - DS_DZ/2) ) {
            angleCam.vy += ( 16 * ( 128 - theControllers[0].analog0 ) ) >> 8 ;
            angleCamTimer = 120;
        }
        if ( theControllers[0].analog0 > (128 + DS_DZ/2)  && theControllers[0].analog0 <= 255 ) {
            angleCam.vy -= ( 16 * ( theControllers[0].analog0 - 128 ) ) >> 8 ;
            angleCamTimer = 120;
        }
        if ( theControllers[0].analog0 >= 0 && theControllers[0].analog0 < (128 - DS_DZ/2) ) {
            angleCam.vy += ( 16 * ( 128 - theControllers[0].analog0 ) ) >> 8 ;
            angleCamTimer = 120;
        }
        if ( theControllers[0].analog0 > (128 + DS_DZ/2) && theControllers[0].analog0 <= 255) {
            angleCam.vy -= ( 16 * ( theControllers[0].analog0 - 128 ) ) >> 8 ;
            angleCamTimer = 120;
        }
        // Timer to lerp cam back behind actor
        if ( angleCamTimer ){
            angleCamTimer --;
        }
        if (!angleCamTimer && angleCam.vy){
            angleCam.vy += lerp( angleCam.vy, 0, 64 ) == 0 ? 1 : lerp( angleCam.vy, 0, 64 );
        }
    } 
    // Print controller infos
    //~ FntPrint( "Pad 1 : %02x\nButtons:%02x %02x, Stick:%02d %02d %02d %02d\n",
            //~ theControllers[0].type,             // Controller type : 0x00 == none,  0x41 == standard, 0x73 == analog/dualshock, 0x12 == mouse, 0x23 == steering wheel, 0x63 == gun, 0x53 == analog joystick
            //~ theControllers[0].button1,          // 
            //~ theControllers[0].button2,
            //~ theControllers[0].analog0,  // R3 hor  : left: 0 7F right: 7F FF   dz 78 83
            //~ theControllers[0].analog1,  // R3 vert :  up : 0 7F down : 7F FF : dz 83 86
            //~ theControllers[0].analog2,  // L3 hor : left : 0 7F right: 7F FF : dz 69 81 68 - 8E 
            //~ theControllers[0].analog3 ); // L3 vert : up : 0 7F down : 7F FF : dz 74 8D
    if ( cursor ) {
        //~ curLvl.actorPtr->body->gForce.vy = 0;
        //~ curLvl.actorPtr->body->position.vy = lerpValues[cursor];
    }
};

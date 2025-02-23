#include "level2.h"

CVECTOR level2_BGc = { 134, 231, 229, 0 };

VECTOR level2_BKc = { 173, 173, 173, 0 };

CAMPOS level2_camPos_Camera = {
	{ -770,459,623 },
	{ 301,531,0 }
};

CAMPATH level2_camPath = {
	0,
	0,
	0,
	{0}
};

MATRIX level2_lgtmat = {
	-2486, 3254, -22, // L1
	0, 0, 0,
	0, 0, 0
	};

MATRIX level2_cmat = {
//   L1   L2   L3
	4096, 0, 0, // R
	4096, 0, 0, // G
	4096, 0, 0  // B
	};

SVECTOR level2_modelCube_mesh[] = {
	{ -32,33,33,0 },
	{ 33,33,33,0 },
	{ 33,33,-32,0 },
	{ -32,33,-32,0 },
	{ -32,-32,33,0 },
	{ 33,-32,33,0 },
	{ 33,-32,-32,0 },
	{ -32,-32,-32,0 }
};

SVECTOR level2_modelCube_normal[] = {
	2365,-2365,-2365, 0,
	-2365,-2365,-2365, 0,
	-2365,-2365,2365, 0,
	2365,-2365,2365, 0,
	2365,2365,-2365, 0,
	-2365,2365,-2365, 0,
	-2365,2365,2365, 0,
	2365,2365,2365, 0
};

CVECTOR level2_modelCube_color[] = {
	255,236,0, 0,
	255,237,0, 0,
	255,237,0, 0,
	255,235,0, 0,
	255,8,0, 0,
	255,2,0, 0,
	255,6,2, 0,
	254,3,0, 0,
	229,0,255, 0,
	229,0,255, 0,
	232,21,232, 0,
	229,0,255, 0,
	0,12,255, 0,
	5,16,250, 0,
	2,13,253, 0,
	0,12,255, 0,
	0,255,26, 0,
	4,251,25, 0,
	0,255,26, 0,
	0,255,26, 0,
	0,248,255, 0,
	0,248,255, 0,
	0,248,255, 0,
	0,248,255, 0
};

PRIM level2_modelCube_index[] = {
	0,1,2,3,8,
	4,7,6,5,8,
	0,4,5,1,8,
	1,5,6,2,8,
	2,6,7,3,8,
	4,0,3,7,8
};

BODY level2_modelCube_body = {
	{0, 0, 0, 0},
	0,-236,23, 0,
	0,-1024,0, 0,
	8,
	ONE/8,
	-33,-32,-33, 0,
	33,32,33, 0,
	0,
	};

TMESH level2_modelCube = {
	level2_modelCube_mesh,
	level2_modelCube_normal,
	0,
	level2_modelCube_color, 
	6
};

MESH level2_meshCube = {
	24,
	&level2_modelCube,
	level2_modelCube_index,
	0,
	0,
	{0}, // Matrix
	{0,-236,23, 0}, // position
	{0,-1024,0, 0}, // rotation
	1, // isProp
	1, // isRigidBody
	0, // isStaticBody
	0, // isRound 
	0, // isPrism
	0, // isAnim
	1, // isActor
	0, // isLevel
	0, // isWall
	0, // isBG
	0, // isSprite
	0, // p
	0, // otz
	&level2_modelCube_body,
	0, // Mesh anim tracks
	0, // Current VANIM
	&level2_nodePlane,
	0 // Screen space coordinates
};

SVECTOR level2_modelPlane_mesh[] = {
	{ -520,0,-520,0 },
	{ 520,0,-520,0 },
	{ -520,0,520,0 },
	{ 520,0,520,0 },
	{ -520,0,313,0 },
	{ -520,0,105,0 },
	{ -520,0,-104,0 },
	{ -520,0,-312,0 },
	{ -312,0,-520,0 },
	{ -104,0,-520,0 },
	{ 105,0,-520,0 },
	{ 313,0,-520,0 },
	{ 520,0,-312,0 },
	{ 520,0,-104,0 },
	{ 520,0,105,0 },
	{ 520,0,313,0 },
	{ 313,0,520,0 },
	{ 105,0,520,0 },
	{ -104,0,520,0 },
	{ -312,0,520,0 },
	{ -312,0,-312,0 },
	{ -312,0,-104,0 },
	{ -312,0,105,0 },
	{ -312,0,313,0 },
	{ -104,0,-312,0 },
	{ -104,0,-104,0 },
	{ -104,0,105,0 },
	{ -104,0,313,0 },
	{ 105,0,-312,0 },
	{ 105,0,-104,0 },
	{ 105,0,105,0 },
	{ 105,0,313,0 },
	{ 313,0,-312,0 },
	{ 313,0,-104,0 },
	{ 313,0,105,0 },
	{ 313,0,313,0 },
	{ -520,0,-416,0 },
	{ 417,0,-520,0 },
	{ 520,0,417,0 },
	{ -416,0,520,0 },
	{ -520,0,417,0 },
	{ -520,0,209,0 },
	{ -520,0,0,0 },
	{ -520,0,-208,0 },
	{ -416,0,-520,0 },
	{ -208,0,-520,0 },
	{ 0,0,-520,0 },
	{ 209,0,-520,0 },
	{ 520,0,-416,0 },
	{ 520,0,-208,0 },
	{ 520,0,0,0 },
	{ 520,0,209,0 },
	{ 417,0,520,0 },
	{ 209,0,520,0 },
	{ 0,0,520,0 },
	{ -208,0,520,0 },
	{ -312,0,417,0 },
	{ -312,0,-416,0 },
	{ -312,0,-208,0 },
	{ -312,0,0,0 },
	{ -312,0,209,0 },
	{ -104,0,417,0 },
	{ -104,0,-416,0 },
	{ -104,0,-208,0 },
	{ -104,0,0,0 },
	{ -104,0,209,0 },
	{ 105,0,417,0 },
	{ 105,0,-416,0 },
	{ 105,0,-208,0 },
	{ 105,0,0,0 },
	{ 105,0,209,0 },
	{ 313,0,417,0 },
	{ 313,0,-416,0 },
	{ 313,0,-208,0 },
	{ 313,0,0,0 },
	{ 313,0,209,0 },
	{ -416,0,-312,0 },
	{ -416,0,-104,0 },
	{ -416,0,105,0 },
	{ -416,0,313,0 },
	{ -208,0,-312,0 },
	{ -208,0,-104,0 },
	{ -208,0,105,0 },
	{ -208,0,313,0 },
	{ 0,0,-312,0 },
	{ 0,0,-104,0 },
	{ 0,0,105,0 },
	{ 0,0,313,0 },
	{ 209,0,-312,0 },
	{ 209,0,-104,0 },
	{ 209,0,105,0 },
	{ 209,0,313,0 },
	{ 417,0,-312,0 },
	{ 417,0,-104,0 },
	{ 417,0,105,0 },
	{ 417,0,313,0 },
	{ 417,0,209,0 },
	{ 417,0,0,0 },
	{ 417,0,-208,0 },
	{ 417,0,-416,0 },
	{ 209,0,209,0 },
	{ 209,0,0,0 },
	{ 209,0,-208,0 },
	{ 209,0,-416,0 },
	{ 0,0,209,0 },
	{ 0,0,0,0 },
	{ 0,0,-208,0 },
	{ 0,0,-416,0 },
	{ -208,0,209,0 },
	{ -208,0,0,0 },
	{ -208,0,-208,0 },
	{ -208,0,-416,0 },
	{ -416,0,209,0 },
	{ -416,0,0,0 },
	{ -416,0,-208,0 },
	{ -416,0,-416,0 },
	{ 209,0,417,0 },
	{ 0,0,417,0 },
	{ -208,0,417,0 },
	{ -416,0,417,0 },
	{ 417,0,417,0 }
};

SVECTOR level2_modelPlane_normal[] = {
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0,
	0,4096,0, 0
};

CVECTOR level2_modelPlane_color[] = {
	0,8,255, 0,
	0,8,255, 0,
	243,255,0, 0,
	240,252,3, 0,
	0,8,255, 0,
	0,8,255, 0,
	243,255,0, 0,
	240,252,3, 0,
	0,14,255, 0,
	0,9,255, 0,
	225,236,19, 0,
	243,255,0, 0,
	0,8,255, 0,
	0,8,255, 0,
	226,238,18, 0,
	225,237,19, 0,
	0,10,255, 0,
	0,8,255, 0,
	223,235,20, 0,
	243,255,0, 0,
	0,255,248, 0,
	0,255,248, 0,
	0,8,255, 0,
	0,8,255, 0,
	251,1,14, 0,
	250,0,14, 0,
	76,6,181, 0,
	78,6,181, 0,
	255,0,227, 0,
	255,0,227, 0,
	0,8,255, 0,
	0,8,255, 0,
	0,255,6, 0,
	0,255,6, 0,
	0,8,255, 0,
	0,8,255, 0,
	0,255,248, 0,
	0,255,248, 0,
	0,13,255, 0,
	0,8,255, 0,
	251,1,13, 0,
	251,1,13, 0,
	75,5,182, 0,
	77,5,180, 0,
	255,0,227, 0,
	255,0,227, 0,
	0,8,255, 0,
	0,8,255, 0,
	0,255,6, 0,
	0,255,6, 0,
	0,8,255, 0,
	0,12,255, 0,
	0,255,248, 0,
	0,255,248, 0,
	0,8,255, 0,
	0,16,255, 0,
	254,0,11, 0,
	254,0,11, 0,
	0,8,255, 0,
	4,9,251, 0,
	255,0,227, 0,
	255,0,227, 0,
	0,8,255, 0,
	0,8,255, 0,
	0,255,6, 0,
	0,255,6, 0,
	0,8,255, 0,
	0,8,255, 0,
	0,255,248, 0,
	0,255,248, 0,
	0,8,255, 0,
	0,8,255, 0,
	255,0,10, 0,
	255,0,10, 0,
	0,8,255, 0,
	0,8,255, 0,
	255,0,227, 0,
	255,0,227, 0,
	0,8,255, 0,
	0,8,255, 0,
	0,255,6, 0,
	0,255,6, 0,
	0,8,255, 0,
	0,9,255, 0,
	0,255,248, 0,
	0,255,248, 0,
	0,12,255, 0,
	0,8,255, 0,
	255,0,10, 0,
	255,0,10, 0,
	0,9,255, 0,
	0,8,255, 0,
	255,0,227, 0,
	255,0,227, 0,
	0,9,255, 0,
	0,8,255, 0,
	0,255,6, 0,
	0,255,6, 0,
	0,8,255, 0,
	0,8,255, 0,
	0,255,6, 0,
	0,255,6, 0,
	0,8,255, 0,
	0,8,255, 0,
	0,8,255, 0,
	0,8,255, 0,
	0,255,6, 0,
	0,255,6, 0,
	0,8,255, 0,
	0,9,255, 0,
	0,255,6, 0,
	0,255,6, 0,
	255,0,227, 0,
	255,0,227, 0,
	0,8,255, 0,
	0,8,255, 0,
	0,8,255, 0,
	0,8,255, 0,
	255,0,227, 0,
	255,0,227, 0,
	0,8,255, 0,
	0,9,255, 0,
	255,0,227, 0,
	255,0,227, 0,
	255,0,10, 0,
	255,0,10, 0,
	0,8,255, 0,
	0,8,255, 0,
	0,8,255, 0,
	0,8,255, 0,
	255,0,10, 0,
	255,0,10, 0,
	0,8,255, 0,
	0,12,255, 0,
	255,0,10, 0,
	255,0,10, 0,
	0,255,248, 0,
	0,255,248, 0,
	0,8,255, 0,
	0,8,255, 0,
	0,8,255, 0,
	0,8,255, 0,
	0,255,248, 0,
	0,255,248, 0,
	0,8,255, 0,
	0,27,255, 0,
	0,255,248, 0,
	0,255,248, 0,
	0,255,6, 0,
	0,255,6, 0,
	0,9,255, 0,
	0,8,255, 0,
	0,8,255, 0,
	0,8,255, 0,
	0,255,6, 0,
	0,255,6, 0,
	0,8,255, 0,
	0,8,255, 0,
	0,255,6, 0,
	0,255,6, 0,
	255,0,227, 0,
	255,0,227, 0,
	0,8,255, 0,
	0,8,255, 0,
	0,8,255, 0,
	0,8,255, 0,
	255,0,227, 0,
	255,0,227, 0,
	0,8,255, 0,
	0,8,255, 0,
	255,0,227, 0,
	255,0,227, 0,
	254,0,11, 0,
	255,0,10, 0,
	0,8,255, 0,
	0,8,255, 0,
	0,8,255, 0,
	0,8,255, 0,
	255,0,10, 0,
	254,0,11, 0,
	0,8,255, 0,
	0,8,255, 0,
	255,0,10, 0,
	255,0,10, 0,
	0,255,248, 0,
	0,255,248, 0,
	0,8,255, 0,
	0,8,255, 0,
	0,10,255, 0,
	0,8,255, 0,
	0,255,248, 0,
	0,255,248, 0,
	0,8,255, 0,
	0,8,255, 0,
	0,255,248, 0,
	0,255,248, 0,
	0,255,6, 0,
	0,255,6, 0,
	0,8,255, 0,
	0,8,255, 0,
	0,8,255, 0,
	0,8,255, 0,
	0,255,6, 0,
	0,255,6, 0,
	0,8,255, 0,
	0,8,255, 0,
	0,255,6, 0,
	0,255,6, 0,
	255,0,227, 0,
	255,0,227, 0,
	0,8,255, 0,
	0,8,255, 0,
	75,5,182, 0,
	4,9,251, 0,
	255,0,227, 0,
	255,0,227, 0,
	4,9,251, 0,
	0,8,255, 0,
	255,0,227, 0,
	255,0,227, 0,
	251,1,13, 0,
	254,0,11, 0,
	4,9,251, 0,
	75,5,182, 0,
	0,13,255, 0,
	0,16,255, 0,
	254,0,11, 0,
	251,1,13, 0,
	0,16,255, 0,
	0,8,255, 0,
	254,0,11, 0,
	254,0,11, 0,
	0,255,248, 0,
	0,255,248, 0,
	0,16,255, 0,
	0,13,255, 0,
	0,31,255, 0,
	0,31,255, 0,
	0,255,248, 0,
	0,255,248, 0,
	0,31,255, 0,
	0,10,255, 0,
	0,255,248, 0,
	0,255,248, 0,
	0,255,6, 0,
	0,255,6, 0,
	0,12,255, 0,
	0,8,255, 0,
	0,8,255, 0,
	0,8,255, 0,
	0,255,6, 0,
	0,255,6, 0,
	0,8,255, 0,
	0,8,255, 0,
	0,255,6, 0,
	0,255,6, 0,
	255,0,227, 0,
	255,0,227, 0,
	0,8,255, 0,
	0,8,255, 0,
	76,6,181, 0,
	77,5,180, 0,
	255,0,227, 0,
	255,0,227, 0,
	77,5,180, 0,
	75,5,182, 0,
	255,0,227, 0,
	255,0,227, 0,
	250,0,14, 0,
	251,1,13, 0,
	77,5,180, 0,
	76,6,181, 0,
	0,8,255, 0,
	0,8,255, 0,
	251,1,13, 0,
	250,0,14, 0,
	0,8,255, 0,
	0,13,255, 0,
	251,1,13, 0,
	251,1,13, 0,
	0,255,248, 0,
	0,255,248, 0,
	0,8,255, 0,
	0,8,255, 0,
	0,9,255, 0,
	0,12,255, 0,
	0,255,248, 0,
	0,255,248, 0,
	0,12,255, 0,
	0,31,255, 0,
	0,255,248, 0,
	0,255,248, 0,
	0,255,6, 0,
	0,255,6, 0,
	0,8,255, 0,
	0,8,255, 0,
	0,8,255, 0,
	0,8,255, 0,
	0,255,6, 0,
	0,255,6, 0,
	0,8,255, 0,
	0,8,255, 0,
	0,255,6, 0,
	0,255,6, 0,
	255,0,227, 0,
	255,0,227, 0,
	0,8,255, 0,
	0,8,255, 0,
	74,5,184, 0,
	78,6,181, 0,
	255,0,227, 0,
	255,0,227, 0,
	78,6,181, 0,
	76,6,181, 0,
	255,0,227, 0,
	255,0,227, 0,
	238,1,26, 0,
	251,1,14, 0,
	78,6,181, 0,
	74,5,184, 0,
	0,8,255, 0,
	0,8,255, 0,
	251,1,14, 0,
	238,1,26, 0,
	0,8,255, 0,
	0,8,255, 0,
	250,0,14, 0,
	251,1,14, 0,
	0,255,248, 0,
	0,255,248, 0,
	0,8,255, 0,
	0,8,255, 0,
	0,25,255, 0,
	0,17,255, 0,
	0,255,248, 0,
	0,255,248, 0,
	0,17,255, 0,
	0,9,255, 0,
	0,255,248, 0,
	0,255,248, 0,
	0,8,255, 0,
	0,10,255, 0,
	243,255,0, 0,
	226,238,18, 0,
	0,8,255, 0,
	0,9,255, 0,
	0,10,255, 0,
	0,8,255, 0,
	0,9,255, 0,
	0,8,255, 0,
	0,8,255, 0,
	0,10,255, 0,
	0,9,255, 0,
	0,8,255, 0,
	225,237,19, 0,
	225,236,19, 0,
	0,8,255, 0,
	0,8,255, 0,
	0,8,255, 0,
	0,9,255, 0,
	0,8,255, 0,
	0,8,255, 0,
	0,8,255, 0,
	0,8,255, 0,
	0,8,255, 0,
	0,14,255, 0,
	243,255,0, 0,
	243,255,0, 0,
	0,8,255, 0,
	0,12,255, 0,
	0,14,255, 0,
	0,8,255, 0,
	0,12,255, 0,
	0,8,255, 0,
	0,9,255, 0,
	0,14,255, 0,
	0,8,255, 0,
	0,8,255, 0,
	240,252,3, 0,
	243,255,0, 0,
	0,8,255, 0,
	0,8,255, 0,
	0,8,255, 0,
	0,8,255, 0,
	0,8,255, 0,
	0,8,255, 0,
	0,8,255, 0,
	0,8,255, 0,
	0,8,255, 0,
	0,8,255, 0,
	240,252,3, 0,
	223,235,20, 0,
	0,8,255, 0,
	0,8,255, 0,
	0,8,255, 0,
	0,8,255, 0,
	0,8,255, 0,
	0,8,255, 0,
	0,8,255, 0,
	0,8,255, 0
};

PRIM level2_modelPlane_index[] = {
	120,38,3,52,8,
	119,56,19,39,8,
	118,61,18,55,8,
	117,66,17,54,8,
	116,71,16,53,8,
	115,57,20,76,8,
	114,58,21,77,8,
	113,59,22,78,8,
	112,60,23,79,8,
	111,62,24,80,8,
	110,63,25,81,8,
	109,64,26,82,8,
	108,65,27,83,8,
	107,67,28,84,8,
	106,68,29,85,8,
	105,69,30,86,8,
	104,70,31,87,8,
	103,72,32,88,8,
	102,73,33,89,8,
	101,74,34,90,8,
	100,75,35,91,8,
	99,48,12,92,8,
	98,49,13,93,8,
	97,50,14,94,8,
	96,51,15,95,8,
	75,96,95,35,8,
	34,94,96,75,8,
	94,14,51,96,8,
	74,97,94,34,8,
	33,93,97,74,8,
	93,13,50,97,8,
	73,98,93,33,8,
	32,92,98,73,8,
	92,12,49,98,8,
	72,99,92,32,8,
	11,37,99,72,8,
	37,1,48,99,8,
	70,100,91,31,8,
	30,90,100,70,8,
	90,34,75,100,8,
	69,101,90,30,8,
	29,89,101,69,8,
	89,33,74,101,8,
	68,102,89,29,8,
	28,88,102,68,8,
	88,32,73,102,8,
	67,103,88,28,8,
	10,47,103,67,8,
	47,11,72,103,8,
	65,104,87,27,8,
	26,86,104,65,8,
	86,30,70,104,8,
	64,105,86,26,8,
	25,85,105,64,8,
	85,29,69,105,8,
	63,106,85,25,8,
	24,84,106,63,8,
	84,28,68,106,8,
	62,107,84,24,8,
	9,46,107,62,8,
	46,10,67,107,8,
	60,108,83,23,8,
	22,82,108,60,8,
	82,26,65,108,8,
	59,109,82,22,8,
	21,81,109,59,8,
	81,25,64,109,8,
	58,110,81,21,8,
	20,80,110,58,8,
	80,24,63,110,8,
	57,111,80,20,8,
	8,45,111,57,8,
	45,9,62,111,8,
	41,112,79,4,8,
	5,78,112,41,8,
	78,22,60,112,8,
	42,113,78,5,8,
	6,77,113,42,8,
	77,21,59,113,8,
	43,114,77,6,8,
	7,76,114,43,8,
	76,20,58,114,8,
	36,115,76,7,8,
	0,44,115,36,8,
	44,8,57,115,8,
	66,116,53,17,8,
	31,91,116,66,8,
	91,35,71,116,8,
	61,117,54,18,8,
	27,87,117,61,8,
	87,31,66,117,8,
	56,118,55,19,8,
	23,83,118,56,8,
	83,27,61,118,8,
	40,119,39,2,8,
	4,79,119,40,8,
	79,23,56,119,8,
	71,120,52,16,8,
	35,95,120,71,8,
	95,15,38,120,8
};

BODY level2_modelPlane_body = {
	{0, 0, 0, 0},
	0,0,0, 0,
	0,0,0, 0,
	10,
	ONE/10,
	-520,0,-520, 0,
	520,0,520, 0,
	0,
	};

TMESH level2_modelPlane = {
	level2_modelPlane_mesh,
	level2_modelPlane_normal,
	0,
	level2_modelPlane_color, 
	100
};

MESH level2_meshPlane = {
	400,
	&level2_modelPlane,
	level2_modelPlane_index,
	0,
	0,
	{0}, // Matrix
	{0,0,0, 0}, // position
	{0,0,0, 0}, // rotation
	0, // isProp
	0, // isRigidBody
	0, // isStaticBody
	0, // isRound 
	0, // isPrism
	0, // isAnim
	0, // isActor
	1, // isLevel
	0, // isWall
	0, // isBG
	0, // isSprite
	0, // p
	0, // otz
	&level2_modelPlane_body,
	0, // Mesh anim tracks
	0, // Current VANIM
	0,
	0 // Screen space coordinates
};

MESH * level2_meshes[2] = {
	&level2_meshCube,
	&level2_meshPlane
}; 

int level2_meshes_length = 2;

CAMANGLE level2_camAngle_Camera = {
	&level2_camPos_Camera,
	0,
	 0,
	 { 0 },
	 { 0 },
	 0,
	 0
};

CAMANGLE * level2_camAngles[0] = {
};

SIBLINGS level2_nodePlane_siblings = {
	0,
	{
		0
	}
};

CHILDREN level2_nodePlane_objects = {
	0,
	{
		0
	}
};

CHILDREN level2_nodePlane_rigidbodies = {
	1,
	{
		&level2_meshCube
	}
};

NODE level2_nodePlane = {
	&level2_meshPlane,
	&level2_nodePlane_siblings,
	&level2_nodePlane_objects,
	&level2_nodePlane_rigidbodies
};

MESH * level2_actorPtr = &level2_meshCube;
MESH * level2_levelPtr = &level2_meshPlane;
MESH * level2_propPtr  = &level2_meshCube;

CAMANGLE * level2_camPtr =  &level2_camAngle_Camera;

NODE * level2_curNode =  &level2_nodePlane;

LEVEL level2 = {
	&level2_BGc,
	&level2_BKc,
	&level2_cmat,
	&level2_lgtmat,
	(MESH **)&level2_meshes,
	&level2_meshes_length,
	&level2_meshCube,
	&level2_meshPlane,
	&level2_meshCube,
	&level2_camAngle_Camera,
	&level2_camPath,
	(CAMANGLE **)&level2_camAngles,
	&level2_nodePlane,
	0,
	0,
	0
};


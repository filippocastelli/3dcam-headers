#pragma once
#include <custom_types.h>
#include <defines.h>
#pragma once

extern LEVEL level2;
extern CVECTOR level2_BGc;
extern VECTOR level2_BKc;
extern CAMPOS level2_camPos_Camera;
extern CAMPATH level2_camPath;
extern MATRIX level2_lgtmat;
extern MATRIX level2_cmat;
extern SVECTOR modelCube_mesh[];
extern SVECTOR level2_modelCube_normal[];
extern CVECTOR level2_modelCube_color[];
extern PRIM level2_modelCube_index[];
extern BODY  level2_modelCube_body;
extern TMESH level2_modelCube;
extern MESH level2_meshCube;
extern SVECTOR modelPlane_mesh[];
extern SVECTOR level2_modelPlane_normal[];
extern CVECTOR level2_modelPlane_color[];
extern PRIM level2_modelPlane_index[];
extern BODY  level2_modelPlane_body;
extern TMESH level2_modelPlane;
extern MESH level2_meshPlane;
extern MESH * level2_meshes[2];
extern int level2_meshes_length;
extern CAMANGLE level2_camAngle_Camera;
extern CAMANGLE * level2_camAngles[0];
extern SIBLINGS level2_nodePlane_siblings;
extern CHILDREN level2_nodePlane_objects;
extern CHILDREN level2_nodePlane_rigidbodies;
extern NODE level2_nodePlane;
extern MESH * level2_actorPtr;
extern MESH * level2_levelPtr;
extern MESH * level2_propPtr;
extern CAMANGLE * level2_camPtr;
extern NODE * level2_curNode;
extern NODE level2_nodePlane;

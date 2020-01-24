//
//  HCMesh.h
//  Test
//
//  Created by Matt Stoker on 3/13/19.
//  Copyright © 2019 HollowCore. All rights reserved.
//

#ifndef HCMesh_h
#define HCMesh_h

#include "HCPrimitive.h"
#include "../Data/HCTriangle.h"

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Object Type
//----------------------------------------------------------------------------------------------------------------------------------
extern HCType HCMeshType;
typedef struct HCMesh* HCMeshRef;

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Construction
//----------------------------------------------------------------------------------------------------------------------------------
HCMeshRef HCMeshCreate(HCVector origin, HCInteger triangleCount, HCTriangle* triangles);

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Object Polymorphic Functions
//----------------------------------------------------------------------------------------------------------------------------------
HCBoolean HCMeshIsEqual(HCMeshRef self, HCMeshRef other);
HCInteger HCMeshHashValue(HCMeshRef self);
void HCMeshPrint(HCMeshRef self, FILE* stream);

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Primitive Polymorphic Functions
//----------------------------------------------------------------------------------------------------------------------------------
HCVector HCMeshNormalAtPoint(HCMeshRef self, HCVector point);
HCReal HCMeshIntersect(HCMeshRef self, HCRay ray);

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Attributes
//----------------------------------------------------------------------------------------------------------------------------------
HCVector HCMeshOrigin(HCMeshRef self);
HCInteger HCMeshTriangleCount(HCMeshRef self);

#endif /* HCMesh_h */

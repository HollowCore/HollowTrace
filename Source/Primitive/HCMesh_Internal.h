//
//  HCMesh_Internal.h
//  HollowCore
//
//  Created by Matt Stoker on 3/13/19.
//  Copyright © 2019 HollowCore. All rights reserved.
//

#ifndef HCMesh_Internal_h
#define HCMesh_Internal_h

#include "HCPrimitive_Internal.h"
#include "HCMesh.h"

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Object Type
//----------------------------------------------------------------------------------------------------------------------------------
typedef struct HCMesh {
    HCPrimitive base;
    HCVector origin;
    HCInteger triangleCount;
    HCTriangle* triangles;
} HCMesh;

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Construction
//----------------------------------------------------------------------------------------------------------------------------------
void HCMeshInit(void* memory, HCVector origin, HCInteger triangleCount, HCTriangle* triangles);
void HCMeshDestroy(HCMeshRef self);

#endif /* HCMesh_Internal_h */

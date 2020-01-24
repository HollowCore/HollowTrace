//
//  HCPlane_Internal.h
//  HollowCore
//
//  Created by Matt Stoker on 3/10/19.
//  Copyright © 2019 HollowCore. All rights reserved.
//

#ifndef HCPlane_Internal_h
#define HCPlane_Internal_h

#include "HCPrimitive_Internal.h"
#include "HCPlane.h"

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Object Type
//----------------------------------------------------------------------------------------------------------------------------------
typedef struct HCPlane {
    HCPrimitive base;
    HCVector origin;
    HCVector normal;
} HCPlane;

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Construction
//----------------------------------------------------------------------------------------------------------------------------------
void HCPlaneInit(void* memory, HCVector origin, HCVector normal);
void HCPlaneDestroy(HCPlaneRef self);

#endif /* HCPlane_Internal_h */

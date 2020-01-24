//
//  HCLight_Internal.h
//  HollowCore
//
//  Created by Matt Stoker on 3/10/19.
//  Copyright © 2019 HollowCore. All rights reserved.
//

#ifndef HCLight_Internal_h
#define HCLight_Internal_h

#include "HCLight.h"
#include "../../HollowMac/HollowCore/Source/Core/HCObject_Internal.h"

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Object Type
//----------------------------------------------------------------------------------------------------------------------------------
extern HCLightTypeData HCLightTypeDataInstance;

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Object Instance Data
//----------------------------------------------------------------------------------------------------------------------------------
typedef struct HCLight {
    HCObject base;
} HCLight;

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Construction
//----------------------------------------------------------------------------------------------------------------------------------
void HCLightInit(void* memory);
void HCLightDestroy(HCLightRef self);

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Light Polymorphic Functions
//----------------------------------------------------------------------------------------------------------------------------------
HCColor HCLightColorDefault(HCLightRef self);
HCVector HCLightDirectionToPointDefault(HCLightRef self, HCVector point);

#endif /* HCLight_Internal_h */

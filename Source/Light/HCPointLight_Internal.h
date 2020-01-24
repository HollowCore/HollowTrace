//
//  HCPointLight_Internal.h
//  HollowCore
//
//  Created by Matt Stoker on 3/10/19.
//  Copyright © 2019 HollowCore. All rights reserved.
//

#ifndef HCPointLight_Internal_h
#define HCPointLight_Internal_h

#include "HCLight_Internal.h"
#include "HCPointLight.h"

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Object Type
//----------------------------------------------------------------------------------------------------------------------------------
typedef struct HCPointLight {
    HCLight base;
    HCVector position;
    HCColor color;
} HCPointLight;

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Construction
//----------------------------------------------------------------------------------------------------------------------------------
void HCPointLightInit(void* memory, HCVector position, HCColor color);
void HCPointLightDestroy(HCPointLightRef self);

#endif /* HCPointLight_Internal_h */

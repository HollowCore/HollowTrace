//
//  HCLight.h
//  Test
//
//  Created by Matt Stoker on 3/10/19.
//  Copyright © 2019 HollowCore. All rights reserved.
//

#ifndef HCLight_h
#define HCLight_h

#include "../../HollowMac/HollowCore/Source/HollowCore.h"
#include "../Data/HCVector.h"

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Object Type
//----------------------------------------------------------------------------------------------------------------------------------
typedef HCColor (*HCLightColorFunction)(HCRef self);
typedef HCVector (*HCLightDirectionToPointFunction)(HCRef self, HCVector point);

typedef const struct HCLightTypeData {
    HCObjectTypeData base;
    HCLightColorFunction color;
    HCLightDirectionToPointFunction directionToPoint;
} HCLightTypeData;
extern HCType HCLightType;

typedef struct HCLight* HCLightRef;

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Construction
//----------------------------------------------------------------------------------------------------------------------------------
// NOTE: Instances of HCLight should be created using sub-types

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Light Polymorphic Functions
//----------------------------------------------------------------------------------------------------------------------------------
HCColor HCLightColor(HCLightRef self);
HCVector HCLightDirectionToPoint(HCLightRef self, HCVector point);

#endif /* HCLight_h */

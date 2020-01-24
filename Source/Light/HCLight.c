//
//  HCLight.c
//  Test
//
//  Created by Matt Stoker on 3/10/19.
//  Copyright © 2019 HollowCore. All rights reserved.
//

#include "HCLight_Internal.h"
#include <math.h>

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Object Type
//----------------------------------------------------------------------------------------------------------------------------------
HCLightTypeData HCLightTypeDataInstance = {
    .base = {
        .base = {
            .ancestor = NULL,
            .name = "HCLight",
        },
        .isEqual = (void*)HCObjectIsEqual,
        .hashValue = (void*)HCObjectHashValue,
        .print = (void*)HCObjectPrint,
        .destroy = (void*)HCLightDestroy,
    },
    .color = (void*)HCLightColorDefault,
    .directionToPoint = (void*)HCLightDirectionToPointDefault,
};
HCType HCLightType = &HCLightTypeDataInstance.base.base;

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Construction
//----------------------------------------------------------------------------------------------------------------------------------
void HCLightInit(void* memory) {
    HCObjectInit(memory);
    HCLightRef self = memory;
    self->base.type = HCLightType;
}

void HCLightDestroy(HCLightRef self) {
    (void)self; // Unused
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Light Polymorphic Functions
//----------------------------------------------------------------------------------------------------------------------------------
HCColor HCLightColor(HCLightRef self) {
    return ((HCLightTypeData*)self->base.type)->color(self);
}

HCVector HCLightDirectionToPoint(HCLightRef self, HCVector point) {
    return ((HCLightTypeData*)self->base.type)->directionToPoint(self, point);
}

HCColor HCLightColorDefault(HCLightRef self) {
    (void)self; // Unused
    return HCColorInvalid;
}

HCVector HCLightDirectionToPointDefault(HCLightRef self, HCVector point) {
    (void)self; (void)point; // Unused
    return HCVectorInvalid;
}

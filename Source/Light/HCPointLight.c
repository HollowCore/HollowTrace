//
//  HCPointLight.c
//  Test
//
//  Created by Matt Stoker on 3/10/19.
//  Copyright © 2019 HollowCore. All rights reserved.
//

#include "HCPointLight_Internal.h"
#include <math.h>

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Object Type
//----------------------------------------------------------------------------------------------------------------------------------
const HCLightTypeData HCPointLightTypeDataInstance = {
    .base = {
        .base = {
            .ancestor = &HCLightTypeDataInstance.base.base,
            .name = "HCPointLight",
        },
        .isEqual = (void*)HCPointLightIsEqual,
        .hashValue = (void*)HCPointLightHashValue,
        .print = (void*)HCPointLightPrint,
        .destroy = (void*)HCPointLightDestroy,
    },
    .color = (void*)HCPointLightColor,
    .directionToPoint = (void*)HCPointLightDirectionToPoint,
};
HCType HCPointLightType = (HCType)&HCPointLightTypeDataInstance;

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Construction
//----------------------------------------------------------------------------------------------------------------------------------
HCPointLightRef HCPointLightCreate(HCVector position, HCColor color) {
    HCPointLightRef self = calloc(sizeof(HCPointLight), 1);
    HCPointLightInit(self, position, color);
    return self;
}

void HCPointLightInit(void* memory, HCVector position, HCColor color) {
    HCLightInit(memory);
    HCPointLightRef self = memory;
    self->base.base.type = HCPointLightType;
    self->position = position;
    self->color = color;
}

void HCPointLightDestroy(HCPointLightRef self) {
    (void)self; // Unused
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Object Polymorphic Functions
//----------------------------------------------------------------------------------------------------------------------------------
HCBoolean HCPointLightIsEqual(HCPointLightRef self, HCPointLightRef other) {
    return
        HCVectorIsEqual(self->position, other->position) &&
        HCColorIsEqual(self->color, other->color);
}

HCInteger HCPointLightHashValue(HCPointLightRef self) {
    return
        HCVectorHashValue(self->position) ^
        HCColorHashValue(self->color);
}

void HCPointLightPrint(HCPointLightRef self, FILE* stream) {
    HCObjectPrint((HCObjectRef)self, stream);
    fprintf(stream, "(");
    fprintf(stream, "p:");
    HCVectorPrint(self->position, stream);
    fprintf(stream, ",");
    fprintf(stream, "c:");
    HCColorPrint(self->color, stream);
    fprintf(stream, ")");
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Light Polymorphic Functions
//----------------------------------------------------------------------------------------------------------------------------------
HCVector HCPointLightDirectionToPoint(HCPointLightRef self, HCVector point) {
    return HCVectorSubtract(self->position, point);
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Attributes
//----------------------------------------------------------------------------------------------------------------------------------
HCVector HCPointLightPosition(HCPointLightRef self) {
    return self->position;
}

HCColor HCPointLightColor(HCPointLightRef self) {
    return self->color;
}

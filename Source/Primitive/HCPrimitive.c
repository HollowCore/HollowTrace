//
//  HCPrimitive.c
//  HollowCore
//
//  Created by Matt Stoker on 3/5/19.
//  Copyright © 2019 HollowCore. All rights reserved.
//

#include "HCPrimitive_Internal.h"
#include <math.h>

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Object Type
//----------------------------------------------------------------------------------------------------------------------------------
HCPrimitiveTypeData HCPrimitiveTypeDataInstance = {
    .base = {
        .base = {
            .ancestor = NULL,
            .name = "HCPrimitive",
        },
        .isEqual = (void*)HCObjectIsEqual,
        .hashValue = (void*)HCObjectHashValue,
        .print = (void*)HCObjectPrint,
        .destroy = (void*)HCPrimitiveDestroy,
    },
    .normalAtPoint = (void*)HCPrimitiveNormalAtPointDefault,
    .intersect = (void*)HCPrimitiveIntersectDefault,
};
HCType HCPrimitiveType = &HCPrimitiveTypeDataInstance.base.base;

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Construction
//----------------------------------------------------------------------------------------------------------------------------------
void HCPrimitiveInit(void* memory) {
    HCObjectInit(memory);
    HCPrimitiveRef self = memory;
    self->base.type = HCPrimitiveType;
}

void HCPrimitiveDestroy(HCPrimitiveRef self) {
    (void)self; // Unused
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Primitive Polymorphic Functions
//----------------------------------------------------------------------------------------------------------------------------------
HCVector HCPrimitiveNormalAtPoint(HCPrimitiveRef self, HCVector point) {
    return ((HCPrimitiveTypeData*)self->base.type)->normalAtPoint(self, point);
}

HCReal HCPrimitiveIntersect(HCPrimitiveRef self, HCRay ray) {
    return ((HCPrimitiveTypeData*)self->base.type)->intersect(self, ray);
}

HCVector HCPrimitiveNormalAtPointDefault(HCPrimitiveRef self, HCVector point) {
    (void)self; (void)point; // Unused
    return HCVectorInvalid;
}

HCReal HCPrimitiveIntersectDefault(HCPrimitiveRef self, HCRay ray) {
    (void)self; (void)ray; // Unused
    return NAN;
}

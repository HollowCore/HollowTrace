//
//  HCPlane.c
//  Test
//
//  Created by Matt Stoker on 3/10/19.
//  Copyright © 2019 HollowCore. All rights reserved.
//

#include "HCPlane_Internal.h"
#include <math.h>

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Object Type
//----------------------------------------------------------------------------------------------------------------------------------
const HCPrimitiveTypeData HCPlaneTypeDataInstance = {
    .base = {
        .base = {
            .ancestor = &HCPrimitiveTypeDataInstance.base.base,
            .name = "HCPlane",
        },
        .isEqual = (void*)HCPlaneIsEqual,
        .hashValue = (void*)HCPlaneHashValue,
        .print = (void*)HCPlanePrint,
        .destroy = (void*)HCPlaneDestroy,
    },
    .normalAtPoint = (void*)HCPlaneNormalAtPoint,
    .intersect = (void*)HCPlaneIntersect,
};
HCType HCPlaneType = (HCType)&HCPlaneTypeDataInstance;

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Construction
//----------------------------------------------------------------------------------------------------------------------------------
HCPlaneRef HCPlaneCreate(HCVector origin, HCVector normal) {
    HCPlaneRef self = calloc(sizeof(HCPlane), 1);
    HCPlaneInit(self, origin, normal);
    return self;
}

void HCPlaneInit(void* memory, HCVector origin, HCVector normal) {
    HCPrimitiveInit(memory);
    HCPlaneRef self = memory;
    self->base.base.type = HCPlaneType;
    self->origin = origin;
    self->normal = normal;
}

void HCPlaneDestroy(HCPlaneRef self) {
    (void)self; // Unused
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Object Polymorphic Functions
//----------------------------------------------------------------------------------------------------------------------------------
HCBoolean HCPlaneIsEqual(HCPlaneRef self, HCPlaneRef other) {
    return
        HCVectorIsEqual(self->origin, other->origin) &&
        HCVectorIsEqual(self->normal, other->normal);
}

HCInteger HCPlaneHashValue(HCPlaneRef self) {
    return
        HCVectorHashValue(self->origin) ^
        HCVectorHashValue(self->normal);
}

void HCPlanePrint(HCPlaneRef self, FILE* stream) {
    HCObjectPrint((HCObjectRef)self, stream);
    fprintf(stream, "(");
    fprintf(stream, "o:");
    HCVectorPrint(self->origin, stream);
    fprintf(stream, ",");
    fprintf(stream, "n:");
    HCVectorPrint(self->normal, stream);
    fprintf(stream, ")");
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Primitive Polymorphic Functions
//----------------------------------------------------------------------------------------------------------------------------------
HCVector HCPlaneNormalAtPoint(HCPlaneRef self, HCVector point) {
    return self->normal;
}

HCReal HCPlaneIntersect(HCPlaneRef self, HCRay ray) {
    HCReal planeNDotRayD = HCVectorDot(HCPlaneNormal(self), ray.direction);
    
    // If the ray is parallel to the plane, no intersection
    if (planeNDotRayD < 0.00001 && planeNDotRayD > -0.00001) {
        return NAN;
    }
    
    // Determine the plane intersection parameter
    HCReal planeNDotRayO = HCVectorDot(HCPlaneNormal(self), ray.origin);
    HCReal planeD = -HCVectorDot(HCPlaneNormal(self), HCPlaneOrigin(self));
    HCReal intersection = -(planeD + planeNDotRayO) / planeNDotRayD;
    
    // Determine if the plane was intersected
    if (intersection > 0.00001) {
//        HCRayAddIntersection(ray, self, intersection);
        return intersection;
    }
    
    return NAN;
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Attributes
//----------------------------------------------------------------------------------------------------------------------------------
HCVector HCPlaneOrigin(HCPlaneRef self) {
    return self->origin;
}

HCVector HCPlaneNormal(HCPlaneRef self) {
    return self->normal;
}

//
//  HCMesh.c
//  Test
//
//  Created by Matt Stoker on 3/13/19.
//  Copyright © 2019 HollowCore. All rights reserved.
//

#include "HCMesh_Internal.h"
#include <math.h>
#include <string.h>

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Object Type
//----------------------------------------------------------------------------------------------------------------------------------
const HCPrimitiveTypeData HCMeshTypeDataInstance = {
    .base = {
        .base = {
            .ancestor = &HCPrimitiveTypeDataInstance.base.base,
            .name = "HCMesh",
        },
        .isEqual = (void*)HCMeshIsEqual,
        .hashValue = (void*)HCMeshHashValue,
        .print = (void*)HCMeshPrint,
        .destroy = (void*)HCMeshDestroy,
    },
    .normalAtPoint = (void*)HCMeshNormalAtPoint,
    .intersect = (void*)HCMeshIntersect,
};
HCType HCMeshType = (HCType)&HCMeshTypeDataInstance;

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Construction
//----------------------------------------------------------------------------------------------------------------------------------
HCMeshRef HCMeshCreate(HCVector origin, HCInteger triangleCount, HCTriangle* triangles) {
    HCMeshRef self = calloc(sizeof(HCMesh), 1);
    HCMeshInit(self, origin, triangleCount, triangles);
    return self;
}

void HCMeshInit(void* memory, HCVector origin, HCInteger triangleCount, HCTriangle* triangles) {
    // TODO: Check that the allocation and copy proceed successfully, determine how to pass the error otherwise
    HCTriangle* trianglesCopy = (HCTriangle*)malloc(sizeof(HCTriangle) * triangleCount);
    for (HCInteger triangleIndex = 0; triangleIndex < triangleCount; triangleIndex++) {
        HCTriangle triangle = triangles[triangleIndex];
        trianglesCopy[triangleIndex] = HCTriangleOffset(triangle, origin);
    }
    
    HCPrimitiveInit(memory);
    HCMeshRef self = memory;
    self->base.base.type = HCMeshType;
    self->origin = origin;
    self->triangleCount = triangleCount;
    self->triangles = trianglesCopy;
}

void HCMeshDestroy(HCMeshRef self) {
    free(self->triangles);
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Object Polymorphic Functions
//----------------------------------------------------------------------------------------------------------------------------------
HCBoolean HCMeshIsEqual(HCMeshRef self, HCMeshRef other) {
    return
        HCVectorIsEqual(self->origin, other->origin) &&
        HCIntegerIsEqual(self->triangleCount, other->triangleCount);
}

HCInteger HCMeshHashValue(HCMeshRef self) {
    HCInteger trianglesHash = 5381;
    for (HCInteger triangleIndex = 0; triangleIndex < self->triangleCount; triangleIndex++) {
        HCInteger triangleHash = HCTriangleHashValue(self->triangles[triangleIndex]);
        trianglesHash = ((trianglesHash << 5) + trianglesHash) + triangleHash;
    }
    return
        HCVectorHashValue(self->origin) ^
        trianglesHash;
}

void HCMeshPrint(HCMeshRef self, FILE* stream) {
    HCObjectPrint((HCObjectRef)self, stream);
    fprintf(stream, "(");
    fprintf(stream, "o:");
    HCVectorPrint(self->origin, stream);
    fprintf(stream, ",");
    fprintf(stream, "c:");
    HCIntegerPrint(self->triangleCount, stream);
    fprintf(stream, ")");
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Primitive Polymorphic Functions
//----------------------------------------------------------------------------------------------------------------------------------
HCVector HCMeshNormalAtPoint(HCMeshRef self, HCVector point) {
    // TODO: Find triangle associated with point, return triangle normal for face or smooth normal for blended vertex normals
    return HCVectorMake(0.0, 1.0, 0.0);
}

HCReal HCMeshIntersect(HCMeshRef self, HCRay ray) {
    // Check all triangles for intersection
    for (HCInteger triangleIndex = 0; triangleIndex < self->triangleCount; triangleIndex++) {
        HCTriangle triangle = self->triangles[triangleIndex];
        
        // TODO: Understand this and make it faster
        HCVector e1 = HCVectorSubtract(triangle.a, triangle.c);
        HCVector e2 = HCVectorSubtract(triangle.b, triangle.c);
        HCVector r1 = HCVectorCross(ray.direction, e2);
        float denominator = HCVectorDot(e1, r1);
        
        // TODO: This kills triangles. Needed?
        // if (fabs(denominator) < EPSILON)
        //    return;
        
        float invDenominator = 1.0 / denominator;
        HCVector s = HCVectorSubtract(ray.origin, triangle.c);
        float b1 = HCVectorDot(s, r1) * invDenominator;
        
        if (b1 < 0.0f || b1 > 1.0f) {
            continue;
        }
        
        HCVector r2 = HCVectorCross(s, e1);
        float b2 = HCVectorDot(ray.direction, r2) * invDenominator;
        
        if (b2 < 0.0f || (b1 + b2) > 1.0f) {
            continue;
        }
        
        float intersection = HCVectorDot(e2, r2) * invDenominator;
        if (intersection > 0.00001) {
//            HCRayAddIntersection(ray, triangle, intersection);
            return intersection;
        }
    }
    return NAN;
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Attributes
//----------------------------------------------------------------------------------------------------------------------------------
HCVector HCMeshOrigin(HCMeshRef self) {
    return self->origin;
}

HCInteger HCMeshTriangleCount(HCMeshRef self) {
    return self->triangleCount;
}

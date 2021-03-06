//
//  HCPrimitive.h
//  HollowCore
//
//  Created by Matt Stoker on 3/5/19.
//  Copyright © 2019 HollowCore. All rights reserved.
//

#ifndef HCPrimitive_h
#define HCPrimitive_h

#include "../../HollowMac/HollowCore/Source/HollowCore.h"
#include "../Data/HCRay.h"

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Object Type
//----------------------------------------------------------------------------------------------------------------------------------
typedef HCVector (*HCPrimitiveNormalAtPointFunction)(HCRef self, HCVector point);
typedef HCReal (*HCPrimitiveIntersectFunction)(HCRef self, HCRay ray);

typedef const struct HCPrimitiveTypeData {
    HCObjectTypeData base;
    HCPrimitiveNormalAtPointFunction normalAtPoint;
    HCPrimitiveIntersectFunction intersect;
} HCPrimitiveTypeData;
extern HCType HCPrimitiveType;

typedef struct HCPrimitive* HCPrimitiveRef;

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Construction
//----------------------------------------------------------------------------------------------------------------------------------
// NOTE: Instances of HCPrimitive should be created using sub-types

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Primitive Polymorphic Functions
//----------------------------------------------------------------------------------------------------------------------------------
HCVector HCPrimitiveNormalAtPoint(HCPrimitiveRef self, HCVector point);
HCReal HCPrimitiveIntersect(HCPrimitiveRef self, HCRay ray);

#endif /* HCPrimitive_h */

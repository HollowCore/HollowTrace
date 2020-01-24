//
//  HCPlane.h
//  Test
//
//  Created by Matt Stoker on 3/10/19.
//  Copyright © 2019 HollowCore. All rights reserved.
//

#ifndef HCPlane_h
#define HCPlane_h

#include "HCPrimitive.h"

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Object Type
//----------------------------------------------------------------------------------------------------------------------------------
extern HCType HCPlaneType;
typedef struct HCPlane* HCPlaneRef;

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Construction
//----------------------------------------------------------------------------------------------------------------------------------
HCPlaneRef HCPlaneCreate(HCVector origin, HCVector normal);

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Object Polymorphic Functions
//----------------------------------------------------------------------------------------------------------------------------------
HCBoolean HCPlaneIsEqual(HCPlaneRef self, HCPlaneRef other);
HCInteger HCPlaneHashValue(HCPlaneRef self);
void HCPlanePrint(HCPlaneRef self, FILE* stream);

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Primitive Polymorphic Functions
//----------------------------------------------------------------------------------------------------------------------------------
HCVector HCPlaneNormalAtPoint(HCPlaneRef self, HCVector point);
HCReal HCPlaneIntersect(HCPlaneRef self, HCRay ray);

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Attributes
//----------------------------------------------------------------------------------------------------------------------------------
HCVector HCPlaneOrigin(HCPlaneRef self);
HCVector HCPlaneNormal(HCPlaneRef self);

#endif /* HCPlane_h */

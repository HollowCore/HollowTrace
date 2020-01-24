//
//  HCPointLight.h
//  Test
//
//  Created by Matt Stoker on 3/10/19.
//  Copyright © 2019 HollowCore. All rights reserved.
//

#ifndef HCPointLight_h
#define HCPointLight_h

#include "HCLight.h"

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Object Type
//----------------------------------------------------------------------------------------------------------------------------------
extern HCType HCPointLightType;
typedef struct HCPointLight* HCPointLightRef;

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Construction
//----------------------------------------------------------------------------------------------------------------------------------
HCPointLightRef HCPointLightCreate(HCVector position, HCColor color);

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Object Polymorphic Functions
//----------------------------------------------------------------------------------------------------------------------------------
HCBoolean HCPointLightIsEqual(HCPointLightRef self, HCPointLightRef other);
HCInteger HCPointLightHashValue(HCPointLightRef self);
void HCPointLightPrint(HCPointLightRef self, FILE* stream);

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Primitive Polymorphic Functions
//----------------------------------------------------------------------------------------------------------------------------------
HCVector HCPointLightDirectionToPoint(HCPointLightRef self, HCVector point);

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Attributes
//----------------------------------------------------------------------------------------------------------------------------------
HCVector HCPointLightPosition(HCPointLightRef self);
HCColor HCPointLightColor(HCPointLightRef self);

#endif /* HCPointLight_h */

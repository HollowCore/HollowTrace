//
//  HCTriangle.h
//  Test
//
//  Created by Matt Stoker on 3/13/19.
//  Copyright © 2019 HollowCore. All rights reserved.
//

#ifndef HCTriangle_h
#define HCTriangle_h

#include "HCVector.h"

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Object Type
//----------------------------------------------------------------------------------------------------------------------------------
typedef struct HCTriangle {
    HCVector a;
    HCVector b;
    HCVector c;
} HCTriangle;

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Constructors
//----------------------------------------------------------------------------------------------------------------------------------
HCTriangle HCTriangleMake(HCVector a, HCVector b, HCVector c);

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Equality
//----------------------------------------------------------------------------------------------------------------------------------
HCBoolean HCTriangleIsInvalid(HCTriangle triangle);
HCBoolean HCTriangleIsSimilar(HCTriangle triangle, HCTriangle other, HCReal axisDissimilarity);
HCBoolean HCTriangleIsEqual(HCTriangle triangle, HCTriangle other);
HCInteger HCTriangleHashValue(HCTriangle triangle);
void HCTrianglePrint(HCTriangle triangle, FILE* stream);

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Operations
//----------------------------------------------------------------------------------------------------------------------------------
HCVector HCTrianglePointAt(HCTriangle triangle, HCReal lambdaA, HCReal lambdaB, HCReal lambdaC);
HCTriangle HCTriangleOffset(HCTriangle triangle, HCVector offset);

#endif /* HCTriangle_h */

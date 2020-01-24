//
//  HCTriangle.c
//  Test
//
//  Created by Matt Stoker on 3/13/19.
//  Copyright © 2019 HollowCore. All rights reserved.
//

#include "HCTriangle.h"

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Constructors
//----------------------------------------------------------------------------------------------------------------------------------
HCTriangle HCTriangleMake(HCVector a, HCVector b, HCVector c) {
    return (HCTriangle){.a = a, .b = b, .c = c};
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Equality
//----------------------------------------------------------------------------------------------------------------------------------
HCBoolean HCTriangleIsInvalid(HCTriangle triangle) {
    return
        HCVectorIsInvalid(triangle.a) ||
        HCVectorIsInvalid(triangle.b) ||
        HCVectorIsInvalid(triangle.c);
}

HCBoolean HCTriangleIsSimilar(HCTriangle triangle, HCTriangle other, HCReal axisDissimilarity) {
    return
        HCVectorIsSimilar(triangle.a, other.a, axisDissimilarity) &&
        HCVectorIsSimilar(triangle.b, other.b, axisDissimilarity) &&
        HCVectorIsSimilar(triangle.c, other.c, axisDissimilarity);
}

HCBoolean HCTriangleIsEqual(HCTriangle triangle, HCTriangle other) {
    return
        HCVectorIsEqual(triangle.a, other.a) &&
        HCVectorIsEqual(triangle.b, other.b) &&
        HCVectorIsEqual(triangle.c, other.c);
}

HCInteger HCTriangleHashValue(HCTriangle triangle) {
    return
        HCVectorHashValue(triangle.a) ^
        HCVectorHashValue(triangle.b) ^
        HCVectorHashValue(triangle.c);
}

void HCTrianglePrint(HCTriangle triangle, FILE* stream) {
    fprintf(stream, "<");
    fprintf(stream, "a:");
    HCVectorPrint(triangle.a, stream);
    fprintf(stream, ",");
    fprintf(stream, "b:");
    HCVectorPrint(triangle.b, stream);
    fprintf(stream, ",");
    fprintf(stream, "c:");
    HCVectorPrint(triangle.c, stream);
    fprintf(stream, ">");
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Operations
//----------------------------------------------------------------------------------------------------------------------------------
HCVector HCTrianglePointAt(HCTriangle triangle, HCReal lambdaA, HCReal lambdaB, HCReal lambdaC) {
    return HCVectorAdd(HCVectorScale(triangle.a, lambdaA), HCVectorAdd(HCVectorScale(triangle.b, lambdaB), HCVectorScale(triangle.c, lambdaC)));
}

HCTriangle HCTriangleOffset(HCTriangle triangle, HCVector offset) {
    return HCTriangleMake(HCVectorAdd(triangle.a, offset), HCVectorAdd(triangle.b, offset), HCVectorAdd(triangle.c, offset));
}

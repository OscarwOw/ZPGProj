#pragma once
#include "ModelKind.h"

/*
    Data inside Model
*/

struct ModelData {
    const float* data;
    int vertexCount;
    ModelKind modelKind;


    ModelData(const float* data, int vertexCount, ModelKind kind)
        : data(data), vertexCount(vertexCount), modelKind(kind) {
    }
};
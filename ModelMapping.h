#pragma once
#include <map>
#include "tree.h"
#include "bushes.h"
#include "suzi_smooth.h"
#include "suzi_flat.h"
#include "gift.h"
#include "plain.h"
#include "sphere.h"
#include "cube.h"
#include "triangle.h"
#include "ModelMapping.h"
#include "ModelType.h"

struct ModelData {
    const float* data;
    int vertexCount;
};

static const std::map<ModelType, ModelData> ModelMappings = {
    { ModelType::TREE, { tree, 92814 } },
    { ModelType::BUSH, { bushes, 8730 } },
    { ModelType::SUZI_SMOOTH, { suziSmooth, 2880 } },
    { ModelType::SUZI_FLAT, { suziFlat, 1704 } },
    { ModelType::GIFT, { gift, 36336 } },
    { ModelType::PLAIN, { plain, 36 } },
    { ModelType::SPHERE, { sphere, 17280 } },
    { ModelType::CUBE, { cube, 216 } },
    { ModelType::TRIANGLE, { triangle, 18 } }
};

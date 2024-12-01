#pragma once
#include <map>
#include "tree.h"
#include "bushes.h"
#include "suzi_smooth.h"
#include "suzi_flat.h"
#include "gift.h"
#include "plain.h"
#include "plainTexture.h"
#include "sphere.h"
#include "square.h"
#include "cube.h"
#include "triangle.h"
#include "ModelMapping.h"
#include "ModelType.h"
#include "ModelData.h"
#include "ModelKind.h"
#include "building.h"

/*
    Maps model name to data necesary for draw 
*/

static const std::map<ModelType, ModelData> ModelMappings = {
    { ModelType::TREE, { tree, 92814, ModelKind::BASIC_MODEL } },
    { ModelType::BUSH, { bushes, 8730, ModelKind::BASIC_MODEL } },
    { ModelType::SUZI_SMOOTH, { suziSmooth, 2880, ModelKind::BASIC_MODEL } },
    { ModelType::SUZI_FLAT, { suziFlat, 1704, ModelKind::BASIC_MODEL } },
    { ModelType::GIFT, { gift, 36336, ModelKind::BASIC_MODEL } },
    { ModelType::PLAIN, { plain, 6, ModelKind::BASIC_MODEL } },
    { ModelType::SPHERE, { sphere, 2880, ModelKind::BASIC_MODEL } },
    { ModelType::CUBE, { cube, 216, ModelKind::BASIC_MODEL } },
    { ModelType::TRIANGLE, { triangle, 18, ModelKind::BASIC_MODEL } },
    { ModelType::PLAIN_TEXTURE, {plainTexture, 6, ModelKind::TEXTURED_MODEL}},
    { ModelType::BUILDING_TEXTURE, {building, 6636, ModelKind::TEXTURED_MODEL}}
};

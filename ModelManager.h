#pragma once
#include <vector>
#include <memory>
#include <map>
#include "Model.h"
#include "ModelType.h"
#include "ModelMapping.h" // For ModelMappings
#include "IModel.h"
#include "TextureModel.h"

class ModelManager {
public:
    static ModelManager& getInstance() {
        static ModelManager instance;
        return instance;
    }

    IModel* getModel(ModelType modelType) {
        auto it = _modelCache.find(modelType);
        if (it != _modelCache.end()) {
            return it->second.get();
        }
        

        auto modelIt = ModelMappings.find(modelType);
        if (modelIt != ModelMappings.end()) {
            const ModelData& modelData = modelIt->second;
            
            if(modelData.modelKind == ModelKind::BASIC_MODEL){
                return loadModel(modelType, modelData.data, modelData.vertexCount, 6);
            }
            if (modelData.modelKind == ModelKind::TEXTURED_MODEL) {
                return loadTextureModel(modelType, modelData.data, modelData.vertexCount, 8);
            }

        }

        // Default to PLAIN model if the requested type isn't found
        std::cerr << "ModelType " << static_cast<int>(modelType) << " not found. Using default model (PLAIN)." << std::endl;
        return getModel(ModelType::PLAIN);
    }

    IModel* getModelFromFile(const char* modelFile) {
        return new TextureModel(modelFile);
    }

private:
    ModelManager() {}

    Model* loadModel(ModelType modelType, const float* rawData, int vertexCount, int floatsPerVertex) {
        auto newModel = std::make_shared<Model>(modelType, rawData, vertexCount, floatsPerVertex);
        _modelCache[modelType] = newModel;
        return newModel.get();
    }


    TextureModel* loadTextureModel(ModelType modelType, const float* rawData, int vertexCount, int floatsPerVertex) {
        auto newTextureModel = std::make_shared<TextureModel>(modelType, rawData, vertexCount, floatsPerVertex);
        _modelCache[modelType] = newTextureModel;
        return newTextureModel.get();
    }




    

    std::map<ModelType, std::shared_ptr<IModel>> _modelCache;
};

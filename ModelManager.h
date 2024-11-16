#pragma once
#include <vector>
#include <memory>
#include <map>
#include "Model.h"
#include "ModelType.h"
#include "ModelMapping.h" // For ModelMappings

class ModelManager {
public:
    // Singleton instance of ModelManager
    static ModelManager& getInstance() {
        static ModelManager instance;
        return instance;
    }

    // Method to get or load a model by ModelType
    Model* getModel(ModelType modelType) {
        // Search for the model in the cache
        auto it = _modelCache.find(modelType);
        if (it != _modelCache.end()) {
            return it->second.get();
        }

        // If not found, load the model from ModelMappings
        auto modelIt = ModelMappings.find(modelType);
        if (modelIt != ModelMappings.end()) {
            const ModelData& modelData = modelIt->second;
            return loadModel(modelType, modelData.data, modelData.vertexCount, 6);
        }

        // Default to PLAIN model if the requested type isn't found
        std::cerr << "ModelType " << static_cast<int>(modelType) << " not found. Using default model (PLAIN)." << std::endl;
        return getModel(ModelType::PLAIN);
    }

private:
    // Private constructor for Singleton pattern
    ModelManager() {}

    // Load a model and add it to the cache
    Model* loadModel(ModelType modelType, const float* rawData, int vertexCount, int floatsPerVertex) {
        auto newModel = std::make_shared<Model>(modelType, rawData, vertexCount, floatsPerVertex);
        _modelCache[modelType] = newModel;
        return newModel.get();
    }

    std::map<ModelType, std::shared_ptr<Model>> _modelCache;
};

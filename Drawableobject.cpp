#include "DrawableObject.h"
#include <glm/gtc/type_ptr.hpp> 
#include "SceneGenerator.h"
#include "ModelManager.h"



DrawableObject::DrawableObject() : _vertexBuffer(nullptr), _indexBuffer(nullptr) {
    _transformationMatrix = glm::mat4(1.0f);
}

DrawableObject::DrawableObject(
    TransformationData transformationData,
    ShaderType shaderType,
    ModelType modelType,
    glm::vec3 color,
    MaterialProperties materialProperties,
    Texture* texture
)
    : _color(color), _materialProperties(materialProperties), _texture(texture) {


    //TODO clean up shaders
    auto it = ShaderMappings.find(shaderType); // ShaderType handle
    if (it == ShaderMappings.end()) {
        std::cerr << "Invalid ShaderType specified. Assigning default shader." << std::endl;
        it = ShaderMappings.find(ShaderType::Test);
    }
    ShaderInfo shaderInfo = it->second;
    std::string accessString = ShaderProgramManager::getInstance().CreateShaderNemec(shaderInfo.vertexPath.c_str(), shaderInfo.fragmentPath.c_str(), "generatedObject");
    _shaderProgram = ShaderProgramManager::getInstance().getShader(accessString);
    if (_shaderProgram) {
        setShaderProgram(_shaderProgram);
    }


    _model = ModelManager::getInstance().getModel(modelType);

    updateDrawData();
}

DrawableObject::DrawableObject(ShaderType shaderType,const char* modelFile, Texture* texture, MaterialProperties material) 
    : _materialProperties(material), _texture(texture), _color(glm::vec3(1.0f))
{
    auto it = ShaderMappings.find(shaderType); 
    if (it == ShaderMappings.end()) {
        std::cerr << "Invalid ShaderType specified. Assigning default shader." << std::endl;
        it = ShaderMappings.find(ShaderType::Test);
    }
    ShaderInfo shaderInfo = it->second;
    std::string accessString = ShaderProgramManager::getInstance().CreateShaderNemec(shaderInfo.vertexPath.c_str(), shaderInfo.fragmentPath.c_str(), "generatedObject");
    _shaderProgram = ShaderProgramManager::getInstance().getShader(accessString);
    if (_shaderProgram) {
        setShaderProgram(_shaderProgram);
    }


    _model = ModelManager::getInstance().getModelFromFile(modelFile);
    updateDrawData();
}

DrawableObject::~DrawableObject() {
    delete _vertexBuffer;
    delete _indexBuffer;
}

void DrawableObject::Draw() {
    if (_shaderProgram) {
        _shaderProgram->use();
        
        updateDrawData();        

        if (_model) {
            _model->draw();
        }
        if (_texture != nullptr) {
            _texture->unbind();
        }
        _shaderProgram->use(0);
    }
}

void DrawableObject::setShaderProgram(ShaderProgram* shaderProgram) { 
    _shaderProgram = shaderProgram;
}

void DrawableObject::setShaderProgram(ShaderProgram* shaderProgram, std::string shaderProgramManagerString) {
    _shaderProgram = shaderProgram;
    _shaderProgramManagerString = shaderProgramManagerString;
}

void DrawableObject::setColor(glm::vec3 color)
{
    _color = color;
}

glm::vec3 DrawableObject::getColor()
{
    return _color;
}

ShaderProgram* DrawableObject::getSaherProgram()
{
    if (_shaderProgram) {
        return _shaderProgram;
    }
    return nullptr;
}

glm::mat4 DrawableObject::GetCurrentTransformation() {
    return this->_transformationMatrix;
}

TransformationData DrawableObject::GetCurrentTransformationData() {
    return transformationData;
}

glm::vec3 DrawableObject::getPosition()
{
    glm::mat4 matrix = transformationComposite.getMatrix();
    return glm::vec3(matrix[3][0], matrix[3][1], matrix[3][2]); 
}

MaterialProperties DrawableObject::getMaterialProperties() const
{
    return _materialProperties;
}



void DrawableObject::updateDrawData() { //update draw data
    MatrixHelper& matrixHelper = MatrixHelper::getInstance();

    glm::mat4 modelMatrix = transformationComposite.getMatrix();

    if (_texture != nullptr) {
        _shaderProgram->setUniformInt("textureUnitID", 0);
        _texture->bind();
        glActiveTexture(GL_TEXTURE0);
    }

    if (_shaderProgram) {
        _shaderProgram->use();
        _shaderProgram->setUniformMat4("modelMatrix", modelMatrix);
        _shaderProgram->setUniformVec3("objectColor", _color);
        _shaderProgram->updateMaterialProperties(_materialProperties);

        _shaderProgram->setUniformMat4("viewMatrix", _shaderProgram->getViewMatrix());
        _shaderProgram->setUniformMat4("projectionMatrix", _shaderProgram->getPerspectiveMatrix());
        _shaderProgram->setUniformVec3("cameraPosition", _shaderProgram->getCameraPosition());

        _shaderProgram->updateLightSources();
    }
}






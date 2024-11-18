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
    MaterialProperties materialProperties
    //later texture
)
    : _color(color), _materialProperties(materialProperties) {

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

    //auto modelIt = ModelMappings.find(modelType); // ModelType handle
    //if (modelIt != ModelMappings.end()) {
    //    const ModelData& modelData = modelIt->second;
    //    loadFromRawData(modelData.data, modelData.vertexCount, 6);
    //}
    //else {
    //    std::cerr << "Invalid ModelType specified. Assigning default model." << std::endl;
    //    const ModelData& modelData = ModelMappings.at(ModelType::PLAIN);
    //    loadFromRawData(modelData.data, modelData.vertexCount, 6);
    //}

    // Apply transformations
    //translate(transformationData.TranslationX, transformationData.TranslationY, transformationData.TranslationZ);
    //rotate(transformationData.RotationAngle, transformationData.RotationX, transformationData.RotationY, transformationData.RotationZ);
    //scale(transformationData.Scale);
    updateDrawData();
}

DrawableObject::~DrawableObject() {
    delete _vertexBuffer;
    delete _indexBuffer;

}

void DrawableObject::loadFromRawData(const float* rawData, int vertexCount, int floatsPerVertex) //TODO RawDataLoader
{
    _vertexCount = vertexCount;

    glGenVertexArrays(1, &_VAO);
    glBindVertexArray(_VAO);

    _vertexBuffer = new VertexBuffer(rawData, vertexCount * floatsPerVertex * sizeof(float));
    _indexBuffer = new IndexBuffer(generateIndices(vertexCount), vertexCount);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, floatsPerVertex * sizeof(float), (void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, floatsPerVertex * sizeof(float), (void*)(3 * sizeof(float)));   

    glBindVertexArray(0);
}

unsigned int* DrawableObject::generateIndices(int vertexCount) {
    unsigned int* indices = new unsigned int[vertexCount];
    for (int i = 0; i < vertexCount; ++i) {
        indices[i] = i;
    }
    return indices;
}

void DrawableObject::Draw() {
    if (_shaderProgram) {
        _shaderProgram->use();
        //updateTransformation(16); //TODO deprecated
        updateDrawData();
        if (_model) {
            _model->bind();
            glDrawElements(GL_TRIANGLES, _model->getVertexCount(), GL_UNSIGNED_INT, nullptr);
            _model->unbind();
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
    return glm::vec3(matrix[3][0], matrix[3][1], matrix[3][2]); // TODO posible bug
    //return glm::vec3(transformationData.TranslationX, transformationData.TranslationY, transformationData.TranslationZ);
}

MaterialProperties DrawableObject::getMaterialProperties() const
{
    return _materialProperties;
}



void DrawableObject::translate(float x, float y, float z) {
    //transformation.translate(glm::vec3(x, y, z));


    //_transformationComposite.addTransformation(new TransformationTranslate(glm::vec3(x, y, z)));
    //_translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));
    

    
    transformationData.TranslationX = x;
    transformationData.TranslationY = y;
    transformationData.TranslationZ = z;


    //_isTranslateTransformationDirty = true;
    //_isTransformationDirty = true;
}

void DrawableObject::rotate(float angle, float x, float y, float z) {
    if (x == 0.0f && y == 0.0f && z == 0.0f) {
        y = 1.0f;
    }
    //_transformationComposite.addTransformation(new TransformationRotate(angle, glm::vec3(x, y, z)));
    //transformation.rotate(angle, glm::vec3(x, y, z));
    
    //_rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(x, y, z));

    transformationData.RotationAngle = angle;
    transformationData.RotationX = x;
    transformationData.RotationY = y;
    transformationData.RotationZ = z;

    //_isRotationTransformationDirty = true;
    //_isTransformationDirty = true;
}

void DrawableObject::scale(float scaleFactor) {    
    //_transformationComposite.addTransformation(new TransformationScale{glm::vec3(scaleFactor)});
    //transformation.scale(scaleFactor);

    //_scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(scaleFactor, scaleFactor, scaleFactor));
    

    transformationData.Scale = scaleFactor;

    //_isScaleTransformationDirty = true;
    //_isTransformationDirty = true;
}






void DrawableObject::updateDrawData() { //update draw data
    MatrixHelper& matrixHelper = MatrixHelper::getInstance();

    //glm::mat4 modelMatrix2 = _translationMatrix * _rotationMatrix * _scaleMatrix;
    //glm::mat4 modelMatrix = transformation.getModelMatrix();

    glm::mat4 modelMatrixNew = transformationComposite.getMatrix();

    glm::mat4 viewMatrix = glm::mat4(1.0);
    glm::mat4 perspectiveMatrix = glm::mat4(1.0);


    glm::vec3 lightPosition = glm::vec3(10.0f, 5.0f, 5.0f);
    float lightIntensity = 1.0f;
    glm::vec4 lightColor = glm::vec4(1.0f);
     

    if (_shaderProgram) {
        _shaderProgram->use();
        _shaderProgram->setUniformMat4("modelMatrix", modelMatrixNew);
        viewMatrix = _shaderProgram->getViewMatrix();

        _shaderProgram->setUniformMat4("viewMatrix", viewMatrix);
        perspectiveMatrix = _shaderProgram->getPerspectiveMatrix();

        _shaderProgram->setUniformMat4("projectionMatrix", perspectiveMatrix);
        _shaderProgram->setUniformVec3("lightPosition", lightPosition);
        _shaderProgram->setUniformVec3("cameraPosition", _shaderProgram->getCameraPosition());
        _shaderProgram->setUniformVec3("objectColor", _color);
        _shaderProgram->updateMaterialProperties(_materialProperties);
        _shaderProgram->updateLightSources();

    }
}

void DrawableObject::updateTransformation(float deltaTime)
{
    //transformation.updateTransformations(deltaTime);
    
}




#pragma once
#include <GL/glew.h>

#include <GLFW/glfw3.h>  

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>


class Texture {
public:
    Texture(const std::string& filePath, GLenum textureTarget = GL_TEXTURE_2D, GLint internalFormat = GL_RGB);
        //: _filePath(filePath), _textureTarget(textureTarget), _textureId(0) 
    void bind();
    void unbind();
    void setParameter(GLenum parameterName, GLint parameterValue);
    GLuint getTextureID() const;

private:
    std::string _filePath;    
    GLenum _textureTarget;    
    GLuint _textureId;

    void setDefaultParameters();
};
#define STB_IMAGE_IMPLEMENTATION
#include "libraries/stb/stb_image.h"

#include "Texture.h"

Texture::Texture(const std::string& filePath, GLenum textureTarget , GLint internalFormat )
    : _filePath(filePath), _textureTarget(textureTarget), _textureId(0){
    int width, height, nrChannels;
    unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &nrChannels, 0);
    if (data) {
        glGenTextures(1, &_textureId);
        glBindTexture(_textureTarget, _textureId);

        glTexImage2D(_textureTarget, 0, internalFormat, width, height, 0,
            nrChannels == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, data);

        glGenerateMipmap(_textureTarget);

        setDefaultParameters();

        stbi_image_free(data);
    }
    else {
        printf("Failed to load texture: %s\n", filePath.c_str());
        stbi_image_free(data);
    }

    if (_textureId == 0) {
        printf("Failed to load texture: \n");
    }

    setDefaultParameters();
}


void Texture::bind() {
    glBindTexture(GL_TEXTURE_2D, _textureId);
}

void Texture::unbind() {
    glBindTexture(_textureTarget, 0);
}


void Texture::setParameter(GLenum parameterName, GLint parameterValue) {
    bind();
    glTexParameteri(_textureTarget, parameterName, parameterValue);
    unbind();
}

GLuint Texture::getTextureID() const {
    return _textureId;
}

void Texture::setDefaultParameters() {
    bind();

    glTexParameteri(_textureTarget, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(_textureTarget, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(_textureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(_textureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    unbind();
}
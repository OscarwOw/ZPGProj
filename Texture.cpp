#define STB_IMAGE_IMPLEMENTATION
#include "libraries/stb/stb_image.h"

#include "Texture.h"

Texture::Texture(const std::string& filePath, GLenum textureTarget , GLint internalFormat )
    : _filePath(filePath), _textureTarget(textureTarget), _textureId(0){
    int width, height, nrChannels;
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &nrChannels, 0);
    if (data) {
        glGenTextures(1, &_textureId);
        //glActiveTexture(GL_TEXTURE0);
        glBindTexture(_textureTarget, _textureId);

        GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB;

        glTexImage2D(_textureTarget, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

        setDefaultParameters();

        glGenerateMipmap(_textureTarget);

        stbi_image_free(data);
        unbind();
    }
    else {
        printf("Failed to load texture: %s\n", filePath.c_str());
        stbi_image_free(data);
    }

    //setDefaultParameters();
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
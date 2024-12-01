#define STB_IMAGE_IMPLEMENTATION
#include "libraries/stb/stb_image.h"

#include "Texture.h"

Texture::Texture(const std::string& filePath, GLenum textureTarget , GLint internalFormat )
    : _filePath(filePath), _textureTarget(textureTarget), _textureId(0){
    int width, height, nrChannels;
    
    stbi_set_flip_vertically_on_load(true);
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

}

Texture::Texture(const std::vector<std::string>& faces)
    : _textureTarget(GL_TEXTURE_CUBE_MAP), _textureId(0) {
    glGenTextures(1, &_textureId);
    glBindTexture(GL_TEXTURE_CUBE_MAP, _textureId);

    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++) {
        unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data) {
            GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB;
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
        else {
            printf("err loading cubemap\n");
            stbi_image_free(data);
        }
    }

    setDefaultCubeMapParameters();
    unbind();
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

void Texture::setDefaultCubeMapParameters() {
    bind();

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    unbind();
}
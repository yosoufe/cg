#include "Texture.hpp"

Texture::Texture() : textureId(0),
                     width(0),
                     height(0),
                     bitDepth(0),
                     fileLocation((char*)"")
{
}

Texture::Texture(char *fileLocation) : textureId(0),
                                       width(0),
                                       height(0),
                                       bitDepth(0),
                                       fileLocation(fileLocation)
{
}

void Texture::loadTexture()
{
    unsigned char* texData = stbi_load(fileLocation, &width, &height, &bitDepth, 0);
    if (!texData)
    {
        printf("failed to find %s", fileLocation);
        return;
    }

    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);

    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(texData);
}

void Texture::useTexture()
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureId);
}

void Texture::clearTexture()
{
    glDeleteTextures(1, &textureId);
    textureId = 0;
    width = 0;
    height = 0;
    bitDepth = 0;
    fileLocation = (char*)"";
}

Texture::~Texture()
{
    clearTexture();
}
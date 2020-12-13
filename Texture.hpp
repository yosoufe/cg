#pragma once

#include <GL/glew.h>
#include "stb_image.h"

class Texture
{
private:
    GLuint textureId;
    int width, height, bitDepth;

    char* fileLocation;
public:
    Texture();
    Texture(char* fileLocation);
    void loadTexture();
    void useTexture();
    void clearTexture();
    ~Texture();
};
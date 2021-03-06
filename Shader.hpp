
#pragma once

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include "GL/glew.h"

class Shader
{
private:
    GLuint shaderId,
        uniformProjection,
        uniformModel,
        uniformView,
        uniformAmbientIntensity,
        uniformAmbientColor,
        uniformDiffuseIntensity,
        uniformDirection,
        uniformSpecularIntensity,
        uniformShininess,
        uniformEyePosition;
    void compileShader(const char *vertexCode, const char *fragmentCode);
    void addShader(GLuint theProgram, const char *shaderCode, GLenum shaderType);

public:
    Shader();
    ~Shader();
    void createFromString(const char *vertexCode, const char *fragmentCode);
    void createFromFiles(const char *vertexFile, const char *fragmentFile);

    GLuint getProjectionLocation();
    GLuint getModelLocation();
    GLuint getAmbientIntensityLocation();
    GLuint getAmbientColorLocation();
    GLuint getDiffuseIntensityLocation();
    GLuint getDirectionLocation();
    GLuint getSpecularIntensityLocation();
    GLuint getShininessLocation();
    GLuint getEyePositionLocation();

    void useShader();
    void clearShader();

    std::string readFile(const char *file);
    GLuint getViewLocation();
};
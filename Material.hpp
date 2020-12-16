#pragma once

#include "GL/glew.h"

class Material
{
private:
    GLfloat specularIntensity;
    GLfloat shininess;
     
public:
    Material();
    Material(GLfloat sIntensity, GLfloat  shininess);
    void useMaterial(GLuint speculatIntensityLocation, GLuint ShininessLocation);
    ~Material();
};
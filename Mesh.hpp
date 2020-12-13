
#pragma once

#include "GL/glew.h"

class Mesh
{
private:
    GLuint VAO, VBO, IBO;
    GLsizei indexCount;

public:
    Mesh();
    ~Mesh();
    void createMesh(GLfloat *vertices, unsigned int *indices,
                    unsigned int numOfVertices, unsigned int numOfIndices);
    void renderMesh();
    void clearMesh();
};
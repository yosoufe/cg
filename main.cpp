#include <stdio.h>
#include <string.h>
#include <cmath> // mathematical library
#include <vector>

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Mesh.hpp"
#include "Shader.hpp"
#include "Window.hpp"
#include "Camera.hpp"

const float toRadians = 3.14159265f / 180.0f;

std::vector<Mesh *> meshList;
std::vector<Shader *> shaderList;

GLfloat deltaTime = 0.0f, lastTime = 0.0f;

bool direction = true;
float triOffset = 0.0f;
float triMaxOffset = 0.7f;
float triIncrement = 0.01f;

float curAngle = 0.0f;

bool sizeDirection = true;
float curSize = 0.4f;
float maxSize = 0.8f;
float minSize = 0.1f;

// Vertex Shader
static const char *vShader = "../shaders/shader.vert";

// Fragment Shader
static const char *fShader = "../shaders/shader.frag";

void createObjects()
{
    unsigned int indices[] = {
        0, 3, 1,
        1, 3, 2,
        2, 3, 0,
        0, 1, 2};

    GLfloat vertices[] = {
        -1.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 1.0f,
        1.0f, -1.0f, 0.0f,
        0.0f, 1.0f, 0.0f};

    Mesh *obj1 = new Mesh();
    obj1->createMesh(vertices, indices, 12, 12);
    meshList.push_back(obj1);

    Mesh *obj2 = new Mesh();
    obj2->createMesh(vertices, indices, 12, 12);
    meshList.push_back(obj2);
}

void createShaders()
{
    Shader *shader1 = new Shader();
    shader1->createFromFiles(vShader, fShader);
    shaderList.push_back(shader1);
}

int main()
{

    Window mainWindow = Window(800, 600);
    mainWindow.initialize();

    createObjects();
    createShaders();
    Camera camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f),
                           glm::vec3(0.0f, 1.0f, 0.0f),
                           -90.0f,
                           0.0f,
                           5.0f,
                           1.0f);

    GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0;

    glm::mat4 projection = glm::perspective(45.0f,
                                            (GLfloat)mainWindow.getBufferWidth() / (GLfloat)mainWindow.getBufferHeight(),
                                            0.1f,
                                            100.0f);

    // Loop until Window Closed
    while (!mainWindow.getShouldClose())
    {
        GLfloat now = glfwGetTime();//returns as seconds // SDL_GetPerformanceCounter();
        deltaTime = now - lastTime; // (now - lastTime)*1000 / SDL_GetPerformaceFrequency();
        lastTime = now;

        // Get + Handler user input events
        glfwPollEvents();

        camera.keyControl(mainWindow.getKeys(), deltaTime);

        if (direction)
        {
            triOffset += triIncrement;
        }
        else
        {
            triOffset -= triIncrement;
        }

        if (std::fabs(triOffset) > triMaxOffset)
        {
            direction = !direction;
        }

        curAngle += 1.0f;

        if (curAngle >= 360)
        {
            curAngle -= 360.0f;
        }

        if (sizeDirection)
        {
            curSize += 0.01f;
        }
        else
        {
            curSize -= 0.01f;
        }

        if (curSize >= maxSize || curSize <= minSize)
        {
            sizeDirection = !sizeDirection;
        }

        // clear window
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shaderList[0]->useShader();
        uniformModel = shaderList[0]->getModelLocation();
        uniformProjection = shaderList[0]->getProjectionLocation();
        uniformView = shaderList[0]->getViewLocation();

        glm::mat4 model(1.0f);
        model = glm::translate(model, glm::vec3(-0.5f, triOffset, -2.5f));
        model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
        model = glm::rotate(model, curAngle * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));

        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));

        meshList[0]->renderMesh();

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.5f, -triOffset, -5.5f));
        model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
        model = glm::rotate(model, curAngle * toRadians, glm::vec3(0.0f, -1.0f, 0.0f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        meshList[1]->renderMesh();

        glUseProgram(0);

        mainWindow.swapBuffers();
    }

    return 0;
}
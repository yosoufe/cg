#pragma once

#include "GL/glew.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "GLFW/glfw3.h"

class Camera
{
private:
    glm::vec3 position, front, up, right, worldUp;
    GLfloat yaw, pitch;

    GLfloat movementSpeed, turnSpeed;

    void update();

public:
    Camera(glm::vec3 initPosition,
           glm::vec3 initUp,
           GLfloat initYaw,
           GLfloat initPitch,
           GLfloat initMoveSpeed,
           GLfloat initTurnSpeed);
    
    void keyControl(bool* keys, GLfloat deltaTime);
    void mouseControl(GLfloat xChange, GLfloat yChange);
    glm::mat4 calculateViewMatrix();
    glm::vec3 getCameraPosition();

    ~Camera();
};
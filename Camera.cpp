#include "Camera.hpp"

Camera::Camera(glm::vec3 initPosition,
               glm::vec3 initUp,
               GLfloat initYaw,
               GLfloat initPitch,
               GLfloat initMoveSpeed,
               GLfloat initTurnSpeed) : position(initPosition),
                                        worldUp(initUp),
                                        yaw(initYaw),
                                        pitch(initPitch),
                                        movementSpeed(initMoveSpeed),
                                        turnSpeed(initTurnSpeed)
{
    front = glm::vec3(0.0f, 0.0f, -1.0f);
    update();
}

void Camera::update()
{
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(front);

    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}

void Camera::keyControl(bool* keys, GLfloat deltaTime)
{
    GLfloat velocity = movementSpeed * deltaTime;

    if (keys[GLFW_KEY_W])
    {
        position += front * velocity;
    }
    if (keys[GLFW_KEY_S])
    {
        position -= front * velocity;
    }
    if (keys[GLFW_KEY_A])
    {
        position -= right * velocity;
    }
    if (keys[GLFW_KEY_D])
    {
        position += right * velocity;
    }
}

glm::mat4 Camera::calculateViewMatrix()
{
    return glm::lookAt(position, position+front, up);
}

void Camera::mouseControl(GLfloat xChange, GLfloat yChange){
    xChange *= turnSpeed;
    yChange *= turnSpeed;

    yaw += xChange;
    pitch += yChange;
    
    if (pitch > 89)
    {
        pitch = 89;
    }

    if (pitch < -89)
    {
        pitch = -89;
    }

    update();
}

glm::vec3 Camera::getCameraPosition()
{
    return position;
}

Camera::~Camera(){
}
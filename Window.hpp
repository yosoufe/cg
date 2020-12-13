#pragma once

#include <stdio.h>
#include "GL/glew.h"
#include "GLFW/glfw3.h"

class Window
{
private:
    GLFWwindow *mainWindow;
    GLint width, height;
    GLint bufferWidth, bufferHeight;

    bool keys[1024];

    GLfloat lastX, lastY, xChange, yChange;
    bool mouseFirstMoved;

    void createCallbacks();
    static void handleKey(GLFWwindow* window, int key, int code, int action, int mode);
    static void handleMouse(GLFWwindow* window, double xPose, double yPose);

public:
    Window();
    Window(GLint windowWidth, GLint widnowHeight);
    int initialize();

    GLint getBufferWidth(){return bufferWidth;}
    GLint getBufferHeight(){return bufferHeight;}

    bool getShouldClose(){return glfwWindowShouldClose(mainWindow);}
    void swapBuffers(){glfwSwapBuffers(mainWindow);}

    bool* getKeys(){return keys;}
    GLfloat getXChange();
    GLfloat getYChange();

    ~Window();
};
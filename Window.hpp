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


public:
    Window();
    Window(GLint windowWidth, GLint widnowHeight);
    int initialize();

    GLint getBufferWidth(){return bufferWidth;}
    GLint getBufferHeight(){return bufferHeight;}

    bool getShouldClose(){return glfwWindowShouldClose(mainWindow);}
    void swapBuffers(){glfwSwapBuffers(mainWindow);}

    ~Window();
};
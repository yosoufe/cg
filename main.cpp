#include <stdio.h>
#include "GL/glew.h"
#include "GLFW/glfw3.h"

const GLint WIDTH = 800, HEIGHT = 600;


int main(){
    // init glfw
    if(!glfwInit())
    {
        printf("GLFW init failed");
        glfwTerminate();
        return 1;
    }

    // setup gflw windwo property
    // OpenGL version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    // CORE PROFILE == no backward compatibility
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // Allow forward compatibility
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // create a window
    GLFWwindow *mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "Test Window", NULL, NULL);
    if (!mainWindow)
    {
        printf("GLFW Window creation failed");
        glfwTerminate();
        return 1;
    }

    // Get Buffer size information
    int bufferWidth, bufferHeight;
    glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

    // Set context for GLEW to use
    glfwMakeContextCurrent(mainWindow);

    // Allow modern Extension features
    glewExperimental = GL_TRUE;

    if(glewInit() != GLEW_OK)
    {
        printf("GLEW init failed\n");
        glfwDestroyWindow(mainWindow);
        glfwTerminate();
        return 1;
    }

    // setup viewport size
    glViewport(0,0, bufferWidth, bufferHeight);

    // Loop until Window Closed
    while(!glfwWindowShouldClose(mainWindow))
    {
        // Get + Handler user input events
        glfwPollEvents();

        // clear window
        glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(mainWindow);
    }

    return 0;
}
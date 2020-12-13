#include "Window.hpp"  

Window::Window(): width(800), height(600){}

Window::Window(GLint windowWidth, GLint widnowHeight):width(windowWidth), height(windowWidth){}

int Window::initialize(){
    // init glfw
    if(!glfwInit())
    {
        printf("GLFW init failed");
        glfwTerminate();
        return 1;
    }

    // setup gflw window property
    // OpenGL version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

    // CORE PROFILE == no backward compatibility
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // Allow forward compatibility
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // create a window
    mainWindow = glfwCreateWindow(width, height, "Test Window", NULL, NULL);
    if (!mainWindow)
    {
        printf("GLFW Window creation failed");
        glfwTerminate();
        return 1;
    }

    // Get Buffer size information
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

    glEnable(GL_DEPTH_TEST);

    // setup viewport size
    glViewport(0,0, bufferWidth, bufferHeight);
}

Window::~Window()
{
    glfwDestroyWindow(mainWindow);
    glfwTerminate();
}
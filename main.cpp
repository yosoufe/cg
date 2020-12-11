#include <stdio.h>
#include <string.h>
#include <cmath> // mathematical library
#include "GL/glew.h"
#include "GLFW/glfw3.h"

const GLint WIDTH = 800, HEIGHT = 600;

GLuint VAO, VBO, shader, uniformXMove;

bool direction = true;
float triOffset = 0.0f;
float triMaxOffset = 0.7f;
float triIncrement = 0.005f;

// Vertex Shader
static const char* vShader = "\n\
#version 330 \n\
\n\
layout (location=0) in vec3 pos;\n\
uniform float xMove;\n\
\n\
void main() \n\
{\n\
    gl_Position = vec4(0.4*pos.x + xMove, 0.4*pos.y, pos.z, 1.0);\n\
}\n\
";

// Fragment Shader
static const char* fShader = "\n\
#version 330 \n\
\n\
out vec4 color;\n\
\n\
void main() \n\
{\n\
    color = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n\
}\n\
";

void CreateTriangle()
{
    GLfloat vertices[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f , -1.0f, 0.0f,
        0.0f, 1.0f, 0.0f
    };

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void addShader(GLuint theProgram, const char* shaderCode, GLenum shaderType){
    GLuint theShader = glCreateShader(shaderType);

    const GLchar* theCode[1];
    theCode[0] = shaderCode;

    GLint codeLength[1];
    codeLength[0]= strlen(shaderCode);

    glShaderSource(theShader, 1, theCode, codeLength);
    glCompileShader(theShader);

    GLint result = 0;
    GLchar eLog[1024] = {0};

    glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
    if (!result){
        glGetShaderInfoLog(theShader, sizeof(eLog), NULL, eLog);
        printf("Error compiling %d shader '%s'\n",shaderType, eLog);
        return;
    }

    glAttachShader(theProgram, theShader);
}

void compileShaders(){
    shader = glCreateProgram();

    if(!shader){
        printf("Error creating shader program!\n");
        return;
    }

    addShader(shader, vShader, GL_VERTEX_SHADER);
    addShader(shader, fShader, GL_FRAGMENT_SHADER);

    GLint result = 0;
    GLchar eLog[1024] = {0};

    glLinkProgram(shader);
    glGetProgramiv(shader, GL_LINK_STATUS, &result);
    if (!result){
        glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
        printf("Error linking program '%s'\n",eLog);
        return;
    }

    glValidateProgram(shader);
    glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);
    if (!result){
        glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
        printf("Error validating program '%s'\n",eLog);
        return;
    }

    uniformXMove = glGetUniformLocation(shader, "xMove");
    printf("uniformXMove = %d\n", uniformXMove);
}

int main(){
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

    CreateTriangle();
    compileShaders();

    // Loop until Window Closed
    while(!glfwWindowShouldClose(mainWindow))
    {
        // Get + Handler user input events
        glfwPollEvents();

        if (direction)
        {
            triOffset += triIncrement;
        }
        else{
            triOffset -= triIncrement;
        }

        if (std::fabs(triOffset) > triMaxOffset){
            direction = !direction;
        }

        // clear window
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader);
        
        glUniform1f(uniformXMove, triOffset);


        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
        glUseProgram(0);


        glfwSwapBuffers(mainWindow);
    }

    return 0;
}
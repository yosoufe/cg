#include "Shader.hpp"  

Shader::Shader(): shaderId(0), uniformProjection(0), uniformModel(0){}

Shader::~Shader()
{
    clearShader();
}

void Shader::createFromString(const char* vertexCode, const char* fragmentCode){
    compileShader(vertexCode, fragmentCode);
}

void Shader::compileShader(const char* vertexCode, const char* fragmentCode){
    shaderId = glCreateProgram();

    if(!shaderId){
        printf("Error creating shader program!\n");
        return;
    }

    addShader(shaderId, vertexCode, GL_VERTEX_SHADER);
    addShader(shaderId, fragmentCode, GL_FRAGMENT_SHADER);

    GLint result = 0;
    GLchar eLog[1024] = {0};

    glLinkProgram(shaderId);
    glGetProgramiv(shaderId, GL_LINK_STATUS, &result);
    if (!result){
        glGetProgramInfoLog(shaderId, sizeof(eLog), NULL, eLog);
        printf("Error linking program '%s'\n",eLog);
        return;
    }

    glValidateProgram(shaderId);
    glGetProgramiv(shaderId, GL_VALIDATE_STATUS, &result);
    if (!result){
        glGetProgramInfoLog(shaderId, sizeof(eLog), NULL, eLog);
        printf("Error validating program '%s'\n",eLog);
        return;
    }

    uniformModel = glGetUniformLocation(shaderId, "model");
    uniformProjection = glGetUniformLocation(shaderId, "projection");
    uniformView = glGetUniformLocation(shaderId, "view");
}

void Shader::addShader(GLuint theProgram, const char* shaderCode, GLenum shaderType){
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

void Shader::useShader(){
    glUseProgram(shaderId);
}

void Shader::clearShader(){
    if (shaderId != 0){
        glDeleteProgram(shaderId);
    }

    uniformModel = 0;
    uniformProjection = 0;
}

GLuint Shader::getProjectionLocation(){
    return uniformProjection;
}

GLuint Shader::getModelLocation(){
    return uniformModel;
}

void Shader::createFromFiles(const char* vertexFile, const char* fragmentFile){
    std::string vertixString = readFile(vertexFile);
    std::string fragmentString = readFile(fragmentFile);

    const char* vertexCode = vertixString.c_str();
    const char* fragmentCode = fragmentString.c_str();

    compileShader(vertexCode, fragmentCode);
}

std::string Shader::readFile(const char* file){
    std::string content;
    std::ifstream fileStream(file, std::ios::in);
    if (!fileStream.is_open()){
        printf("Failed to read %s\n", file);
        return "";
    }

    std::string line = "";
    while(!fileStream.eof()){
        std::getline(fileStream, line);
        content.append(line + "\n");
    }
    // std::cout << content << std::endl;
    return content;
}

GLuint Shader::getViewLocation(){
    return uniformView;
}
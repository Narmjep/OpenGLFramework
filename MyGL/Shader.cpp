#include "Shader.h"
#include <fstream>
#include <iostream>
#include "debugging.hpp"
#include "../include/MyGL.h"

using namespace MyGL;

bool Shader::throwExceptionOnCompileError = true;

Shader::Shader(const std::string& vertexShaderPath , const std::string& fragmentShaderPath ) : vertexShaderPath(vertexShaderPath) , fragmentShaderPath(fragmentShaderPath)
{
    // Vertex
    std::string vertexSource = GetFileContent(vertexShaderPath);
    //Create shader
    int vertexID = glCreateShader(GL_VERTEX_SHADER);
    const char* content = vertexSource.c_str();
    //Compile
    GLDbgCall(glShaderSource(vertexID,1, &content,NULL)); //! c string
    CompileProgram(vertexID);
    //Check for error
    GLint succes = 0;
    glGetShaderiv(vertexID , GL_COMPILE_STATUS , &succes);
    if(succes == GL_FALSE){
        std::cerr << "Failed to compile shader: " << vertexShaderPath << std::endl;
        // Get the length of the shader compilation log
        int logLength;
        glGetShaderiv(vertexID, GL_INFO_LOG_LENGTH, &logLength);
        // Allocate a buffer to store the log
        char* logBuffer = new char[logLength];
        // Retrieve the shader compilation log and print it to the console
        glGetShaderInfoLog(vertexID, logLength, nullptr, logBuffer);
        std::cerr << logBuffer << std::endl;
        // Free the memory allocated for the log buffer
        delete[] logBuffer;
    }

    // Fragment
    std::string fragmentSource = GetFileContent(fragmentShaderPath);
    //Create shader
    GLDbgCall(int fragmentID = glCreateShader(GL_FRAGMENT_SHADER));
    content = fragmentSource.c_str();
    //Compile
    GLDbgCall(glShaderSource(fragmentID,1, &content,NULL)); //! c string
    CompileProgram(fragmentID);
    //Check for error
    succes = 0;
    glGetShaderiv(fragmentID , GL_COMPILE_STATUS , &succes);
    if(succes == GL_FALSE){
        std::cerr << "Failed to compile shader: " << fragmentShaderPath << std::endl;
        // Get the length of the shader compilation log
        int logLength;
        glGetShaderiv(fragmentID, GL_INFO_LOG_LENGTH, &logLength);
        // Allocate a buffer to store the log
        char* logBuffer = new char[logLength];
        // Retrieve the shader compilation log and print it to the console
        glGetShaderInfoLog(fragmentID, logLength, nullptr, logBuffer);
        std::cerr << logBuffer << std::endl;
        // Free the memory allocated for the log buffer
        delete[] logBuffer;
    }

    //Shader program
    GLDbgCall(shaderID = glCreateProgram());
    GLDbgCall(glAttachShader(shaderID , vertexID));
    GLDbgCall(glAttachShader(shaderID , fragmentID));
    GLDbgCall(glLinkProgram(shaderID));

    //Free shaders
    GLDbgCall(glDeleteShader(vertexID));
    GLDbgCall(glDeleteShader(fragmentID));
}

Shader::~Shader(){
    GLDbgCall(glDeleteProgram(shaderID));
}

void Shader::Use(){
    GLDbgCall(glUseProgram(shaderID));
}

void Shader::CompileProgram(GLuint shaderID){
    GLDbgCall(glCompileShader(shaderID));
    //Check for error
    GLint succes = 0;
    GLDbgCall(glGetShaderiv(shaderID , GL_COMPILE_STATUS , &succes));
    if(succes == GL_TRUE){
        return;
    } else {
        std::cerr << "Failed to compile shader: " << vertexShaderPath << std::endl;
        // Get the length of the shader compilation log
        int logLength;
        glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &logLength);
        // Allocate a buffer to store the log
        char* logBuffer = new char[logLength];
        // Retrieve the shader compilation log and print it to the console
        glGetShaderInfoLog(shaderID, logLength, nullptr, logBuffer);
        std::cerr << logBuffer << std::endl;
        // Free the memory allocated for the log buffer
        delete[] logBuffer;
        if(throwExceptionOnCompileError) throw std::runtime_error("Shader compilation failed! See log for details.");
    }
}


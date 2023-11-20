#ifndef DEBUGGING_HPP
#define DEBUGGING_HPP

#include <opengl.h>
#include <iostream>
#include "Shader.h"

#ifdef __GNUC__
#define ASSERT(x) if(!(x)) __builtin_trap();
#else ifdef _MSC_VER_
#define ASSERT(x) if(!(x)) __debugbreak();
#endif

#ifndef DBG
#define GLDbgCall(x) x
#else
#define GLDbgCall(x) ClearErrors();\
    x;\
    ASSERT(GetError(__FILE__,#x,__LINE__))
#endif

inline void ClearErrors(){
    while(glGetError() != GL_NO_ERROR);
}

inline bool GetError(const char* file, const char* func, int line){
    while(GLenum errorCode = glGetError()){
        std::cerr << "OpenGL Error at: " << file << " ; in function " << func << " ; at line " << line << " | Error code is " << std::hex << errorCode << std::endl;
        return false;
    }
    return true;
}

#define GLDbgGetUniformLocation(shader, uniform) GLDbgGetUniformLocationWrapper(shader, uniform, __FILE__ , __LINE__)

static inline GLint GLDbgGetUniformLocationWrapper(MyGL::Shader& shader , const char* uniform, const char* file , int line){
    GLint ret = GLDbgCall(glGetUniformLocation(shader.GetShaderID() , uniform));
    if(ret == -1) {
        std::cerr << "OpenGL Error in file: " << file << " ; Line: " << line << "| "; 
        std::cerr << "Couldn't find the uniform \'" << uniform << "\' in shader " << shader.GetVertexShaderPath() << " | " << shader.GetFragmentShaderPath() << '\n';
    }
    return ret;
}

static inline GLint GLDbgGetUniformLocationWrapper(MyGL::Shader* shader , const char* uniform, const char* file , int line){
    GLint ret = GLDbgCall(glGetUniformLocation(shader->GetShaderID() , uniform));
    if(ret == -1) {
        std::cerr << "OpenGL Error in file: " << file << " ; Line: " << line << "| "; 
        std::cerr << "Couldn't find the uniform \'" << uniform << "\' in shader " << shader->GetVertexShaderPath() << " | " << shader->GetFragmentShaderPath() << '\n';
    }
    return ret;
}

static inline GLint GLDbgGetUniformLocationWrapper(GLuint shaderID , const char* uniform, const char* file , int line){
    GLint ret = GLDbgCall(glGetUniformLocation(shaderID , uniform));
    if(ret == -1){
        std::cerr << "OpenGL Error in file: " << file << " ; Line: " << line << "| "; 
        std::cerr << "Couldn't find the uniform \'" << uniform << "\'" << '\n';
    }
    return ret;
}


#endif //DEBUGGING_HPP
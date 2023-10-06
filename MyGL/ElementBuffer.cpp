#include "ElementBuffer.h"
#include "debugging.hpp"

using namespace MyGL;

ElementBuffer::ElementBuffer(std::vector<GLuint>& indices){
    GLDbgCall(glGenBuffers(1 , &id));
    GLDbgCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,id));
    GLDbgCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW));
}

ElementBuffer::~ElementBuffer(){
    glDeleteBuffers(1,&id);
}

void ElementBuffer::Bind(){
    GLDbgCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,id));
}

void ElementBuffer::Unbind(){
    GLDbgCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0));
}
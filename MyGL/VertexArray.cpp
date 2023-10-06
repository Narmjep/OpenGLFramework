#include "VertexArray.h"
#include "debugging.hpp"

using namespace MyGL;

VertexArray::VertexArray()
{
    GLDbgCall(glGenVertexArrays(1,&id));
}

VertexArray::~VertexArray(){
    GLDbgCall(glDeleteVertexArrays(1,&id));
}

void VertexArray::LinkAttrib(VertexBuffer& vb , GLuint layout , GLuint number , GLenum type , GLsizeiptr stride , void* offset){
    vb.Bind();
    GLDbgCall(glVertexAttribPointer(layout , number , type , GL_FALSE , stride , offset));
    GLDbgCall(glEnableVertexAttribArray(layout));
    vb.Unbind();
}

void VertexArray::Bind(){
    GLDbgCall(glBindVertexArray(id));
}

void VertexArray::Unbind(){
    GLDbgCall(glBindVertexArray(0));
}
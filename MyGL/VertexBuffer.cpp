#include "VertexBuffer.h"
#include "debugging.hpp"

using namespace MyGL;

VertexBuffer::VertexBuffer(const std::vector<Vertex>& vertices){
    GLDbgCall(glGenBuffers(1 , &id));
    GLDbgCall(glBindBuffer(GL_ARRAY_BUFFER,id));
    GLDbgCall(glBufferData(GL_ARRAY_BUFFER,vertices.size() * sizeof(Vertex),vertices.data(),GL_STATIC_DRAW));
}

VertexBuffer::VertexBuffer(const void* data , GLsizeiptr size){
    GLDbgCall(glGenBuffers(1 , &id));
    Bind();
    GLDbgCall(glBufferData(GL_ARRAY_BUFFER,size,data,GL_STATIC_DRAW));
    Unbind();
}

VertexBuffer::~VertexBuffer(){
    GLDbgCall(glDeleteBuffers(1,&id));
}

void VertexBuffer::Bind(){
    GLDbgCall(glBindBuffer(GL_ARRAY_BUFFER,id));
}

void VertexBuffer::Unbind(){
    GLDbgCall(glBindBuffer(GL_ARRAY_BUFFER,0));
}
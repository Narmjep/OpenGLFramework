#ifndef ELEMENTBUFFER_H
#define ELEMENTBUFFER_H

#include <opengl.h>
#include "VertexArray.h"
#include "MyGLAPI.h"

namespace MyGL{

/**
 * @brief An element buffer is a buffer that contains indices to vertices in a vertex buffer
 * 
 */
class MyGLAPI ElementBuffer
{
public:
	ElementBuffer(std::vector<GLuint>& indices);
	ElementBuffer(const void* data , GLsizeiptr size);
	~ElementBuffer();
	void Bind();
	void Unbind();
	
private:
	GLuint id;
};

}

#endif // ELEMENTBUFFER_H
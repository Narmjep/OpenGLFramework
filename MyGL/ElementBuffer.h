#ifndef ELEMENTBUFFER_H
#define ELEMENTBUFFER_H

#include <opengl.h>
#include "VertexArray.h"
#include "MyGLAPI.h"

namespace MyGL{

class MyGLAPI ElementBuffer
{
public:
	ElementBuffer(std::vector<GLuint>& indices);
	~ElementBuffer();
	void Bind();
	void Unbind();
	
private:
	GLuint id;
};

}

#endif // ELEMENTBUFFER_H
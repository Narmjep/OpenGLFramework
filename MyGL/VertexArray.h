#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H

#include <opengl.h>
#include "VertexBuffer.h"
#include "MyGLAPI.h"

namespace MyGL{

class MyGLAPI VertexArray{
public:
	GLuint id;
	//Methods
	VertexArray();
	~VertexArray();
	/// @brief Enables a 
	/// @param vb 
	/// @param layout 
	/// @param number 
	/// @param type 
	/// @param stride 
	/// @param offset 
	void LinkAttrib(VertexBuffer& vb , GLuint layout , GLuint number , GLenum type , GLsizeiptr stride , void* offset);
	void Bind();
	void Unbind();
};

}

#endif // VERTEXARRAY_H
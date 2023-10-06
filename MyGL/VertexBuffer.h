#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

#include <opengl.h>
#include <glm.hpp>
#include <vector>
#include "MyGLAPI.h"

namespace MyGL{

struct MyGLAPI Vertex{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 color;
	glm::vec2 textureUV;
};

class MyGLAPI VertexBuffer
{
public:
	VertexBuffer(const std::vector<Vertex>& vertices);
	~VertexBuffer();
	void Bind();
	void Unbind();
	
private:
	GLuint id;
};

}

#endif // VERTEXBUFFER_H
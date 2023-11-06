#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

#include <opengl.h>
#include <glm.hpp>
#include <vector>
#include "MyGLAPI.h"

namespace MyGL{

/**
 * @brief A simple vertex struct that contains position, normal, color and textureUV
 * You can use a custom vertex struct if you want to
 */
struct MyGLAPI Vertex{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 color;
	glm::vec2 textureUV;
};

/**
 * @brief In OpenGL, a vertex buffer is a memory buffer inside the GPU.
 * Usually, it is used to store a large number of vertices.
 * 
 */
class MyGLAPI VertexBuffer
{
public:
	/**
	 * @brief Construct a new Vertex Buffer object
	 * 
	 * @param vertices A astd::vector of vertices
	 */
	VertexBuffer(const std::vector<Vertex>& vertices);
	/**
	 * @brief Construct a new Vertex Buffer object with a custom vertex struct
	 * 
	 * @param data a pointer to the data of the vertices
	 * @param size the size of the data
	 */
	VertexBuffer(const void* data , GLsizeiptr size);
	~VertexBuffer();
	void Bind();
	void Unbind();
	
private:
	GLuint id;
};

}

#endif // VERTEXBUFFER_H
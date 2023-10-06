#pragma once

#include "opengl.h"
#include "VertexArray.h"
#include "ElementBuffer.h"
#include "Texture.h"
#include <vector>
#include <memory>
#include "MyGLAPI.h"

namespace MyGL{

class MyGLAPI Mesh
{
public:
	//std::vector <Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<std::shared_ptr<Texture2D>> textures;
	Mesh(const std::vector<Vertex> vertices , std::vector<GLuint> indices , std::vector<std::shared_ptr<Texture2D>> textures = {});
	~Mesh();
	Mesh(const Mesh&);
	void Draw(Shader& shader ,
	const glm::mat4& modelMatrices = glm::mat4(1.0),
	const glm::vec3& translations = glm::vec3(0,0,0),
	const glm::vec3 & rotations = glm::vec3(0,0,0),
	const glm::vec3& scales = glm::vec3(0,0,0)
	);
	
private:
	VertexArray vertexArray;
	VertexBuffer* vb;
	ElementBuffer* eb;
};

}

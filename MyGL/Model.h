#pragma once

#include "MyGLAPI.h"
#include "Mesh.h"
#include <string>
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glm.hpp>


namespace MyGL{

class MyGLAPI  Model
{
public:
    static int importFlags;
    Model(const std::string& fileName);
    ~Model();
    void Draw(Shader& shader ,
	const glm::mat4& modelMatrices = glm::mat4(1.0),
	const glm::vec3& translations = glm::vec3(0,0,0),
	const glm::vec3 & rotations = glm::vec3(0,0,0),
	const glm::vec3& scales = glm::vec3(0,0,0)
	);

private:
    std::vector<std::unique_ptr<Mesh>> meshes;
    const std::string path;  
    void LoadModel(const std::string& fileName);
    void ProcessNode(aiNode* node , const aiScene* scene);
    std::unique_ptr<Mesh> ProcessMesh(aiMesh* mesh , const aiScene* scene);
    std::vector<std::shared_ptr<Texture2D>> LoadMaterialTextures(const aiScene* scene , aiMaterial* mat , aiTextureType type , TextureType typeName);
};

}
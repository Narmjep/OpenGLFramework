#include "Model.h"
#include <memory>
#include <stb_image.h>

namespace MyGL{

int Model::importFlags = aiProcess_FlipUVs | aiProcess_Triangulate | aiProcess_GenNormals | aiProcess_JoinIdenticalVertices;

Model::Model(const std::string& fileName) : path(fileName)
{
    LoadModel(fileName);
}

Model::~Model()
{

}

void Model::Draw(Shader& shader ,
    const glm::mat4& modelMatrices,
    const glm::vec3& translations,
    const glm::vec3 & rotations,
    const glm::vec3& scales
    )
{
    for(unsigned int i = 0; i < meshes.size(); i++){
        meshes[i]->Draw(shader , modelMatrices , translations , rotations , scales);
    }
}

void Model::LoadModel(const std::string& fileName)
{
    // Create scene
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(fileName , importFlags);
    if(!scene){
        printf("Model (%s) failed to load: %s\n" , fileName.c_str() , importer.GetErrorString());
        return;
    }

    // Process root node
    printf("Processing root node\n");
    ProcessNode(scene->mRootNode , scene);

}

void Model::ProcessNode(aiNode* node , const aiScene* scene)
{
    // Process meshes
    printf("Processing new node\n");
    printf("Node has %d meshes\n" , node->mNumMeshes);
    for(unsigned int i = 0; i < node->mNumMeshes; i++){
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        printf("Adding mesh to model\n");
        meshes.push_back(ProcessMesh(mesh , scene));
    }

    // Process children
    unsigned int numChildren = node->mNumChildren;
    printf("Current node has %d children\n" , numChildren);
    for(unsigned int i = 0; i < node->mNumChildren; i++){
        ProcessNode(node->mChildren[i] , scene);
    }
    printf("Finished processing node\n");
}

std::unique_ptr<Mesh> Model::ProcessMesh(aiMesh* mesh , const aiScene* scene)
{
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    std::vector<std::shared_ptr<Texture2D>> textures;

    // Process vertices
    printf("Processing %d vertices\n" , mesh->mNumVertices);
    for(unsigned int i = 0; i < mesh->mNumVertices; i++){
        Vertex vertex;
        // Process vertex positions
        vertex.position = glm::vec3(mesh->mVertices[i].x , mesh->mVertices[i].y , mesh->mVertices[i].z);

        // Process vertex normals
        if(mesh->HasNormals()){
            vertex.normal = glm::vec3(mesh->mNormals[i].x , mesh->mNormals[i].y , mesh->mNormals[i].z);
        }

        // Process color
        if(mesh->mMaterialIndex >= 0){
            aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
            aiColor4D color = aiColor4D(0.0f , 0.0f , 0.0f , 0.0f);
            aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE, &color);
            vertex.color = glm::vec4(color.r , color.g , color.b , color.a);
        }

        // Process vertex texture coordinates
        if(mesh->HasTextureCoords(0)){
            vertex.textureUV = glm::vec2(mesh->mTextureCoords[0][i].x ,1 - mesh->mTextureCoords[0][i].y);
        } else {
            vertex.textureUV = glm::vec2(0.0f , 0.0f);
        }

        vertices.push_back(vertex);
    }

    // Process indices
    printf("Processing %d faces\n" , mesh->mNumFaces);
    for(unsigned int i = 0; i < mesh->mNumFaces; i++){
        aiFace face = mesh->mFaces[i];
        for(unsigned int j = 0; j < face.mNumIndices; j++){
            indices.push_back(face.mIndices[j]);
        }
    }

    // Process material
    //comming soon...

    //Process color
    

    // Process diffuse textures
    if(mesh->mMaterialIndex >= 0){
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
        std::vector<std::shared_ptr<Texture2D>> diffuseMaps = LoadMaterialTextures(scene , material , aiTextureType_DIFFUSE , TextureType::DIFFUSE);
        textures.insert(textures.end() , diffuseMaps.begin() , diffuseMaps.end());
    }

    // Process specular textures
    if(mesh->mMaterialIndex >= 0){
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
        std::vector<std::shared_ptr<Texture2D>> specularMaps = LoadMaterialTextures(scene , material , aiTextureType_SPECULAR , TextureType::SPECULAR);
        textures.insert(textures.end() , specularMaps.begin() , specularMaps.end());
    }
    
    printf("New mesh with %d vertices, %d indices\n" , vertices.size() , indices.size());
    return std::make_unique<Mesh>(vertices , indices , textures);

}

std::vector<std::shared_ptr<Texture2D>> Model::LoadMaterialTextures(const aiScene* scene , aiMaterial* mat , aiTextureType type , TextureType textureType){
    std::vector<std::shared_ptr<Texture2D>> textures;
    unsigned int count = mat->GetTextureCount(type);
    printf("Found %d textures\n" , count);
    for(unsigned int i = 0; i < count; i++){
        aiString texturePath;
        mat->GetTexture(type , i , &texturePath);
        // Check if texture is embedded
        if(texturePath.C_Str()[0] == '*'){
            printf("Texture is embedded\n");
            const aiTexture* texture = scene->GetEmbeddedTexture(texturePath.C_Str());
            if(texture){
                printf("Creating embedded texture %s of type %c%c%c\n" , texture->mFilename.C_Str() , texture->achFormatHint[0] , texture->achFormatHint[1] , texture->achFormatHint[2]);
                //Get number of channels
                int nChannels = 4; //Assimp uses RGBA8888
                int width = texture->mWidth;
                int height = texture->mHeight;
                unsigned char* bytes = (unsigned char*)texture->pcData;
                // Check if texture is compressed
                if(height == 0){
                    bytes = stbi_load_from_memory(bytes , texture->mWidth , &width , &height , &nChannels , 0);
                }
                std::shared_ptr<Texture2D> texturePtr = std::make_shared<Texture2D>(bytes , width , height , nChannels , textureType);
                textures.push_back(texturePtr);
                continue;
            } else{
                printf("Texture appears not to be embedded\n");
            }
        }
        const std::string fullPath = path + "/../" + texturePath.C_Str();
        printf("Creating texture: %s\n" , fullPath.c_str());
        std::shared_ptr<Texture2D> texturePtr = std::make_shared<Texture2D>(fullPath , textureType , 0);
        textures.push_back(texturePtr);
    }
    return textures;
}


}
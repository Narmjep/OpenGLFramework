#include "Mesh.h"
#include "debugging.hpp"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtx/rotate_vector.hpp>
#include <gtx/vector_angle.hpp>
#include <gtc/type_ptr.hpp>

using namespace MyGL;

Mesh::Mesh(const std::vector<Vertex> vertices , std::vector<GLuint> indices ,std::vector<std::shared_ptr<Texture2D>> textures){
    //this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;
    
    vb = new VertexBuffer(vertices);
    eb = new ElementBuffer(indices);
    vertexArray.Bind();
    vertexArray.LinkAttrib(*vb , 0 , 3 , GL_FLOAT , sizeof(Vertex) , (void*)0);     	                   // Position
    vertexArray.LinkAttrib(*vb , 1 , 3 , GL_FLOAT , sizeof(Vertex) , (void*)(3 * sizeof(GL_FLOAT)));       // Normals
    vertexArray.LinkAttrib(*vb , 2 , 3 , GL_FLOAT , sizeof(Vertex) , (void*)(6 * sizeof(GL_FLOAT)));       // Colors
    vertexArray.LinkAttrib(*vb , 3 , 2 , GL_FLOAT , sizeof(Vertex) , (void*)(9 * sizeof(GL_FLOAT)));       // Texture coords

    vb->Unbind();
    eb->Unbind();
    vertexArray.Unbind();
}

Mesh::Mesh(const Mesh&){
    //printf("Mesh has been copied!\n");
}

Mesh::~Mesh(){
    //std::cout << "Mesh has been destroyed\n";
}


void Mesh::Draw(Shader& shader, const glm::mat4& model ,const glm::vec3& translation, const glm::vec3& rotation, const glm::vec3& scale){
    shader.Use(); //2nd time

    this->vertexArray.Bind();

    uint32_t numDiffuseTextures = 0;
    uint32_t numSpecularTextures = 0;

    Texture2D::Unbind();
    for(int i = 0; i < textures.size(); i++){
        std::string num;
        std::string typeName;
        switch(textures[i]->type){
            case TextureType::DIFFUSE:
                typeName = "diffuse";
                num = std::to_string(numDiffuseTextures++);
                break;
            case TextureType::SPECULAR:
                typeName = "specular";
                num = std::to_string(numSpecularTextures++);
                break;
        }
        textures[i]->AssignTextureUnit(shader , (typeName+num).c_str() , i);
        textures[i]->Bind();
    }

    //Apply tranfomations
    glm::mat4 translationMatrix = glm::mat4(1);
    glm::mat4 rotationMatrix = glm::mat4(1);
    glm::mat4 scaleMatrix = glm::mat4(1);

    translationMatrix = glm::translate(translationMatrix , translation);
    rotationMatrix = glm::translate(rotationMatrix , rotation);
    scaleMatrix = glm::translate(scaleMatrix , scale);

    GLDbgCall(glUniformMatrix4fv(GLDbgGetUniformLocation(shader , "translation") , 1 , GL_FALSE , glm::value_ptr(translationMatrix)));
    GLDbgCall(glUniformMatrix4fv(GLDbgGetUniformLocation(shader , "rotation") , 1 , GL_FALSE , glm::value_ptr(rotationMatrix)));
    GLDbgCall(glUniformMatrix4fv(GLDbgGetUniformLocation(shader , "scale") , 1 , GL_FALSE , glm::value_ptr(scaleMatrix)));
    GLDbgCall(glUniformMatrix4fv(GLDbgGetUniformLocation(shader , "model") , 1 , GL_FALSE , glm::value_ptr(model)));

    GLDbgCall(glDrawElements(GL_TRIANGLES, indices.size() , GL_UNSIGNED_INT , indices.data()));

    vertexArray.Unbind();
}

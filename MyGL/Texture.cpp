#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION 
#include "stb_image.h"
#include <iostream>
#include <fstream>
#include "debugging.hpp"

using namespace MyGL;

Texture2D::Texture2D(const std::string& path , TextureType type, GLuint slot , GLint resizeAlgorithm, GLint repetitionAlgorithm)
{
    this->path = path;
    this->type = type;
    //Check if file exists
    std::ifstream file(path);
    if(!file.good()){
        std::cerr << "Couldnt find " << path << ". This texture failed to initialize\n";
        file.close();
        return;
    }
    file.close();
    //Create Texture2D
    GLDbgCall(glGenTextures(1,&id));
    GLDbgCall(glActiveTexture(GL_TEXTURE0 + slot));
    textureUnit = slot;
    GLDbgCall(glBindTexture(GL_TEXTURE_2D , id));
    //Set algorithms
    //  Repetition
    GLDbgCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, repetitionAlgorithm));
    GLDbgCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, repetitionAlgorithm));
    //Resizing
    switch(resizeAlgorithm){
        case GL_NEAREST:
            GLDbgCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST_MIPMAP_NEAREST));
            break;
        case GL_LINEAR:
            GLDbgCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST_MIPMAP_LINEAR));
            break;
    }
    GLDbgCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,resizeAlgorithm)); //! 500
    //Load Image
    stbi_set_flip_vertically_on_load(true);
    int width, height, nClrChannels;
    unsigned char* bytes = stbi_load(path.c_str(),&width,&height,&nClrChannels,0);
    if (bytes == nullptr) {
        std::cerr << "Failed to load image " << path << " with the reason: " << stbi_failure_reason() << '\n';
        return;
    }
    //Find image type
    switch(nClrChannels){
        case 4:
            GLDbgCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width , height , 0 , GL_RGBA , GL_UNSIGNED_BYTE , bytes));
            break;
        case 3:
            GLDbgCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width , height , 0 , GL_RGB , GL_UNSIGNED_BYTE , bytes));
            break;
        case 1:
            GLDbgCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width , height , 0 , GL_RED , GL_UNSIGNED_BYTE , bytes));
            break;
        default:
            throw std::invalid_argument("The image " + path + " has an unusual ammount of channels. Failed to create the texture!");
            return;
            break;
    }
    //Mipmaps
    GLDbgCall(glGenerateMipmap(GL_TEXTURE_2D));
    //Free image
    stbi_image_free(bytes);
    Unbind();

}

Texture2D::Texture2D(unsigned char* imageData , int width , int height , int nChannels , TextureType type, GLuint slot , GLint resizeAlgorithm, GLint repetitionAlgorithm)
{
    this->type = type;
    //Create Texture2D
    GLDbgCall(glGenTextures(1,&id));
    GLDbgCall(glActiveTexture(GL_TEXTURE0 + slot));
    textureUnit = slot;
    GLDbgCall(glBindTexture(GL_TEXTURE_2D , id));
    //Set algorithms
    //  Repetition
    GLDbgCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, repetitionAlgorithm));
    GLDbgCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, repetitionAlgorithm));
    //Resizing
    switch(resizeAlgorithm){
        case GL_NEAREST:
            GLDbgCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST_MIPMAP_NEAREST));
            break;
        case GL_LINEAR:
            GLDbgCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST_MIPMAP_LINEAR));
            break;
    }
    GLDbgCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,resizeAlgorithm)); //! 500
    //Load Image
    //Find image type
    switch(nChannels){
        case 4:
            GLDbgCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width , height , 0 , GL_RGBA , GL_UNSIGNED_BYTE , imageData));
            break;
        case 3:
            GLDbgCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width , height , 0 , GL_RGB , GL_UNSIGNED_BYTE , imageData));
            break;
        case 1:
            GLDbgCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width , height , 0 , GL_RED , GL_UNSIGNED_BYTE , imageData));
            break;
        default:
            throw std::invalid_argument("The image has an unusual ammount of channels. Failed to create the texture!");
            return;
            break;
    }
    //Mipmaps
    GLDbgCall(glGenerateMipmap(GL_TEXTURE_2D));
    //Free image
    Unbind();
}

Texture2D::~Texture2D(){
    GLDbgCall(glDeleteTextures(1,&id));
}

void Texture2D::Bind(){
    GLDbgCall(glActiveTexture(GL_TEXTURE0 + textureUnit));
    GLDbgCall(glBindTexture(GL_TEXTURE_2D , id));
}

void Texture2D::Unbind(){
    GLDbgCall(glBindTexture(GL_TEXTURE_2D , 0));
}

void Texture2D::AssignTextureUnit(Shader& program , const char* uniform , GLuint unit){
    textureUnit = unit;
    GLDbgCall(GLuint textUniform = GLDbgGetUniformLocation(program, uniform));
    program.Use();
    GLDbgCall(glUniform1i(textUniform ,  textureUnit));
}


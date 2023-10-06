#pragma once
#include "opengl.h"
#include <debugging.hpp>
#include <Shader.h>
#include <ElementBuffer.h>
#include <VertexArray.h>
#include <VertexBuffer.h>
#include <Texture.h>
#include <Mesh.h>
#include <Camera.h>
#include <Model.h>
//#include <Model.h>
#include <fstream>


inline std::string GetFileContent(const std::string& path){
    std::ifstream file(path , std::ios::binary);
    if(!file.good()){
        throw std::invalid_argument("File \'" + path + "\' not found!");
    }
    std::string data((std::istreambuf_iterator<char>(file)),
                    (std::istreambuf_iterator<char>()));
    return data;
}

#ifndef TEXTURE_H
#define TEXTURE_H

#include <opengl.h>
#include "Shader.h"
#include "MyGLAPI.h"

namespace MyGL{

enum MyGLAPI TextureType{
	DIFFUSE,
	SPECULAR,
};

class MyGLAPI Texture2D
{
public:
	TextureType type;
	/**
	 * @brief Create a Texture2D.
	 * 
	 * @param path to the image
	 * @param texType the texture type (eg. GL_TEXTURE_2D)
	 * @param slot texture slot in your gpu
	 * @param pixelType 
	 * @param resizeAlgorithm 
	 * @param repetitionAlgorithm 
	 * 
	 */
	Texture2D(const std::string& path , TextureType type,  GLenum slot = 0 , GLint resizeAlgorithm = GL_NEAREST, GLint repetitionAlgorithm = GL_REPEAT);
	Texture2D(unsigned char* imageData , int width , int height , int nChannels, TextureType type, GLenum slot = 0 , GLint resizeAlgorithm = GL_NEAREST, GLint repetitionAlgorithm = GL_REPEAT);
	//Texture2D(const Texture2D&)=delete;
	~Texture2D();
	void Bind();
	static void Unbind();
	void AssignTextureUnit(Shader& program , const char* uniform , GLuint unit);
private:
	GLuint id;
	GLuint textureUnit;
	std::string path;
};


}

#endif // TEXTURE_H
#ifndef SHADER_H
#define SHADER_H
#include <string>
#include <vector>
#include <opengl.h>
#include "MyGLAPI.h"


namespace MyGL{

/**
 * @brief Shader used to be loaded into a ShaderProgram
 * 
 */
class MyGLAPI Shader
{
public:
	static bool throwExceptionOnCompileError;
	/// @brief Create a Shader object
	/// @param path The path to your shader file
	/// @param type The type of the shader
	Shader(const std::string& vertexShaderPath , const std::string& fargmentShaderPath );
	~Shader();
	void Use();
	//Getters
	inline GLuint GetShaderID(){return shaderID;}
	inline const std::string GetVertexShaderPath(){return vertexShaderPath;}
	inline const std::string GetFragmentShaderPath(){return fragmentShaderPath;}
private:
	const std::string vertexShaderPath;
	const std::string fragmentShaderPath;
	GLuint shaderID = 0;
	void CompileProgram(GLuint shaderID);

};
}

#endif // SHADER_H
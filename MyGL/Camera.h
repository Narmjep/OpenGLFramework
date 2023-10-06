#pragma once

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtx/rotate_vector.hpp>
#include <gtx/vector_angle.hpp>
#include <gtc/type_ptr.hpp>
#include "MyGL.h"
#include "MyGLAPI.h"

namespace MyGL{

class MyGLAPI Camera
{
public:
	glm::vec3 position= glm::vec3(0, 0 ,0);;
	glm::vec3 orientation = glm::vec3(0,0,-1);
	const glm::vec3 upDirection = glm::vec3(0,1.0,0);

	//Settings
	int width;
	int height;
	float aspectRatio;
	float nearClip;
	float farClip;
	
	float speed = 0.001f;
	float sensitivity = 100.0f;
	float FOV = 45.0;

	glm::mat4 cameraMatrix;

	Camera(int width , int height , float aspectRatio , float nearClip = 0.1f , float farClip = 100.0f);
	~Camera() = default;
	void UpdateMatrix();
	void ExportMatrix(MyGL::Shader& shaderprogram , const char* uniform);
	void HandleInputs(GLFWwindow* window);

	private:
		bool firstLeftMouseClick = true;
		
		bool firstRClick = true;
};


}

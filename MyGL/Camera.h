#pragma once

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtx/rotate_vector.hpp>
#include <gtx/vector_angle.hpp>
#include <gtc/type_ptr.hpp>
#include "MyGL.h"
#include "MyGLAPI.h"

namespace MyGL{

class MyGLAPI Camera{
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
	float FOV = 90.0;
	

	Camera(int width , int height , float aspectRatio , float nearClip = 0.1f , float farClip = 100.0f);
	~Camera() = default;
	/// @brief Recalculates the projection, view and camera matrix
	void UpdateMatrices();
	/// @brief Sets the uniform matrix of the shader to the projection * view matrix of this camera
	/// @param shaderprogram The shader program to set the uniform matrix to
	/// @param uniform The name of the uniform matrix in the shader
	void ExportMatrix(MyGL::Shader& shaderprogram , const char* uniform);
	/// @brief Moves the camera based on the input
	/// @param window The window to receive input from
	void HandleInputs(GLFWwindow* window);
	/// @brief Returns the view matrix of this camera
	/// @return 
	glm::mat4 GetViewMatrix(){return viewMatrix;}
	/// @brief Returns the projection matrix of this camera
	glm::mat4 GetProjectionMatrix(){return projectionMatrix;}
	/// @brief Returns the projection * view matrix of this camera
	glm::mat4 GetCameraMatrix(){return cameraMatrix;}

	private:
		glm::mat4 cameraMatrix;
		glm::mat4 projectionMatrix;
		glm::mat4 viewMatrix;
		bool firstLeftMouseClick = true;
		bool firstRClick = true;
};

}
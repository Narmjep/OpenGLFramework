#include "Camera.h"
#include "debugging.hpp"

using namespace MyGL;

Camera::Camera(int width , int height , float aspectRatio , float nearClip , float farClip)
{
    this->width = width;
    this->height = height; 
    this->nearClip = nearClip;
    this->farClip = farClip;
    this->aspectRatio = aspectRatio;
    UpdateMatrices();
}

void Camera::UpdateMatrices(){
    viewMatrix = glm::lookAt(position, position + orientation , upDirection);
    projectionMatrix = glm::perspective(glm::radians(FOV) , aspectRatio , nearClip , farClip);
    cameraMatrix = projectionMatrix * viewMatrix;
}

void Camera::ExportMatrix(MyGL::Shader& shaderProgram , const char* uniform){
    glUniformMatrix4fv(GLDbgGetUniformLocation(shaderProgram , uniform) , 1 , GL_FALSE , glm::value_ptr(cameraMatrix));
}

void Camera::HandleInputs(GLFWwindow* window){
    //Keys
    //  W 
    if(glfwGetKey(window , GLFW_KEY_W) == GLFW_PRESS){
        position += orientation * speed;
    }
    //  A 
    if(glfwGetKey(window , GLFW_KEY_A) == GLFW_PRESS){
        position -= glm::normalize(glm::cross(orientation, upDirection)) * speed;
    }
    //  S 
    if(glfwGetKey(window , GLFW_KEY_S) == GLFW_PRESS){
        position -= orientation * speed;
    }
    //  D 
    if(glfwGetKey(window , GLFW_KEY_D) == GLFW_PRESS){
        position += glm::normalize(glm::cross(orientation, upDirection)) * speed;

    }
    


    //Additional key input
    //  Rotate pyramid
    // Q
    if(glfwGetKey(window , GLFW_KEY_Q) == GLFW_PRESS){
        position += upDirection * speed;
    }
    // E
    if(glfwGetKey(window , GLFW_KEY_E) == GLFW_PRESS){
        position -=  upDirection * speed;
    }

    //Turning
    //  Cursor
    if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS){
        glfwSetInputMode(window , GLFW_CURSOR , GLFW_CURSOR_HIDDEN);

        if(firstLeftMouseClick){
            glfwSetCursorPos(window , width / 2 , height / 2);
            firstLeftMouseClick = false;
        }
        //  rotate
        double mouseX, mouseY;
        glfwGetCursorPos(window , &mouseX , &mouseY);

        float rotationX = sensitivity * (float)(mouseY - (height / 2 )) / height;
        float rotationY = sensitivity * (float)(mouseX - (width / 2)) / width;

        orientation  = glm::rotate(orientation , glm::radians(-rotationX) , glm::normalize(glm::cross(orientation , upDirection))); //vertical rotation
        orientation = glm::rotate(orientation , glm::radians(-rotationY) , upDirection); //horizontal rotation
        glfwSetCursorPos(window , width / 2 , height / 2);
    }
     else if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE){
        glfwSetInputMode(window , GLFW_CURSOR , GLFW_CURSOR_NORMAL);
        firstLeftMouseClick = true;
    }
}
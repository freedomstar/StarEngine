#include "Camera.h"
#include "Time.h"



Camera::Camera(glm::vec3 postition, glm::vec3 cameraFront, float fov, float aspectRatio, float nearDistance, float farDistance)
{
	firstMouse = true;
	yaw = -90.0f;
	pitch = 0.0f;
	this->postition = postition;
	this->cameraFront = cameraFront;
	glm::vec3 Right = glm::normalize(glm::cross(cameraFront, worldUpVec));
	cameraUp = glm::normalize(glm::cross(Right, cameraFront));
	viewMatrix = glm::lookAt(postition, postition + cameraFront, cameraUp);
	projectionMatrix = glm::perspective(glm::radians(fov), aspectRatio, nearDistance, farDistance);
}

void Camera :: mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (!glfwGetMouseButton(window, 0)) 
	{
		firstMouse = true;
		return;
	}
	if (glfwGetMouseButton(window, 0) && firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.05;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(front);
	//updateViewMatrix();
}

void Camera::processInput(GLFWwindow *window)
{

	float cameraSpeed = 2.0f*Time::deltaTime; 
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		postition += cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		postition -= cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		postition -= glm::normalize(glm::cross(cameraFront, worldUpVec)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		postition += glm::normalize(glm::cross(cameraFront, worldUpVec)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		postition -= worldUpVec * cameraSpeed;	
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		postition += worldUpVec * cameraSpeed;
}

void Camera::updateViewMatrix() 
{
	glm::vec3 Right = glm::normalize(glm::cross(cameraFront, worldUpVec));
	cameraUp = glm::normalize(glm::cross(Right, cameraFront));
	viewMatrix = glm::lookAt(postition, postition + cameraFront, cameraUp);
}

Camera::~Camera()
{
}

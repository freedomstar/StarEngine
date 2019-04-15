#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h> 

class Camera
{
public:
	glm::vec3 postition;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;
	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;
	Camera(glm::vec3 postition, glm::vec3 cameraFront,float fov,float aspectRatio, float nearDistance, float farDistance);
	void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	void updateViewMatrix();
	void processInput(GLFWwindow *window);
	~Camera();
private:
	const glm::vec3 worldUpVec = glm::vec3(0.0f, 1.0f, 0.0f);
	bool firstMouse;
	float lastX, lastY, yaw, pitch;

};


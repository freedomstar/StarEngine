#pragma once
#include "Define.h"
#include <queue>
#include <atomic>

class SBaseWindow;
class GLFWwindow;

struct DrawCallData
{
	char* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";
	char* fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\n\0";
	std::vector<float> vertices = {
		0.5f,  0.5f, 0.0f,  // top right
		0.5f, -0.5f, 0.0f,  // bottom right
	   -0.5f, -0.5f, 0.0f,  // bottom left
	   -0.5f,  0.5f, 0.0f   // top left
	};
	std::vector<uint32> indices = {  // note that we start from 0!
	0, 1, 3,  // first Triangle
	1, 2, 3   // second Triangle
	};
};

class SRender
{
public:
	SRender();
	virtual ~SRender();
	void Init();
	void Run();
	SBaseWindow* baseWindow = nullptr;
	GLFWwindow* glfwWindow = nullptr;
	//std::atomic<std::queue<DrawCallData>> DrawList;

private:
	void OpenglInit();
	void DirectX12Init();
	void Tick();
	void RenderDrawCall(const DrawCallData& Data);
};

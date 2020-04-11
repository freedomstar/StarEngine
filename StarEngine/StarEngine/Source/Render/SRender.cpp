#include "SRender.h"
#include <GLFW/glfw3.h>
#include "Runtime/SBaseWindow/SBaseWindowMgr.h"

SRender::SRender()
{
}

SRender::~SRender()
{
}

void SRender::Init()
{
	OpenglInit();
}

void SRender::OpenglInit()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#if __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
}

void SRender::DirectX12Init()
{
}

void SRender::Run()
{
	while (true)
	{
		Tick();
	}
}

void SRender::Tick()
{
}
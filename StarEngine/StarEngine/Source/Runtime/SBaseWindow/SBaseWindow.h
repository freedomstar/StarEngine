#pragma once
#include "../../Core/SObject/SObject.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Editor/SWindow/MainEditorWindow.h"

struct BaseWindowInputAction
{
	int32 key = 0;
	int32 action = 0;
	std::function<void()> callBackFuntion;
};

class SBaseWindow :public SObject
{
public:
	SBaseWindow();
	virtual ~SBaseWindow();
	bool CreateBaseWindow(char* WindowName, int32 Width, int32 Height);
	bool CreateBaseWindow(char* WindowName);
	bool CreateGlfwWindow(char* WindowName, int32 Width, int32 Height);
	virtual void Tick(float DeltaTime) override;
	void ProcessInput();
	void RegisterAction(int32 key, int32 action, std::function<void()> callBackFuntion);
	void GlfwTick(float DeltaTime);
	void Close();
	bool IsColse();
	std::list<BaseWindowInputAction> InputActionList;
	void ImguiInit();
	int32 WindowWidth, WindowHeight;
private:
	GLFWwindow* glfwWindow = nullptr;
	MainEditorWindow* mainEditorWindow;
	bool bClose = false;
};

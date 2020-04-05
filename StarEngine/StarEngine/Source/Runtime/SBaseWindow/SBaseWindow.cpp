#include "SBaseWindow.h"
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"

SBaseWindow::SBaseWindow()
{
}

SBaseWindow::~SBaseWindow()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();
	glfwDestroyWindow(glfwWindow);
	delete glfwWindow;
}

bool SBaseWindow::CreateBaseWindow(char* WindowName, int32 Width, int32 Height)
{
	if (CreateGlfwWindow(WindowName, Width, Height))
	{
		glfwMakeContextCurrent(glfwWindow);
		this->AddToRoot();
		return true;
	}
	return false;
}

static int32 ScreenWidth;
static int32 ScreenHeight;

bool SBaseWindow::CreateBaseWindow(char* WindowName)
{
	GLFWmonitor* pMonitor = glfwGetPrimaryMonitor();
	if (!pMonitor)
	{
		std::cout << "Failed to create GLFW window, pMonitor Is NUll" << std::endl;
		return false;
	}
	const GLFWvidmode* mode = glfwGetVideoMode(pMonitor);
	if (!mode)
	{
		std::cout << "Failed to create GLFW window, mode Is NUll" << std::endl;
		return false;
	}
	if (CreateGlfwWindow(WindowName, mode->width, mode->height))
	{
		ScreenWidth = mode->width;
		ScreenHeight = mode->height;
		this->AddToRoot();
		return true;
	}
	return false;
}

bool SBaseWindow::CreateGlfwWindow(char* WindowName, int32 Width, int32 Height)
{
	glfwWindow = glfwCreateWindow(Width, Height, WindowName, NULL, NULL);
	if (glfwWindow == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		return false;
	}
	glfwMakeContextCurrent(glfwWindow);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return false;
	}
	ImguiInit();
}

void SBaseWindow::Tick(float DeltaTime)
{
	if (bClose)
	{
		return;
	}
	this->SObject::Tick(DeltaTime);
	GlfwTick(DeltaTime);
}

void SBaseWindow::GlfwTick(float DeltaTime)
{
	if (!glfwWindow)
	{
		return;
	}
	if (glfwWindowShouldClose(glfwWindow))
	{
		bClose = true;
		glfwDestroyWindow(glfwWindow);
		this->Destroy();
		return;
	}
	ProcessInput();
	glfwPollEvents();
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	int32 width, height;
	glfwGetFramebufferSize(glfwWindow, &width, &height);
	ImGui::Begin("Splitter test", 0, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoScrollbar);
	ImGui::SetWindowSize(ImVec2(width, height));
	ImGui::SetWindowPos(ImVec2(0, 0));
	ImGui::BeginMenuBar();
	ImGui::MenuItem("File");
	ImGui::MenuItem("Tool");
	ImGui::MenuItem("Setting");
	ImGui::EndMenuBar();
	ImGui::BeginChild("child1", ImVec2(width, 50), true);
	ImGui::SetWindowPos(ImVec2(0, 0));
	ImGui::EndChild();
	ImGui::BeginGroup();
	static float w = 200.0f;
	static float h = 300.0f;
	static float rw = 300.0f;
	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
	ImGui::BeginChild("childo1", ImVec2(w, h), true);
	ImGui::EndChild();
	ImGui::SameLine();
	ImGui::InvisibleButton("vsplitter", ImVec2(8.0f, h));
	if (ImGui::IsItemActive()) {
		w += ImGui::GetIO().MouseDelta.x;
		rw -= ImGui::GetIO().MouseDelta.x;
	}
	ImGui::SameLine();
	ImGui::BeginChild("child2", ImVec2(rw, h), true);
	ImGui::EndChild();
	ImGui::SameLine();
	ImGui::InvisibleButton("vsplittesr", ImVec2(8.0f, h));
	if (ImGui::IsItemActive())
		rw += ImGui::GetIO().MouseDelta.x;
	ImGui::SameLine();
	ImGui::BeginChild("childf2", ImVec2(0, h), true);
	ImGui::EndChild();
	ImGui::InvisibleButton("hsplitter", ImVec2(-1, 8.0f));
	if (ImGui::IsItemActive())
		h += ImGui::GetIO().MouseDelta.y;
	ImGui::BeginChild("child3", ImVec2(0, 0), true);
	ImGui::EndChild();
	ImGui::PopStyleVar();
	ImGui::EndGroup();

	ImGui::End();

	ImGui::Render();

	int display_w, display_h;
	glfwGetFramebufferSize(glfwWindow, &display_w, &display_h);
	glViewport(0, 0, display_w, display_h);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	glfwSwapBuffers(glfwWindow);
}

void SBaseWindow::ImguiInit()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(glfwWindow, true);
	ImGui_ImplOpenGL3_Init("#version 330 core");
}

void SBaseWindow::ProcessInput()
{
	if (!glfwWindow)
	{
		return;
	}
	static std::list<BaseWindowInputAction>::iterator iter;
	for (iter = InputActionList.begin(); iter != InputActionList.end();)
	{
		if (glfwGetKey(glfwWindow, (*iter).key) == (*iter).action)
		{
			(*iter).callBackFuntion();
		}
		iter++;
	}
}

void SBaseWindow::RegisterAction(int32 key, int32 action, std::function<void()> callBackFuntion)
{
	BaseWindowInputAction Action;
	Action.key = key;
	Action.action = action;
	Action.callBackFuntion = callBackFuntion;
	InputActionList.push_back(Action);
}

void SBaseWindow::Close()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwSetWindowShouldClose(glfwWindow, true);
	bClose = true;
}

bool SBaseWindow::IsColse()
{
	return bClose;
}
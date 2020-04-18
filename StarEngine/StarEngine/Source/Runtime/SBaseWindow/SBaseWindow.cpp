#include "SBaseWindow.h"
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"
#include "Runtime/SBaseWindow/SBaseWindowMgr.h"

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
	delete mainEditorWindow;
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
		//SBaseWindowMgr::ScreenWidth = mode->width;
		//SBaseWindowMgr::ScreenHeight = mode->height;
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
	return true;
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
	if (mainEditorWindow && !mainEditorWindow->ChangeLayoutFunList.empty())
	{
		std::list<std::function<void()>>::iterator fiter;
		for (fiter = mainEditorWindow->ChangeLayoutFunList.begin(); fiter != mainEditorWindow->ChangeLayoutFunList.end();)
		{
			(*fiter)();
			fiter++;
		}
		mainEditorWindow->ChangeLayoutFunList.clear();
	}
	ProcessInput();
	glfwPollEvents();
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	if (mainEditorWindow)
	{
		mainEditorWindow->Draw();
	}
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
	mainEditorWindow = new MainEditorWindow();
	if (mainEditorWindow)
	{
		glfwGetFramebufferSize(glfwWindow, &WindowWidth, &WindowHeight);
		mainEditorWindow->width = WindowWidth;
		mainEditorWindow->height = WindowHeight;
		mainEditorWindow->SetWindowName("StarEngineMainEditorWindow");
		mainEditorWindow->bRoot = true;
		SLayoutWindow* LayoutWindow2 = new SLayoutWindow();
		STabItem* Item1 = new STabItem();
		LayoutWindow2->addTab(Item1);

		SLayoutWindow* LayoutWindow3 = new SLayoutWindow();
		STabItem* Item2 = new STabItem();
		LayoutWindow3->addTab(Item2);

		SLayoutWindow* LayoutWindow4 = new SLayoutWindow();
		STabItem* Item3 = new STabItem();
		LayoutWindow4->addTab(Item3);

		SLayoutWindow* LayoutWindow5 = new SLayoutWindow();
		STabItem* Item4 = new STabItem();
		LayoutWindow5->addTab(Item4);

		SLayoutWindow* LayoutWindow6 = new SLayoutWindow();
		STabItem* Item5 = new STabItem();
		LayoutWindow6->addTab(Item5);

		SLayoutWindow* LayoutWindow7 = new SLayoutWindow();
		STabItem* Item6 = new STabItem();
		LayoutWindow7->addTab(Item6);

		mainEditorWindow->AddLayoutWindow(LayoutWindow2, 0, 0, true, true, true);
		mainEditorWindow->AddLayoutWindow(LayoutWindow3, 0, 0, false, false, true);
		mainEditorWindow->AddLayoutWindow(LayoutWindow4, 0, 0, true, false, false);
		mainEditorWindow->AddLayoutWindow(LayoutWindow5, 0, 1, true, false, true);
		mainEditorWindow->AddLayoutWindow(LayoutWindow6, 0, 0, false, true, true);
		mainEditorWindow->AddLayoutWindow(LayoutWindow7, 1, 0, true, true, false);
		mainEditorWindow->MoveLayoutWindow(LayoutWindow7, LayoutWindow5, true, true, true);
	}
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
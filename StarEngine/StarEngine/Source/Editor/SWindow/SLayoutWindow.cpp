#include "SLayoutWindow.h"
#include "imgui.h"
#include <sstream>

int32 SLayoutWindow::LayOutWindowIndex = 0;

SLayoutWindow::SLayoutWindow()
{
	SLayoutWindow::LayOutWindowIndex++;
	std::ostringstream WName;
	WName << "LayoutWindow" << SLayoutWindow::LayOutWindowIndex;
	WindowName = WName.str();
}

SLayoutWindow::~SLayoutWindow()
{
}

void SLayoutWindow::Draw(float lineheight, bool bLastHorizontal, float SplitterWidth)
{
	SWindow::Draw();
	if (bLastHorizontal)
	{
		ImGui::BeginChild(WindowName.data(), ImVec2(width - 15 - SplitterWidth, lineheight), true);
	}
	else
	{
		ImGui::BeginChild(WindowName.data(), ImVec2(width, lineheight), true);
	}
	//ImGui::SetWindowPos(ImVec2(0, 0));
	ImGui::EndChild();
	//ImGui::Begin("Splitter test", 0, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoScrollbar);
//ImGui::SetWindowSize(ImVec2(width, height));
//ImGui::SetWindowPos(ImVec2(0, 0));
//ImGui::BeginMenuBar();
//ImGui::MenuItem("File");
//ImGui::MenuItem("Tool");
//ImGui::MenuItem("Setting");
//ImGui::EndMenuBar();
//ImGui::BeginChild("child1", ImVec2(width, 50), true);
//ImGui::SetWindowPos(ImVec2(0, 0));
//ImGui::EndChild();
//ImGui::BeginGroup();
//static float w = 200.0f;
//static float h = 300.0f;
//static float rw = 300.0f;
//ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
//ImGui::BeginChild("childo1", ImVec2(w, h), true);
//ImGui::EndChild();
//ImGui::SameLine();
//ImGui::InvisibleButton("vsplitter", ImVec2(8.0f, h));
//if (ImGui::IsItemActive()) {
//	w += ImGui::GetIO().MouseDelta.x;
//	rw -= ImGui::GetIO().MouseDelta.x;
//}
//ImGui::SameLine();
//ImGui::BeginChild("child2", ImVec2(rw, h), true);
//ImGui::EndChild();
//ImGui::SameLine();
//ImGui::InvisibleButton("vsplittesr", ImVec2(8.0f, h));
//if (ImGui::IsItemActive())
//	rw += ImGui::GetIO().MouseDelta.x;
//ImGui::SameLine();
//ImGui::BeginChild("childf2", ImVec2(0, h), true);
//ImGui::EndChild();
//ImGui::InvisibleButton("hsplitter", ImVec2(-1, 8.0f));
//if (ImGui::IsItemActive())
//	h += ImGui::GetIO().MouseDelta.y;
//ImGui::BeginChild("child3", ImVec2(0, 0), true);
//ImGui::EndChild();
//ImGui::PopStyleVar();
//ImGui::EndGroup();
	//ImGui::Begin("111");
	////ImGui::BeginChild("child1", ImVec2(100, 50), true);
	////ImGui::SetWindowPos(ImVec2(100, 100));
	//ImVec2 pos(0, 0);
	////ImGui::EndChild();
	//ImVec2 wpos = ImGui::GetWindowPos();
	//if (ImGui::BeginTabBar("##Tabs", ImGuiTabBarFlags_Reorderable))
	//{
	//	if (ImGui::BeginTabItem("Description"))
	//	{
	//		if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None)) {
	//			ImVec2 spos = ImGui::GetMousePos();
	//			pos = spos - wpos;
	//			ImGui::EndDragDropSource();
	//		}

	//		ImGui::TextWrapped("Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. ");
	//		ImGui::EndTabItem();
	//	}
	//	if (ImGui::BeginTabItem("Details"))
	//	{
	//		ImGui::Text("ID: 0123456789");
	//		ImGui::EndTabItem();
	//	}
	//	ImGui::EndTabBar();
	//}
	//if (ImGui::BeginTabBar("##T4abs", ImGuiTabBarFlags_Reorderable))
	//{
	//	if (ImGui::BeginTabItem("Desc6ription"))
	//	{
	//		ImGui::TextWrapped("Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. ");
	//		ImGui::EndTabItem();
	//	}
	//	if (ImGui::BeginTabItem("Deta6ils"))
	//	{
	//		ImGui::Text("ID: 01234566789");
	//		ImGui::EndTabItem();
	//	}
	//	ImGui::EndTabBar();
	//}
	//ImGui::Text("x:%f y:%f", pos.x, pos.y);
	//ImGui::End();
}
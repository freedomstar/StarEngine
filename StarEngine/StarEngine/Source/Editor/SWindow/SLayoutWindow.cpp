#include "SLayoutWindow.h"
#include "imgui.h"
#include <sstream>
#include "MainEditorWindow.h"

int32 SLayoutWindow::LayOutWindowIndex = 0;

SLayoutWindow::SLayoutWindow()
{
	SLayoutWindow::LayOutWindowIndex++;
	std::ostringstream WName;
	WName << "LayoutWindow" << SLayoutWindow::LayOutWindowIndex;
	WindowName = WName.str();
	std::ostringstream TName;
	TName << "##" << WindowName << "_Tabs";
	TabsName = TName.str();
	//TabItems.push_back(Item2);
}

void SLayoutWindow::addTab(STabItem* tab)
{
	tab->ParentLayoutWindow = this;
	TabItems.push_back(tab);
}

SLayoutWindow::~SLayoutWindow()
{
	static std::list<STabItem*>::iterator iter;
	for (iter = TabItems.begin(); iter != TabItems.end();)
	{
		if ((*iter))
		{
			delete* iter;
		}
	}
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
	if (ImGui::BeginTabBar(TabsName.data(), ImGuiTabBarFlags_Reorderable))
	{
		std::list<STabItem*>::iterator iter;
		for (iter = TabItems.begin(); iter != TabItems.end();)
		{
			if ((*iter)->ParentLayoutWindow)
			{
				(*iter)->LayoutRow = Row;
				(*iter)->LayoutColumn = Column;
				(*iter)->Draw();
			}
			iter++;
		}
		ImGui::EndTabBar();
	}

	ImGui::Text("%d %d", Row, Column);
	ImGui::Text(WindowName.data());
	ImVec2 MousePos = ImGui::GetMousePos();
	ImVec2 LayoutPos = ImGui::GetWindowPos();
	ImGui::Text("MousePos: %f %f  LayoutPos: %f %f", MousePos.x, MousePos.y, LayoutPos.x, LayoutPos.y);
	ImGui::EndChild();

	if (ImGui::BeginDragDropTarget())
	{
		if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("Drag_Tab_Item"))
		{
			IM_ASSERT(payload->DataSize == sizeof(DragItemData));
			DragItemData payload_n = *(DragItemData*)payload->Data;
			if (payload_n.item && payload_n.item->ParentLayoutWindow)
			{
				if (payload_n.item->ParentLayoutWindow == this && payload_n.item->ParentLayoutWindow->TabItems.size() <= 1)
				{
				}
				else
				{
					float LW = (float)width * 0.25f;
					float RW = (float)width * 0.75f;
					float TH = lineheight * 0.25f;
					float BH = lineheight * 0.75f;
					float RelativePosX = MousePos.x - LayoutPos.x;
					float RelativePosY = MousePos.y - LayoutPos.y;
					bool btop = false;
					bool baddRow = false;
					bool bfront = false;
					bool baddColumn = false;
					if (RelativePosX > 0 && RelativePosY > 0)
					{
						if (RelativePosX < LW)
						{
							baddColumn = true;
							bfront = true;
						}
						if (RelativePosX > RW)
						{
							baddColumn = true;
						}
						if (RelativePosY < TH && !baddColumn)
						{
							btop = true;
							baddRow = true;
						}
						if (RelativePosY > BH && !baddColumn)
						{
							baddRow = true;
						}
						if (baddColumn || baddRow)
						{
							auto fun = [=]() {
								//payload_n.item->ParentLayoutWindow->TabItems.remove(payload_n.item);
								if (payload_n.item->ParentLayoutWindow->TabItems.size() == 1)
								{
									payload_n.item->ParentLayoutWindow->mainEditorWindow->MoveLayoutWindow(payload_n.item->ParentLayoutWindow, this, bfront, baddRow, btop);
								}
								else
								{
									payload_n.item->ParentLayoutWindow->TabItems.remove(payload_n.item);
									if (payload_n.item->ParentLayoutWindow->TabItems.empty())
									{
										payload_n.item->ParentLayoutWindow->mainEditorWindow->DeleteLayoutWindow(payload_n.item->ParentLayoutWindow);
										payload_n.item->ParentLayoutWindow = nullptr;
									}
									SLayoutWindow* newLayoutWindows = new SLayoutWindow();
									newLayoutWindows->TabItems.push_back(payload_n.item);
									payload_n.item->ParentLayoutWindow = newLayoutWindows;
									this->mainEditorWindow->AddLayoutWindow(newLayoutWindows, this->Row, this->Column, bfront, baddRow, btop);
								}
							};
							this->mainEditorWindow->ChangeLayoutFunList.push_back(std::bind(fun));
						}
					}
				}
			}
		}
		ImGui::EndDragDropTarget();
	}
}
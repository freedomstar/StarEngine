#include "MainEditorWindow.h"
#include "imgui.h"
#include <sstream>

MainEditorWindow::MainEditorWindow()
{
}

MainEditorWindow::~MainEditorWindow()
{
}

void MainEditorWindow::RefreshRowAndColumn()
{
	static std::list<RowListLayoutData*>::iterator iter;
	static std::list<SLayoutWindow*>::iterator witer;
	int32 Row = 0;
	int32 Column = 0;
	for (iter = Layouts.begin(); iter != Layouts.end();)
	{
		if (*iter)
		{
			Column = 0;
			for (witer = (*iter)->LayoutList.begin(); witer != (*iter)->LayoutList.end();)
			{
				(*witer)->Row = Row;
				(*witer)->Column = Column;
				++witer;
				Column++;
			}
		}
		Row++;
		iter++;
	}
}

bool MainEditorWindow::RemoveLayoutWindow(SLayoutWindow* LayoutWindow)
{
	static std::list<RowListLayoutData*>::iterator iter;
	static std::list<SLayoutWindow*>::iterator witer;
	iter = Layouts.begin();
	std::advance(iter, LayoutWindow->Row);
	if (*iter)
	{
		(*iter)->LayoutList.remove(LayoutWindow);
	}

	if ((*iter)->LayoutList.size() <= 0)
	{
		int32 removeheight = (*iter)->Height;
		Layouts.remove(*iter);
		iter = Layouts.begin();
		if (LayoutWindow->Row > Layouts.size())
		{
			iter = Layouts.end();
		}
		else
		{
			std::advance(iter, LayoutWindow->Row);
		}

		if (iter == Layouts.end())
		{
			iter--;
		}
		(*iter)->Height += removeheight;
	}
	else
	{
		witer = (*iter)->LayoutList.begin();
		if (LayoutWindow->Column > (*iter)->LayoutList.size())
		{
			witer == (*iter)->LayoutList.end();
		}
		else
		{
			std::advance(witer, LayoutWindow->Column);
		}
		if (witer == (*iter)->LayoutList.end())
		{
			witer--;
		}
		(*witer)->width += LayoutWindow->width;
	}
	RefreshRowAndColumn();
	return true;
}

bool MainEditorWindow::DeleteLayoutWindow(SLayoutWindow* LayoutWindow)
{
	RemoveLayoutWindow(LayoutWindow);
	delete LayoutWindow;
	return true;
}

bool MainEditorWindow::MoveLayoutWindow(SLayoutWindow* LayoutWindow, SLayoutWindow* TargetLayoutWindow, bool bFront, bool bAddRow, bool bTop)
{
	RefreshRowAndColumn();
	RemoveLayoutWindow(LayoutWindow);
	AddLayoutWindow(LayoutWindow, TargetLayoutWindow->Row, TargetLayoutWindow->Column, bFront, bAddRow, bTop);
	return true;
}

bool MainEditorWindow::AddLayoutWindow(SLayoutWindow* LayoutWindow, int32 TargetRow, int32 TargetColumn, bool bFront, bool bAddRow, bool bTop)
{
	if (!LayoutWindow)
	{
		return false;
	}
	int32 LayoutsSize = (int32)Layouts.size();
	if (TargetRow - (LayoutsSize - 1) > 1)
	{
		return false;
	}
	RowListLayoutData* rowListLayoutData;
	static std::list<RowListLayoutData*>::iterator iter;
	if (bAddRow)
	{
		rowListLayoutData = new RowListLayoutData();
		if (Layouts.empty())
		{
			rowListLayoutData->Height = height;
			Layouts.push_back(rowListLayoutData);
		}
		else
		{
			if (TargetRow == LayoutsSize)
			{
				Layouts.push_back(rowListLayoutData);
				iter = Layouts.begin();
				std::advance(iter, TargetRow - 1);
			}
			else
			{
				iter = Layouts.begin();
				std::advance(iter, TargetRow);
				if (!bTop)
				{
					iter++;
				}
				if (iter == Layouts.end())
				{
					Layouts.push_back(rowListLayoutData);
				}
				else
				{
					Layouts.insert(iter, rowListLayoutData);
				}
				iter = Layouts.begin();
				std::advance(iter, TargetRow);
				if (bTop)
				{
					iter++;
				}
			}
			rowListLayoutData->Height = (*iter)->Height / 2;
			(*iter)->Height = rowListLayoutData->Height;
		}
	}
	else
	{
		iter = Layouts.begin();
		std::advance(iter, TargetRow);
		rowListLayoutData = *iter;
	}

	int32 LayoutListSize = (int32)rowListLayoutData->LayoutList.size();

	if (TargetColumn - (LayoutListSize - 1) > 1 && !bAddRow)
	{
		return false;
	}

	static std::list<SLayoutWindow*>::iterator witer;
	if (rowListLayoutData->LayoutList.empty())
	{
		LayoutWindow->width = width;
		rowListLayoutData->LayoutList.push_back(LayoutWindow);
	}
	else
	{
		if (TargetColumn == LayoutListSize)
		{
			rowListLayoutData->LayoutList.push_back(LayoutWindow);
			witer = rowListLayoutData->LayoutList.begin();
			std::advance(witer, TargetColumn - 1);
		}
		else
		{
			witer = rowListLayoutData->LayoutList.begin();
			std::advance(witer, TargetColumn);
			if (!bFront)
			{
				witer++;
			}
			if (witer == rowListLayoutData->LayoutList.end())
			{
				rowListLayoutData->LayoutList.push_back(LayoutWindow);
			}
			else
			{
				rowListLayoutData->LayoutList.insert(witer, LayoutWindow);
			}
			witer = rowListLayoutData->LayoutList.begin();
			std::advance(witer, TargetColumn);
			if (bFront)
			{
				witer++;
			}
		}
		LayoutWindow->width = (*witer)->width / 2;
		(*witer)->width = LayoutWindow->width;
	}
	RefreshRowAndColumn();
	LayoutWindow->mainEditorWindow = this;
	return true;
}

void MainEditorWindow::Draw()
{
	ImGui::Begin(WindowName.data(), 0, ImGuiWindowFlags_NoDecoration |
		ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_MenuBar |
		ImGuiWindowFlags_NoScrollWithMouse |
		ImGuiWindowFlags_NoScrollbar);
	ImGui::SetWindowSize(ImVec2((float)width, (float)height));
	ImGui::SetWindowPos(ImVec2(0, 0));

	ImGui::BeginMenuBar();
	ImGui::MenuItem("File");
	ImGui::MenuItem("Tool");
	ImGui::MenuItem("Setting");
	ImGui::EndMenuBar();

	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
	static std::list<RowListLayoutData*>::iterator iter;
	static std::list<SLayoutWindow*>::iterator witer;
	int32 Row = 0;
	int32 Column = 0;
	int32 aColumn = 0;
	int32 RSize = (int32)Layouts.size();
	int32 AllSplitterHeight = 4 * (RSize - 1);
	float MouseDeltaY = ImGui::GetIO().MouseDelta.y;
	float MouseDeltaX = ImGui::GetIO().MouseDelta.x;
	for (iter = Layouts.begin(); iter != Layouts.end();)
	{
		if (*iter)
		{
			Column = 0;
			int32 CSize = (int32)(*iter)->LayoutList.size();
			int32 AllSplitterWidth = 4 * (CSize - 1);
			for (witer = (*iter)->LayoutList.begin(); witer != (*iter)->LayoutList.end();)
			{
				(*witer)->Row = Row;
				(*witer)->Column = Column;
				bool isLast = false;
				if (Column == CSize - 1)
				{
					isLast = true;
				}
				if (Row == RSize - 1)
				{
					(*witer)->Draw((*iter)->Height - AllSplitterHeight - 75, isLast, AllSplitterWidth);
				}
				else
				{
					(*witer)->Draw((*iter)->Height, isLast, AllSplitterWidth);
				}

				if (++witer != (*iter)->LayoutList.end())
				{
					ImGui::SameLine();
					std::ostringstream VerticalSplitterName;
					VerticalSplitterName << "VerticalSplitter" << aColumn;
					ImGui::InvisibleButton(VerticalSplitterName.str().data(), ImVec2(4.0f, (*iter)->Height));
					if (ImGui::IsItemActive()) {
						if ((*witer)->width - MouseDeltaX > 5)
						{
							(*witer)->width -= (int32)MouseDeltaX;
							--witer;
							if ((*witer)->width + MouseDeltaX > 5)
							{
								(*witer)->width += (int32)MouseDeltaX;
								witer++;
							}
							else
							{
								witer++;
								(*witer)->width += (int32)MouseDeltaX;
							}
						}
					}
					ImGui::SameLine();
				}
				Column++;
				aColumn++;
			}
		}
		Row++;
		iter++;

		if (iter != Layouts.end())
		{
			std::ostringstream  HorizontalSplitterName;
			HorizontalSplitterName << "HorizontalSplitter" << Row;
			ImGui::InvisibleButton(HorizontalSplitterName.str().data(), ImVec2((float)width, 4.0f));
			if (ImGui::IsItemActive()) {
				if ((*iter)->Height - MouseDeltaY > 5)
				{
					(*iter)->Height -= (int32)MouseDeltaY;
					--iter;
					if ((*iter)->Height + MouseDeltaY > 5)
					{
						(*iter)->Height += (int32)MouseDeltaY;
						iter++;
					}
					else
					{
						iter++;
						(*iter)->Height += (int32)MouseDeltaY;
					}
				}
			}
			AllSplitterHeight += 4;
		}
	}
	ImGui::PopStyleVar();
	ImGui::End();
}
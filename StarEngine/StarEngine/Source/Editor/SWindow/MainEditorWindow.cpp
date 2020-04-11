#include "MainEditorWindow.h"
#include "imgui.h"
#include <sstream>

MainEditorWindow::MainEditorWindow()
{
	bRoot = true;
	for (int32 i = 0; i < MAX_HORIZONTAL_LAYOUT_COUNT; i++)
	{
		HorizontalLayoutCount[i] = 0;
	}
}

MainEditorWindow::~MainEditorWindow()
{
}

std::list<SLayoutWindow*>* MainEditorWindow::AddLayoutRow(int32 TRow, bool bTop)
{
	if (VerticalLayoutCount == MAX_VERTICAL_LAYOUT_COUNT || TRow < 0 || TRow >= MAX_VERTICAL_LAYOUT_COUNT)
	{
		return nullptr;
	}
	std::list<SLayoutWindow*>* vlist = new std::list<SLayoutWindow*>();
	auto iter = begin(Layouts);
	int32 index = 0;
	if (bTop)
	{
		if (TRow == 0)
		{
			Layouts.push_front(vlist);
			VerticalLayoutCount++;
			for (int32 i = MAX_VERTICAL_LAYOUT_COUNT - 1; i >= 0; i--)
			{
				if (i == MAX_VERTICAL_LAYOUT_COUNT - 1)
				{
					continue;
				}
				if (i == index)
				{
					HorizontalLayoutCount[i] = 0;
					VerticalLayoutHeight[i] = 0;
					break;
				}
				HorizontalLayoutCount[i] = HorizontalLayoutCount[i - 1];
				VerticalLayoutHeight[i] = VerticalLayoutHeight[i - 1];
			}
			if (VerticalLayoutHeight[index] == 0)
			{
				VerticalLayoutHeight[index] = height / VerticalLayoutCount;
			}
			return vlist;
		}
		std::advance(iter, TRow);
		index = TRow;
	}
	else
	{
		std::advance(iter, TRow + 1);
		index = TRow + 1;
	}
	Layouts.insert(iter, vlist);
	VerticalLayoutCount++;
	for (int32 i = MAX_VERTICAL_LAYOUT_COUNT - 1; i >= 0; i--)
	{
		if (i == MAX_VERTICAL_LAYOUT_COUNT - 1)
		{
			continue;
		}
		if (i == index)
		{
			HorizontalLayoutCount[i] = 0;
			VerticalLayoutHeight[i] = 0;
			break;
		}
		HorizontalLayoutCount[i] = HorizontalLayoutCount[i - 1];
		VerticalLayoutHeight[i] = VerticalLayoutHeight[i - 1];
	}
	if (index >= 0)
	{
		if (bTop)
		{
			if (index < MAX_VERTICAL_LAYOUT_COUNT - 1)
			{
				VerticalLayoutHeight[index] = VerticalLayoutHeight[index + 1] / 2;
				VerticalLayoutHeight[index + 1] /= 2;
			}
		}
		else
		{
			if (index > 0)
			{
				VerticalLayoutHeight[index] = VerticalLayoutHeight[index - 1] / 2;
				VerticalLayoutHeight[index - 1] /= 2;
			}
		}
	}
	if (VerticalLayoutHeight[index] == 0)
	{
		VerticalLayoutHeight[index] = height / VerticalLayoutCount;
	}

	return vlist;
}

SLayoutWindow* MainEditorWindow::AddLayoutColumn(int32 TRow, int32 Column, bool bFront, SLayoutWindow* LayoutWindow)
{
	if (HorizontalLayoutCount[TRow] == MAX_VERTICAL_LAYOUT_COUNT || TRow < 0 || TRow >= MAX_HORIZONTAL_LAYOUT_COUNT)
	{
		return nullptr;
	}
	if (LayoutWindow == nullptr)
	{
		return nullptr;
	}
	//LayoutWindow->width = width / (HorizontalLayoutCount[TRow] + 1);
	LayoutWindow->Row = TRow;
	auto viter = begin(Layouts);
	std::advance(viter, TRow);
	auto hiter = begin(*(*viter));
	if (HorizontalLayoutCount[TRow] == 0)
	{
		(*viter)->push_front(LayoutWindow);
		LayoutWindow->Column = 0;
		HorizontalLayoutCount[TRow]++;
		LayoutWindow->width = width;
		return LayoutWindow;
	}
	if (bFront)
	{
		if (Column == 0)
		{
			(*viter)->push_front(LayoutWindow);
			LayoutWindow->Column = 0;
			HorizontalLayoutCount[TRow]++;
			return LayoutWindow;
		}
		std::advance(hiter, Column);
		LayoutWindow->Column = Column;
	}
	else
	{
		std::advance(hiter, Column + 1);
		LayoutWindow->Column = Column + 1;
	}
	(*viter)->insert(hiter, LayoutWindow);
	HorizontalLayoutCount[TRow]++;

	if (!bFront)
	{
		hiter--;
		hiter--;
	}

	if ((*hiter) != nullptr)
	{
		LayoutWindow->width = (*hiter)->width / 2;
		(*hiter)->width /= 2;
	}
	else
	{
		LayoutWindow->width = width;
	}
	return LayoutWindow;
}

bool MainEditorWindow::RemoveLayoutWindow(SLayoutWindow* LayoutWindow)
{
	if (LayoutWindow == nullptr)
	{
		return false;
	}
	auto viter = begin(Layouts);
	std::advance(viter, LayoutWindow->Row);
	static std::list<SLayoutWindow*>::iterator witer;
	static std::list<SLayoutWindow*>::iterator bwiter;
	bool bFind = false;
	int32 allWidth = 0;
	for (witer = (*viter)->begin(); witer != (*viter)->end();)
	{
		if ((*witer) == LayoutWindow)
		{
			bFind = true;
			if (witer == (*viter)->end())
			{
				bwiter = --witer;
				witer++;
			}
			if (witer == (*viter)->begin())
			{
				bwiter = ++witer;
				witer--;
			}
			bwiter = witer;
		}
		else
		{
			allWidth += (*witer)->width;
		}
		witer++;
	}
	if (!bFind)
	{
		return false;
	}
	(*viter)->remove(LayoutWindow);
	HorizontalLayoutCount[LayoutWindow->Row]--;
	for (int32 i = 0; i < MAX_VERTICAL_LAYOUT_COUNT - 1; i++)
	{
		if (i >= LayoutWindow->Row)
		{
			HorizontalLayoutCount[i] = HorizontalLayoutCount[i + 1];
			break;
		}
	}
	if (HorizontalLayoutCount[LayoutWindow->Row] != 0)
	{
		if (width - allWidth > 0 && (*bwiter))
		{
			(*bwiter)->width += width - allWidth;
		}
	}
	if (LayoutWindow->Row < MAX_HORIZONTAL_LAYOUT_COUNT && HorizontalLayoutCount[LayoutWindow->Row] == 0)
	{
		VerticalLayoutCount--;
		Layouts.remove(*viter);
		//return true;
		int32 ChangeIndex = -1;

		for (int32 i = 0; i < MAX_VERTICAL_LAYOUT_COUNT - 1; i++)
		{
			if (i >= LayoutWindow->Row)
			{
				VerticalLayoutHeight[i] = VerticalLayoutHeight[i + 1];
				if (i == LayoutWindow->Row)
				{
					ChangeIndex = i;
					VerticalLayoutHeight[i] = VerticalLayoutHeight[i + 1] * 2;
				}
				break;
			}
		}

		if (ChangeIndex >= 0)
		{
			int32  AllHeight = 0;
			for (int32 i = 0; i < MAX_VERTICAL_LAYOUT_COUNT - 1; i++)
			{
				AllHeight += VerticalLayoutHeight[i];
			}
			if (height - AllHeight > 0)
			{
				if (ChangeIndex - 1 >= 0)
				{
					VerticalLayoutHeight[ChangeIndex - 1] += height - AllHeight;
				}
				if (ChangeIndex == 0 && VerticalLayoutCount > 0)
				{
					VerticalLayoutHeight[ChangeIndex + 1] += height - AllHeight;
				}
			}
		}
		return true;
	}
	return false;
}

bool MainEditorWindow::DeleteLayoutWindow(SLayoutWindow* LayoutWindow)
{
	if (RemoveLayoutWindow(LayoutWindow))
	{
		delete LayoutWindow;
		return true;
	}
	return false;
}

bool MainEditorWindow::MoveLayoutWindow(SLayoutWindow* LayoutWindow, int32 TagetRow, int32 TagetColumn, bool bFront, bool bAddRow, bool bTop)
{
	if (!LayoutWindow || TagetRow < 0 || TagetColumn < 0)
	{
		return false;
	}
	RemoveLayoutWindow(LayoutWindow);
	if (bAddRow)
	{
		if (!AddLayoutRow(TagetRow, bTop))
		{
			return false;
		}
		if (VerticalLayoutCount > 1 && !bTop)
		{
			TagetRow++;
		}
	}
	if (AddLayoutColumn(TagetRow, TagetColumn, bFront, LayoutWindow))
	{
		return false;
	}
	return true;
}

bool MainEditorWindow::AddLayoutWindow(SLayoutWindow* LayoutWindow, int32 TagetRow, int32 TagetColumn, bool bFront, bool bAddRow, bool bTop)
{
	if (bAddRow)
	{
		if (!AddLayoutRow(TagetRow, bTop))
		{
			return false;
		}
		if (VerticalLayoutCount > 1 && !bTop)
		{
			TagetRow++;
		}
	}
	if (AddLayoutColumn(TagetRow, TagetColumn, bFront, LayoutWindow))
	{
		return false;
	}
	return true;
}

void MainEditorWindow::Draw()
{
	ImGui::Begin("Splitter test", 0,
		ImGuiWindowFlags_NoDecoration |
		ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_MenuBar |
		ImGuiWindowFlags_NoScrollWithMouse |
		ImGuiWindowFlags_NoScrollbar);
	ImGui::BeginMenuBar();
	ImGui::MenuItem("File");
	ImGui::MenuItem("Tool");
	ImGui::MenuItem("Setting");
	//float MenuBarHeight = ImGui::GetWindowHeight();
	ImGui::EndMenuBar();

	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
	static std::list<std::list<SLayoutWindow*>*>::iterator viter;
	static std::list<SLayoutWindow*>::iterator witer;
	int32 VerticalIndex = 0;
	int32 HorizontalIndex = 0;
	float SplitterHeight = 0.f;
	for (viter = Layouts.begin(); viter != Layouts.end();)
	{
		float SplitterWidth = 0.f;
		for (witer = (*viter)->begin(); witer != (*viter)->end();)
		{
			float VerticalHeight = 0.f;
			if (*witer)
			{
				bool bLast = false;
				if (++witer == (*viter)->end())
				{
					bLast = true;
				}
				witer--;

				if (VerticalIndex == VerticalLayoutCount - 1)
				{
					VerticalHeight = VerticalLayoutHeight[VerticalIndex] - SplitterHeight - 75;
				}
				else
				{
					VerticalHeight = VerticalLayoutHeight[VerticalIndex];
				}
				(*witer)->Draw(VerticalHeight, bLast, SplitterWidth);
			}
			witer++;
			if (witer != (*viter)->end())
			{
				ImGui::SameLine();
				std::ostringstream VerticalSplitterName;
				VerticalSplitterName << "VerticalSplitter" << HorizontalIndex;
				ImGui::InvisibleButton(VerticalSplitterName.str().data(), ImVec2(4.0f, VerticalHeight));
				if (ImGui::IsItemActive()) {
				}
				ImGui::SameLine();
				SplitterWidth += 4;
			}
			HorizontalIndex++;
		}
		viter++;
		if (viter != Layouts.end())
		{
			std::ostringstream  HorizontalSplitterName;
			HorizontalSplitterName << "HorizontalSplitter" << VerticalIndex;
			ImGui::InvisibleButton(HorizontalSplitterName.str().data(), ImVec2(width, 4.0f));
			if (ImGui::IsItemActive()) {
			}
			SplitterHeight += 4;
		}
		VerticalIndex++;
	}
	ImGui::PopStyleVar();

	ImGui::SetWindowSize(ImVec2(width, height));
	ImGui::SetWindowPos(ImVec2(0, 0));
	ImGui::End();
}
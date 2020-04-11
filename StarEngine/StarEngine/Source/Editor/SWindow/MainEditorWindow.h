#pragma once
#include "Define.h"
#include "SLayoutWindow.h"

class MainEditorWindow :public SLayoutWindow
{
public:
	MainEditorWindow();
	virtual ~MainEditorWindow();
	virtual void Draw();
	std::list<std::list<SLayoutWindow*>*> Layouts;
	int32 HorizontalLayoutCount[MAX_VERTICAL_LAYOUT_COUNT];
	int32 VerticalLayoutCount = 0;
	float VerticalLayoutHeight[MAX_VERTICAL_LAYOUT_COUNT];
	std::list<SLayoutWindow*>* AddLayoutRow(int32 TRow = 0, bool bTop = false);
	SLayoutWindow* AddLayoutColumn(int32 TRow = 0, int32 Column = 0, bool bFront = false, SLayoutWindow* LayoutWindow = nullptr);
	bool MoveLayoutWindow(SLayoutWindow* LayoutWindow = nullptr, int32 TagetRow = -1, int32 TagetColumn = -1, bool bFront = false, bool bAddRow = false, bool bTop = false);
	bool RemoveLayoutWindow(SLayoutWindow* LayoutWindow = nullptr);
	bool DeleteLayoutWindow(SLayoutWindow* LayoutWindow = nullptr);
	bool AddLayoutWindow(SLayoutWindow* LayoutWindow, int32 TagetRow, int32 TagetColumn, bool bFront, bool bAddRow, bool bTop);
};

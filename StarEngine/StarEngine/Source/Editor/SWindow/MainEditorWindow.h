#pragma once
#include "Define.h"
#include "SLayoutWindow.h"
class STabItem;

struct RowListLayoutData
{
	int32 Height = 0;
	std::list<SLayoutWindow*> LayoutList;
};

class MainEditorWindow :public SLayoutWindow
{
public:
	MainEditorWindow();
	virtual ~MainEditorWindow();
	virtual void Draw();
	std::list<RowListLayoutData*> Layouts;
	bool MoveLayoutWindow(SLayoutWindow* LayoutWindow, SLayoutWindow* TargetLayoutWindow, bool bFront, bool bAddRow, bool bTop);
	bool RemoveLayoutWindow(SLayoutWindow* LayoutWindow = nullptr);
	bool DeleteLayoutWindow(SLayoutWindow* LayoutWindow = nullptr);
	bool AddLayoutWindow(SLayoutWindow* LayoutWindow, int32 TagetRow, int32 TagetColumn, bool bFront, bool bAddRow, bool bTop);
	void RefreshRowAndColumn();
	std::list<std::function<void()>> ChangeLayoutFunList;
};

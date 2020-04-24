#pragma once
#include "Define.h"
#include "SWindow.h"
#include "STabItem.h"

class MainEditorWindow;
class SLayoutWindow :public SWindow
{
public:
	SLayoutWindow();
	virtual ~SLayoutWindow();
	virtual void Draw(float lineheight, bool bLastHorizontal, float SplitterWidth = 0.f);
	static int32 LayOutWindowIndex;
	bool bRoot = false;
	int32 Row = 0;
	int32 Column = 0;
	std::string TabsName;
	std::list<STabItem*> TabItems;
	MainEditorWindow* mainEditorWindow;
	void addTab(STabItem* tab);
	float realHeight = 0.f;
	float realWidth = 0.f;
	//float width = 0.f;
};

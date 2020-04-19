#pragma once
#include "Define/Define.h"
#include "SWidget.h"
class SLayoutWindow;

class STabItem :public SWidget
{
public:
	STabItem();
	~STabItem();
	int32 LayoutRow = 0;
	int32 LayoutColumn = 0;
	SLayoutWindow* ParentLayoutWindow;
	void Draw() override;
	static int32 STabItemIndex;
	std::string Name;
	bool isRender = false;
private:
};

struct DragItemData
{
	STabItem* item;
	DragItemData()
	{
	}
};

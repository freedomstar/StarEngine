#pragma once
#include "Define.h"
#include "SWindow.h"

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
	//float width = 0.f;
};

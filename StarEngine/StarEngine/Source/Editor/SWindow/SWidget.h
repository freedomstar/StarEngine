#pragma once
#include "Define.h"

class SWidget
{
public:
	static int32 WidgetIndex;
	SWidget();
	virtual ~SWidget();
	virtual void Draw();
	std::string  WidgetName;
private:
};

#pragma once
#include "Define.h"

class SWindow
{
public:
	SWindow();
	void SetWindowName(std::string WindowName);
	virtual ~SWindow();
	virtual void Draw();
	int32 width, height;
	std::string WindowName;
protected:
};

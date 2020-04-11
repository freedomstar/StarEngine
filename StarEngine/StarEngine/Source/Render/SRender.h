#pragma once
#include "Define/Define.h"

class SRender
{
public:
	SRender();
	virtual ~SRender();
	void Init();
	void Run();

private:
	void OpenglInit();
	void DirectX12Init();
	void Tick();
};

#pragma once

#include "Define.h"
#include "Render/SRender.h"
#include "../Runtime/GC/SGarbageCollectionMgr.h"
#include "Runtime/SBaseWindow/SBaseWindow.h"

class StarEngine
{
public:
	StarEngine();
	~StarEngine();
	void Run();
	void ShutDown();
	bool bShutDown = false;
private:
	void Init();
	void DispatchTick(float DeltaTime);
	SRender Render;
	SGarbageCollectionMgr* GarbageCollectionMgr;
	SBaseWindow* BaseWindow;
};

#pragma once

#include "Define.h"
#include "Render/SRender.h"
#include "../Runtime/GC/SGarbageCollectionMgr.h"
#include "Runtime/SBaseWindow/SBaseWindow.h"
#include <time.h>

class StarEngine
{
public:
	StarEngine();
	~StarEngine();
	void Run();
	void ShutDown();
	bool bShutDown = false;
	static StarEngine* GetInstance();
	static StarEngine* _Instance;
	SRender Render;
private:
	void Init();
	void DispatchTick(float DeltaTime);
	SGarbageCollectionMgr* GarbageCollectionMgr;
	SBaseWindow* BaseWindow;
};

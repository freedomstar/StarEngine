#pragma once

#include "Define.h"
#include "Render/SRender.h"
#include "../Runtime/GC/SGarbageCollectionMgr.h"

class StarEngine
{
public:
	StarEngine();
	~StarEngine();
	void Run();
	void ShutDown();
private:
	void Init();
	void DispatchTick(float DeltaTime);
	SRender Render;
	SGarbageCollectionMgr* GarbageCollectionMgr;
};

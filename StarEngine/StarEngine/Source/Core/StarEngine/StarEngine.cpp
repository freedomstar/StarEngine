#include "StarEngine.h"

StarEngine::StarEngine()
{
}

StarEngine::~StarEngine()
{
	delete GarbageCollectionMgr;
}

void StarEngine::Run()
{
	Init();
	double DeltaTime = 0;
	while (!bShutDown)
	{
		if (!BaseWindow || BaseWindow->IsColse())
		{
			break;
		}
		auto StartTime = std::chrono::steady_clock::now();
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		DispatchTick(DeltaTime);
		auto EndTime = std::chrono::steady_clock::now();
		std::chrono::milliseconds DeltaTimeMilli = std::chrono::duration_cast<std::chrono::milliseconds> (EndTime - StartTime);
		DeltaTime = DeltaTimeMilli.count() / 1000.f;
	}
}

void StarEngine::ShutDown()
{
	bShutDown = true;
}

void StarEngine::Init()
{
	GarbageCollectionMgr = SGarbageCollectionMgr::GetInstance();
	std::thread GCThread(&SGarbageCollectionMgr::Start, GarbageCollectionMgr);
	GCThread.detach();

	Render.Init();
	std::thread RenderThread(&SRender::Run, Render);
	RenderThread.detach();

	BaseWindow = NewSObject<SBaseWindow>();
	BaseWindow->CreateBaseWindow("StarEngine");
}

void StarEngine::DispatchTick(float DeltaTime)
{
	GarbageCollectionMgr->DispatchSObjectTick(DeltaTime);
}
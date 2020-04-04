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

	static std::chrono::microseconds DeltaTime;
	while (true)
	{
		static auto StartTime = std::chrono::system_clock::now();
		DispatchTick(float(DeltaTime.count()) / 1000000);
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		static auto EndTime = std::chrono::system_clock::now();
		DeltaTime = std::chrono::duration_cast<std::chrono::microseconds>(EndTime - StartTime);
	}
}

void StarEngine::ShutDown()
{
}

void StarEngine::Init()
{
	GarbageCollectionMgr = SGarbageCollectionMgr::GetInstance();
	std::thread GCThread(&SGarbageCollectionMgr::Start, GarbageCollectionMgr);
	GCThread.detach();

	Render.Init();
	std::thread RenderThread(&SRender::Run, Render);
	RenderThread.detach();
}

void StarEngine::DispatchTick(float DeltaTime)
{
	GarbageCollectionMgr->DispatchSObjectTick(DeltaTime);
}
#include "SGarbageCollectionMgr.h"
#include "Core/SObject/SObject.h"
#include "stdio.h"
#include <chrono>

SGarbageCollectionMgr* SGarbageCollectionMgr::_Instance = nullptr;

SGarbageCollectionMgr::SGarbageCollectionMgr()
{
}

SGarbageCollectionMgr::~SGarbageCollectionMgr()
{
}

void SGarbageCollectionMgr::Start()
{
	printf("\nStart GC,Interval %d second \n", GARBAGE_COLLECTIONMGR_TIMER_INTERVAL);
	while (true)
	{
		std::this_thread::sleep_for(std::chrono::seconds(GARBAGE_COLLECTIONMGR_TIMER_INTERVAL));
		ClearGarbageCollection();
	}
}

SGarbageCollectionMgr* SGarbageCollectionMgr::GetInstance()
{
	if (_Instance == nullptr)
	{
		_Instance = new SGarbageCollectionMgr();
	}
	return _Instance;
};

void SGarbageCollectionMgr::ClearGarbageCollection()
{
	std::cout << "\n--------------Start Clear Garbage Collection-------------" << std::endl;
	bool block = _mutex.try_lock();
	if (!block)
	{
		std::cout << "\n--------------Garbage Collection Mutex.try_lock failed-------------" << std::endl;
		std::cout << "--------------End Clear Garbage Collection-------------" << std::endl;
		return;
	}
	std::list<SObject*>::iterator iter;
	for (iter = RootObjects.begin(); iter != RootObjects.end();)
	{
		if ((*iter)->ObjectGCFlag != PendingKill)
		{
			(*iter)->GCArrive = true;
			MarkGCflag((*iter)->childObjRefList);
			iter++;
		}
		else
		{
			RootObjects.erase(iter++);
		}
	}
	for (iter = SObjectList.begin(); iter != SObjectList.end();)
	{
		if ((*iter)->GCArrive == false)
		{
			SObject* obj = *iter;
			SObjectList.erase(iter++);
			printf("Delete No. %d obj \n", obj->index);
			if (obj->ObjectGCFlag == AtRoot)
			{
				RootObjects.remove(obj);
			}
			delete obj;
		}
		else
		{
			(*iter)->GCArrive = false;
			iter++;
		}
	}
	_mutex.unlock();
	std::cout << "--------------End Clear Garbage Collection-------------" << std::endl;
}

void SGarbageCollectionMgr::MarkGCflag(std::list<void*>& RefGClist)
{
	std::list<void*>::iterator iter;
	for (iter = RefGClist.begin(); iter != RefGClist.end(); iter++)
	{
		SObject* obj = *(SObject**)*iter;
		if (obj)
		{
			if (obj->ObjectGCFlag != PendingKill)
			{
				obj->GCArrive = true;
				MarkGCflag(obj->childObjRefList);
			}
		}
	}
}

void SGarbageCollectionMgr::AddGcObject(SObject* obj)
{
	if (obj)
	{
		SObjectList.push_back(obj);
	}
}

void SGarbageCollectionMgr::AddToRoot(SObject* obj)
{
	if (obj)
	{
		RootObjects.push_back(obj);
	}
}

void SGarbageCollectionMgr::DispatchSObjectTick(float DeltaTime)
{
	static std::list<SObject*>::iterator iter;
	for (iter = SObjectList.begin(); iter != SObjectList.end();)
	{
		if ((*iter)->bTick && (*iter)->ObjectGCFlag != PendingKill)
		{
			(*iter)->Tick(DeltaTime);
			iter++;
		}
	}
}
#include "SGarbageCollectionMgr.h"
#include <boost/thread.hpp>
#include "Core/SObject/SObject.h"
#include "stdio.h"

#define GARBAGE_COLLECTIONMGR_TIMER_INTERVAL 5

SGarbageCollectionMgr::SGarbageCollectionMgr()
{
}

SGarbageCollectionMgr::~SGarbageCollectionMgr()
{
	delete io_service;
	delete timer;
}

void SGarbageCollectionMgr::Tick()
{
	ClearGarbageCollection();
	static boost::posix_time::seconds interval(GARBAGE_COLLECTIONMGR_TIMER_INTERVAL);
	timer->expires_at(timer->expires_at() + interval);
	timer->async_wait(boost::bind(&SGarbageCollectionMgr::Tick, this));
}

void SGarbageCollectionMgr::Start(boost::asio::io_service* io_service)
{
	printf("\nStart GC,Interval %d second \n", GARBAGE_COLLECTIONMGR_TIMER_INTERVAL);
	timer = new boost::asio::deadline_timer(*io_service, boost::posix_time::seconds(GARBAGE_COLLECTIONMGR_TIMER_INTERVAL));
	timer->async_wait(boost::bind(&SGarbageCollectionMgr::Tick, this));
}

SGarbageCollectionMgr* SGarbageCollectionMgr::_Instance = nullptr;

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
	_mutex.lock();
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
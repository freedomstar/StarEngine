#pragma once
#include <list>
#include <boost/asio.hpp>
#include <iostream>
#include <boost/thread/mutex.hpp>
//#include "Core/SObject/SObject.h"

enum GCFlag
{
	AtRoot,
	NoGC,
	PendingKill,
	Auto
};

class SObject;

class SGarbageCollectionMgr
{
public:
	SGarbageCollectionMgr();
	~SGarbageCollectionMgr();
	static SGarbageCollectionMgr* GetInstance();
	boost::asio::io_service* io_service;
	boost::asio::deadline_timer* timer;
	void AddGcObject(SObject* obj);
	void Tick();
	void Start(boost::asio::io_service* io_service);
	void AddToRoot(SObject* obj);
private:
	std::list<SObject*> SObjectList;
	std::list<SObject*>RootObjects;
	static SGarbageCollectionMgr* _Instance;
	void ClearGarbageCollection();
	void MarkGCflag(std::list<void*>& RefGClist);
	boost::mutex _mutex;
};

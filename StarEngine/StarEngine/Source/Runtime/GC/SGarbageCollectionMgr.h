#pragma once
#include <list>
#include <iostream>
#include <mutex>
//#include "Core/SObject/SObject.h"

#define GARBAGE_COLLECTIONMGR_TIMER_INTERVAL 60

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
	virtual ~SGarbageCollectionMgr();
	static SGarbageCollectionMgr* GetInstance();
	void AddGcObject(SObject* obj);
	void Start();
	void AddToRoot(SObject* obj);
	void DispatchSObjectTick(float DeltaTime);
private:
	std::list<SObject*> SObjectList;
	std::list<SObject*>RootObjects;
	static SGarbageCollectionMgr* _Instance;
	void ClearGarbageCollection();
	void MarkGCflag(std::list<void*>& RefGClist);
	double DeltaTime = 0;
	std::mutex _mutex;
};

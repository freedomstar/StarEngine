#pragma once

#include "Define.h"
#include "Runtime/GC/SGarbageCollectionMgr.h"
#include <list>

typedef void (SObject::* BaseSFunction)(void*, ...);

struct SFunction
{
public:
	BaseSFunction fun;
};

class SObject
{
public:
	SObject();
	virtual ~SObject();
	GCFlag ObjectGCFlag = GCFlag::Auto;
	void AddToRoot();
	std::list<void*> childObjRefList;
	std::map<std::string, SFunction> funRefMap;
	void AddGCRef(void* child);
	bool GCArrive = false;
	void Destroy();
	int32 index;
	void PrintChildObject();
	bool bTick = true;
	virtual void ConfigGCRef() {};
	virtual void Tick(float DeltaTime);
private:
	void FindChildObj(std::list<void*>& list, int32 level);
};

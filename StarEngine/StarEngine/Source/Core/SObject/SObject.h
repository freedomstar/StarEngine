#pragma once

#include "Define.h"
#include "Runtime/GC/SGarbageCollectionMgr.h"
#include <list>

class SObject
{
	//typedef signed int	 		int32;		// 32-bit signed.
public:
	SObject();
	~SObject();
	GCFlag ObjectGCFlag = GCFlag::Auto;
	void AddToRoot();
	std::list<void*> childObjRefList;
	void AddGCRef(void* child);
	bool GCArrive = false;
	void Destroy();
	int32 index;
	void PrintChildObject();
private:
	void FindChildObj(std::list<void*>& list, int32 level);
};

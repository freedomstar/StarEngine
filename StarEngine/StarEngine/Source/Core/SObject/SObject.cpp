#include "SObject.h"

SObject::SObject()
{
	index = 0;
}

SObject::~SObject()
{
}

void SObject::AddGCRef(void* child)
{
	//childObjRefList.Con
	childObjRefList.push_back(child);
}

void SObject::Destroy()
{
	printf("\nMark No. %d obj destroy \n", index);
	this->ObjectGCFlag = PendingKill;
	PrintChildObject();
}

void SObject::AddToRoot()
{
	this->ObjectGCFlag = AtRoot;
	SGarbageCollectionMgr* GarbageCollectionMgr = SGarbageCollectionMgr::GetInstance();
	GarbageCollectionMgr->AddToRoot(this);
}

void SObject::FindChildObj(std::list<void*>& list, int32 level)
{
	std::list<void*>::iterator iter;
	for (iter = list.begin(); iter != list.end(); iter++)
	{
		SObject* obj = *(SObject**)*iter;
		if (obj)
		{
			for (int32 i = 0; i < level; i++)
			{
				printf("  ");
			}
			printf("ChildObj No. %d obj \n", obj->index);
			FindChildObj(obj->childObjRefList, level + 1);
		}
	}
}

void SObject::PrintChildObject()
{
	std::list<void*>::iterator iter;
	for (iter = childObjRefList.begin(); iter != childObjRefList.end(); iter++)
	{
		SObject* obj = *(SObject**)*iter;
		if (obj)
		{
			for (int32 i = 0; i < 1; i++)
			{
				printf("  ");
			}
			printf("ChildObj No. %d obj \n", obj->index);
			FindChildObj(obj->childObjRefList, 2);
		}
	}
}

void SObject::Tick(float DeltaTime)
{
}
//#include "windows.h"
#include <iostream>
#include <boost/thread/thread.hpp>
#include "boost/array.hpp"
#include "Define.h"
#include "../Core/Math/SMath.h"
#include "Core/Math/SMatrix.h"
#include "Core/SObject/SObject.h"
#include "Runtime/GC/SGarbageCollectionMgr.h"
//typedef signed int int32;

class Test :public SObject
{
public:
	Test();
	~Test();
	SObject* m;
	Test* t;
};

Test::Test()
{
	AddGCRef(&m);
	AddGCRef(&t);
}

Test::~Test()
{
}

int main(void) {
	SGarbageCollectionMgr* mgr = SGarbageCollectionMgr::GetInstance();
	Test* testlist[3];
	int32 index = 0;
	for (int32 i = 0; i < 3; i++)
	{
		testlist[i] = NewSObject<Test>();
		testlist[i]->AddToRoot();
		printf("Create No. %d obj \n", index);
		testlist[i]->index = index++;
		testlist[i]->t = NewSObject<Test>();
		printf("Create No. %d obj \n", index);
		testlist[i]->t->index = index++;
		testlist[i]->m = NewSObject<SObject>();
		printf("Create No. %d obj \n", index);
		testlist[i]->m->index = index++;
		testlist[i]->t->t = NewSObject<Test>();
		printf("Create No. %d obj \n", index);
		testlist[i]->t->t->index = index++;
		testlist[i]->t->t->t = NewSObject<Test>();
		printf("Create No. %d obj \n", index);
		testlist[i]->t->t->t->index = index++;
		testlist[i]->t->m = NewSObject<SObject>();
		printf("Create No. %d obj \n", index);
		testlist[i]->t->m->index = index++;
		//testlist[i]->PrintChildObject();
	}
	boost::asio::io_service* io_service = new boost::asio::io_service();
	testlist[1]->Destroy();
	mgr->Start(io_service);
	boost::thread td(boost::bind(&boost::asio::io_service::run, io_service));
	while (true)
	{
		Sleep(1000);
		std::cout << "Main Thread" << std::endl;
	}
	return 0;
}
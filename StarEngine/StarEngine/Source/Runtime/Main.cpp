//#include "windows.h"
#include <iostream>
#include <boost/thread/thread.hpp>
#include "boost/array.hpp"
#include "Define.h"
#include "../Core/Math/SMath.h"
#include "Core/Math/SMatrix.h"
#include "Core/SObject/SObject.h"
#include "Runtime/GC/SGarbageCollectionMgr.h"
#include <stdarg.h>
#include "Core/TestRefClass.h"
//typedef signed int int32;

int main(void)
{
	SGarbageCollectionMgr* mgr = SGarbageCollectionMgr::GetInstance();
	TestRefClass* test = NewSObject<TestRefClass>();
	(test->*(test->funRefMap["TestRefFun"].fun))(test, "string²ÎÊý²âÊÔ");
	test->index = 0;
	test->TestObj = NewSObject<SObject>();
	test->index = 1;
	boost::asio::io_service* io_service = new boost::asio::io_service();
	test->Destroy();
	mgr->Start(io_service);
	boost::thread td(boost::bind(&boost::asio::io_service::run, io_service));
	while (true)
	{
		Sleep(1000);
	}
	return 0;
}
//#include "windows.h"
#include <iostream>
#include "Define.h"
#include "Core/SObject/SObject.h"
#include "Runtime/GC/SGarbageCollectionMgr.h"
#include "Core/TestRefClass.h"
#include "Core/StarEngine/StarEngine.h"

//typedef signed int int32;
void test()
{
	while (true)
	{
		std::cout << "test!" << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}

int main(void)
{
	//SGarbageCollectionMgr* mgr = SGarbageCollectionMgr::GetInstance();
	//TestRefClass* test = NewSObject<TestRefClass>();
	//(test->*(test->funRefMap["TestRefFun"].fun))(test, "string²ÎÊý²âÊÔ");
	//test->index = 0;
	//test->TestObj = NewSObject<SObject>();
	//test->TestObj->index = 1;
	//test->Destroy();
	//std::thread threa(&SGarbageCollectionMgr::Start, mgr);
	//threa.detach();
	//while (true)
	//{
	//	Sleep(1000);
	//}
	//return 0;
	StarEngine engine;
	engine.Run();
	engine.ShutDown();
}
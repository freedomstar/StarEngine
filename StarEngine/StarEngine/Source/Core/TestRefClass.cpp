#include "TestRefClass.h"

TestRefClass::~TestRefClass()
{
}

TestRefClass::TestRefClass()
{
}

void TestRefClass::TestRefFun(char* str)
{
	std::cout << "���� TestRefFun, str =" << str << std::endl;
}
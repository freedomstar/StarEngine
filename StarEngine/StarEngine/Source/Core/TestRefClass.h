#pragma once
#include "TestRefClassStarCode.h"
#include "Core/SObject/SObject.h"
#include "Define.h"

SCLASS()
class TestRefClass :public SObject
{
	STAR_DEFINE_CODE();

public:
	TestRefClass();
	virtual ~TestRefClass();

	SPROPERTY()
		SObject* TestObj;

	SFUNCTION()
		void TestRefFun(char* str);
};

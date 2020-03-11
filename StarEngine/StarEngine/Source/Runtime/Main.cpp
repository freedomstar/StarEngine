#include "windows.h"
#include <iostream>
#include <boost/thread/thread.hpp>
#include "boost/array.hpp"
#include "Define.h"
#include "../Core/Math/SMath.h"
//typedef signed int int32;

int main()
{
	float fa[] = { 1,2,
				   1,-1 };
	SMatrix a = SMatrix(2, 2, fa);
	float fb[] = { 1,2,-3,
				   -1,1,2 };
	SMatrix b = SMatrix(2, 3, fb);

	SMatrix c = a * b;

	for (int32 i = 0; i < b.Row; i++)
	{
		for (int32 j = 0; j < b.Column; j++)
		{
			std::cout << b.Matrix[i][j] << " ";
		}
		std::cout << std::endl;
	}
	return 0;
}
#pragma once
#include "Define.h"
#include "Core/SObject/SObject.h"
#include <iostream>

//TODO::Use SIMD
class SObject;

class SMatrix
{
public:
	SMatrix();
	SMatrix(int32 Row, int32 Column);
	SMatrix(int32 Row, int32 Column, float data[]);
	SMatrix(int32 Row, int32 Column, float data[], bool MateData);
	SMatrix(float data[]);
	virtual ~SMatrix();
	int32 Row = 0;
	int32 Column = 0;
	float Matrix[4][4] = { {0,0,0,0},
						   {0,0,0,0},
						   {0,0,0,0},
						   {0,0,0,0} };

	SMatrix operator *(const SMatrix& sMatrix)
	{
		if (this->Column == sMatrix.Row)
		{
			int32 newRow = this->Row;
			int32 newColumn = sMatrix.Column;
			static float data[] = { 0,0,0,0,
							0,0,0,0,
							0,0,0,0,
							0,0,0,0 };
			for (int32 i = 0; i < 4; i++)
			{
				for (int32 j = 0; j < 4; j++)
				{
					data[4 * i + j] = 0;
					for (int32 k = 0; k < 4; k++)
					{
						data[4 * i + j] += this->Matrix[i][k] * sMatrix.Matrix[k][j];
					}
				}
			}
			return SMatrix(newRow, newColumn, data, true);
		}
		else
		{
			return SMatrix();
		}
	};
};

#pragma once
#include "Define.h"
#include "Core/SObject/SObject.h"
#include <iostream>

class SObject;

class SMatrix :public SObject
{
public:
	SMatrix();
	SMatrix(int32 Row, int32 Column);
	SMatrix(int32 Row, int32 Column, float data[]);
	SMatrix(const SMatrix& sMatrix);
	~SMatrix();
	int32 Row = 0;
	int32 Column = 0;
	float** Matrix;

	SMatrix operator *(const SMatrix& sMatrix)
	{
		if (this->Column == sMatrix.Row)
		{
			int32 newRow = this->Row;
			int32 newColumn = sMatrix.Column;
			float* data = new float[newRow * newColumn];
			for (int32 i = 1; i <= newRow; i++)
			{
				for (int32 j = 1; j <= newColumn; j++)
				{
					data[newColumn * (i - 1) + (j - 1)] = 0.f;
					for (int32 k = 0; k < this->Column; k++)
					{
						data[newColumn * (i - 1) + (j - 1)] += this->Matrix[i - 1][k] * sMatrix.Matrix[k][j - 1];
					}
				}
			}
			return SMatrix(newRow, newColumn, data);
		}
		else
		{
			return SMatrix();
		}
	};
};

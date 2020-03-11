#include "SMatrix.h"

SMatrix::SMatrix()
{
	this->Row = Row;
	this->Column = Column;
	Matrix = new float* [Row];
	for (int32 i = 0; i < Row; i++)
	{
		Matrix[i] = new float[Column];
	}
}

SMatrix::SMatrix(int32 Row, int32 Column)
{
	this->Row = Row;
	this->Column = Column;
	Matrix = new float* [Row];
	for (int32 i = 0; i < Row; i++)
	{
		Matrix[i] = new float[Column];
	}
}

SMatrix::SMatrix(int32 Row, int32 Column, float data[])
{
	this->Row = Row;
	this->Column = Column;
	Matrix = new float* [Row];
	for (int32 i = 1; i <= Row; i++)
	{
		Matrix[i - 1] = new float[Column];
		for (int32 j = 1; j <= Column; j++)
		{
			Matrix[i - 1][j - 1] = data[Column * (i - 1) + (j - 1)];
		}
	}
}

SMatrix::SMatrix(const SMatrix& sMatrix)
{
}

SMatrix::~SMatrix()
{
	for (int i = 0; i < Row; i++)
		delete[]Matrix[i];
	delete[]Matrix;
}
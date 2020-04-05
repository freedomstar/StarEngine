#include "SMatrix.h"
#include "Core/SObject/SObject.h"

SMatrix::SMatrix()
{
	for (int32 i = 0; i < 4; i++)
	{
		for (int32 j = 0; j < 4; j++)
		{
			Matrix[i][j] = 0;
		}
	}
}

SMatrix::SMatrix(int32 Row, int32 Column)
{
	this->Row = Row;
	this->Column = Column;
	for (int32 i = 0; i < 4; i++)
	{
		for (int32 j = 0; j < 4; j++)
		{
			Matrix[i][j] = 0;
		}
	}
}

SMatrix::SMatrix(int32 Row, int32 Column, float data[])
{
	this->Row = Row;
	this->Column = Column;
	for (int32 i = 0; i < 4; i++)
	{
		for (int32 j = 0; j < 4; j++)
		{
			if (i + 1 > Row || j + 1 > Column)
			{
				if (i == j)
				{
					Matrix[i][j] = 1;
				}
				else
				{
					Matrix[i][j] = 0;
				}
			}
			else
			{
				Matrix[i][j] = data[Column * i + j];
			}
		}
	}
}

SMatrix::SMatrix(int32 Row, int32 Column, float data[], bool MateData)
{
	this->Row = Row;
	this->Column = Column;
	if (MateData)
	{
		for (int32 i = 0; i < 4; i++)
		{
			for (int32 j = 0; j < 4; j++)
			{
				Matrix[i][j] = data[4 * i + j];
			}
		}
	}
	else
	{
		for (int32 i = 0; i < 4; i++)
		{
			for (int32 j = 0; j < 4; j++)
			{
				if (i + 1 > Row || j + 1 > Column)
				{
					if (i == j)
					{
						Matrix[i][j] = 1;
					}
					else
					{
						Matrix[i][j] = 0;
					}
				}
				else
				{
					Matrix[i][j] = data[Column * i + j];
				}
			}
		}
	}
}

SMatrix::SMatrix(float data[])
{
	Row = 4;
	Column = 4;
	for (int32 i = 0; i < 4; i++)
	{
		for (int32 j = 0; j < 4; j++)
		{
			Matrix[i][j] = data[Column * i + j];
		}
	}
}

SMatrix::~SMatrix()
{
}
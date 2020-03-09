#pragma once

class SVector
{
public:
	SVector();
	~SVector();
};

class SVector2:SVector
{
public:
	SVector2(float x,float y);
	~SVector2();

	float x = 0, y = 0;

	SVector2 operator +(const SVector2& Vector2)
	{
		return SVector2(this->x + Vector2.x, this->y + Vector2.y);
	};

	SVector2 operator -(const SVector2& Vector2)
	{
		return SVector2(this->x - Vector2.x, this->y - Vector2.y);
	};

	float operator ^(const SVector2& Vector2)
	{
		return (this->x * Vector2.y) - (this->y * Vector2.x);
	};

	float operator *(const SVector2& Vector2)
	{
		return (this->x * Vector2.x) + (this->y * Vector2.y);
	};
};

class SVector3 :SVector
{
public:
	SVector3(float x, float y, float z);
	~SVector3();

	float x = 0, y = 0, z = 0;

	SVector3 operator +(const SVector3& Vector3)
	{
		return SVector3(this->x + Vector3.x, this->y + Vector3.y, this->z + Vector3.z);
	};

	SVector3 operator -(const SVector3& Vector3)
	{
		return SVector3(this->x - Vector3.x, this->y - Vector3.y, this->z - Vector3.z);
	};

	SVector3 operator ^(const SVector3& Vector3)
	{
		return SVector3(
			(this->y * Vector3.z)-(this->z * Vector3.y), 
			(this->z * Vector3.x) - (this->x * Vector3.z),
			(this->x * Vector3.y) - (this->y * Vector3.x)
		);
	};

	float operator *(const SVector3& Vector3)
	{
		return (this->x * Vector3.x) + (this->y * Vector3.y) + (this->z * Vector3.z);
	};
};




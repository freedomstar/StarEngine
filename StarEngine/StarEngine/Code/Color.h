#pragma once
class Color
{
public:
	float R;
	float G;
	float B;
	float A;
	static Color Lerp(Color color1, Color color2, float value);
	Color(float r,float g,float b,float a);
	~Color();

private:

};


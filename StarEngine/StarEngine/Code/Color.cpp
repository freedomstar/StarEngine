#include"Color.h"
#include<algorithm>
using namespace std;

Color Color::Lerp(Color color1, Color color2, float value)
{
	value = min(max(value, 0.0f), 1.0f);
	return Color((color2.R - color1.R)*value + color1.R, (color2.G - color1.G)*value + color1.G, (color2.B - color1.B)*value + color1.B, (color2.A - color1.A)*value + color1.A);
}

Color::Color(float r, float g, float b, float a)
{
	R = r;
	G = g;
	B = b;
	A = a;
}

Color::~Color()
{
}
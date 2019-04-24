#include "Light.h"

Light::Light(LightType type, glm::vec3 dir, Color *color, glm::vec3 pos)
{
	FrontDir = dir;
	Type = type;
	this->color = color;
	Postition = pos;
}

Light::Light(LightType type, glm::vec3 dir, Color *Color, glm::vec3 pos,float Range)
{
	FrontDir = dir;
	Type = type;
	this->color = color;
	this->Range = Range;
	Postition = pos;
}

Light::Light(LightType type, glm::vec3 dir, Color *Color, glm::vec3 pos,float Range, float Phi)
{
	FrontDir = dir;
	Type = type;
	this->color = color;
	this->Range = Range;
	this->Phi = Phi;
	Postition = pos;
}

Light::~Light()
{
	delete color;
}
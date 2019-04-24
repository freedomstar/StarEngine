#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Color.h"

enum LightType
{
	Directional,
	Point,
	Spotlight,
};

class  Light
{
public:
	Color *color;
	glm::vec3 FrontDir;
	glm::vec3 Postition;
	float Range;
	float Phi;
	LightType Type;
	Light(LightType type,glm::vec3 dir,Color *Color, glm::vec3 pos);
	Light(LightType type, glm::vec3 dir, Color *Color, glm::vec3 pos, float Range);
	Light(LightType type, glm::vec3 dir, Color *Color, glm::vec3 pos, float Range,float Phi);
	~Light();

private:

};



#pragma once
#include "Light.h"
#include<List>
#include "Color.h"

using namespace std;
class LightMgr
{
public:
	LightMgr();
	void CreateLight(LightType type,glm::vec3 dir, Color *color, glm::vec3 pos,float Range, float Phi);
	Light* GetDirLight();
	~LightMgr();
private:
	Light* DirLight;
	list<Light*> LightList;
};


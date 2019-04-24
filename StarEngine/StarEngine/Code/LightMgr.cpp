#include "LightMgr.h"

LightMgr::LightMgr()
{
	
}

void LightMgr::CreateLight(LightType type, glm::vec3 dir,Color *color, glm::vec3 pos,float Range,  float Phi)
{
	Light* light;
	switch (type)
	{
	case Directional:
		light = new Light(type, dir, color,pos);
		if (DirLight==NULL)
		{
			DirLight = light;
		}
		else
		{
			LightList.push_back(light);
		}
		break;
	case Point:
		light = new Light(type, dir, color, pos, Range);
		LightList.push_back(light);
		break;
	case Spotlight:
		light = new Light(type, dir, color, pos, Range, Phi);
		LightList.push_back(light);
		break;
	default:
		light = new Light(type, dir, color, pos);
		LightList.push_back(light);
		break;
	}
}
Light* LightMgr::GetDirLight()
{
	return DirLight;
}

LightMgr::~LightMgr()
{
	for (list<Light* >::iterator it = LightList.begin(); it != LightList.end(); ++it)
	{
		delete *it;
	}
}
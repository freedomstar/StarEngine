#pragma once
#include <string>
#include <iostream>
#include <map>
#include <glad/glad.h>
#include <map>
#include "stb_image.h"

using namespace std;
class Texture
{
public:
	static unsigned int LoadTexture(const char *path, int  wrapMode, int filterMode);
	static map<string,Texture> TextureMap;
	unsigned int textureID;
	Texture(const char *path, int  wrapMode, int filterMode);
	~Texture();
};


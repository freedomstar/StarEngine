#pragma once
#include "Shader.h"
#include <vector>
#include "Texture.h"
using namespace std;

enum TextureType
{
	Albedo,
	Normal,
	Custom
}; 

struct TextureParm
{
	TextureType type;
	string name;
	string path;
};

struct TextureStruct
{
	unsigned int ID;
	TextureType type;
	string name;
	string path;
};

class Material
{
public:
	vector<TextureStruct*> textures;
	Shader* shader;
	Material(Shader* shader, vector<TextureParm> &textureStructs);
	~Material();

private:

};


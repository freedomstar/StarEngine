#include "Material.h"

Material::Material(Shader* shader, vector<TextureParm> &textureStructs)
{
	this->shader = shader;
	for (unsigned int i = 0; i < textureStructs.size(); i++)
	{
		TextureStruct* z = new TextureStruct();
		z->ID = Texture::LoadTexture(textureStructs[i].path.c_str(), GL_REPEAT, GL_LINEAR);
		z->name = textureStructs[i].type, textureStructs[i].name;
		z->path = textureStructs[i].path;
		textures.push_back(z);
	}
}

Material::~Material()
{
	delete shader;
	for (int i = 0; i < textures.size(); i++)
	{
		delete textures[i];
	}
}
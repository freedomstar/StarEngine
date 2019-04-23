#include "Texture.h"

map<string, Texture> Texture::TextureMap;



unsigned int Texture::LoadTexture(const char *path, int  wrapMode, int filterMode)
{
	map<string, Texture>::iterator iter;
	iter = TextureMap.find(path);
	if (iter != TextureMap.end())
	{
		return iter->second.textureID;
	}
	else
	{
		Texture t(path, wrapMode, filterMode);
		TextureMap.insert(pair<string, Texture>(path, t));
		return t.textureID;
	}
}

Texture::Texture(const char *path ,int  wrapMode, int filterMode)
{
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterMode);

	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);
	if (data)
	{
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		cout << "Failed to load texture" <<endl;
	}
	stbi_image_free(data);
}


Texture::~Texture()
{
}

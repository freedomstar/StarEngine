#include "stb_image.h"
#include <string>
#include <iostream>
#include <map>
#include <glad/glad.h>

using namespace std;
class Texture
{
public:
	unsigned int texture;
	Texture(const char *path, int  wrapMode, int filterMode);
	~Texture();
private:
	static bool isInit;
};


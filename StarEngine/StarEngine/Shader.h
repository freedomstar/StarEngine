#pragma once
#include <iostream>
#include <fstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace std;
class Shader
{
public:
	Shader(const char* vertexPath, const char* fragmentPath);
	void Use();
	void setBool(const string &name, bool value);
	void setInt(const string &name, int value);
	void setFloat(const string &name, float value);
	~Shader();
private:
	char* readShaderFile(const char* Path);
	void checkShaderCompile(int shader, string type);
	void checkShaderLink(int shaderProgram);
	char* vertexShaderSource;
	char* fragmentShaderSource;
	unsigned int vertexShader;
	unsigned int fragmentShader;
	unsigned int shaderProgram;
};


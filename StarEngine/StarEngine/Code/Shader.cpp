
#include "Shader.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	vertexShaderSource = readShaderFile(vertexPath);
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	checkShaderCompile(vertexShader, "VERTEX");

	fragmentShaderSource = readShaderFile(fragmentPath);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	checkShaderCompile(fragmentShader, "FRAGMENT");

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	checkShaderLink(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void  Shader::Use()
{
	glUseProgram(shaderProgram);
}

 char* Shader::readShaderFile(const char* Path)
{

	std::string shaderCode;
	std::ifstream ShaderFile;
	ShaderFile.exceptions(std::ifstream::badbit);
	try
	{
		ShaderFile.open(Path);
		std::stringstream ShaderStream;
		ShaderStream << ShaderFile.rdbuf();
		ShaderFile.close();
		shaderCode = ShaderStream.str();
	}
	catch(std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	int len = shaderCode.length();
	char *result=new char[len+1];
	strcpy_s(result, len+1, shaderCode.c_str());
	return result;
}

void Shader::checkShaderCompile(int shader,string type)
{
	GLint success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		GLchar InfoLog[1024];
		glGetShaderInfoLog(shader, sizeof(InfoLog), NULL, InfoLog);
		cout<<(stderr, "Error compiling shader type %d:'%s'\n", type, InfoLog);
	}
}

void Shader::checkShaderLink(int shaderProgram)
{
	GLint success;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		GLchar InfoLog[1024];
		glGetProgramInfoLog(shaderProgram, sizeof(InfoLog), NULL, InfoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << InfoLog << std::endl;
	}
}


void Shader::setBool(const string &name, bool value)
{
	glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()),value);
}

void Shader::setInt(const string &name, int value)
{
	glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), value);
}

void Shader::setVec3(const std::string &name, float x, float y, float z) 
{
	glUniform3f(glGetUniformLocation(shaderProgram, name.c_str()), x, y, z);
}

void Shader::setFloat(const string &name, float value)
{
	glUniform1f(glGetUniformLocation(shaderProgram, name.c_str()), value);
}

Shader::~Shader()
{
	delete[] vertexShaderSource;
	delete[] fragmentShaderSource;
}

#include "Shader.h"



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
	std::ifstream t;
	streamoff  length = 0;
	t.open(Path);
	t.seekg(0, std::ios::end);
	length = t.tellg();
	t.seekg(0, std::ios::beg);
	char* buffer = new char[length];
	memset(buffer, 0, length - 1);
	t.read(buffer, length);
	t.close();
	//Path = buffer;
	//cout << Path;
	return buffer;
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

void Shader::setFloat(const string &name, float value)
{
	glUniform1f(glGetUniformLocation(shaderProgram, name.c_str()), value);
}


Shader::~Shader()
{
}

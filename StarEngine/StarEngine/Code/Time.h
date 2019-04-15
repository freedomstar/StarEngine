#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h> 

class Time
{
public:
	static float deltaTime;
	Time();
	~Time();
	static void UpdateTime();

private:
	static float lastFrame;
};



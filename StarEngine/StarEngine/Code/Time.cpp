#include "Time.h"

Time::Time()
{

}


Time::~Time()
{

}
 
float Time::deltaTime = 0.0f;
float Time::lastFrame = 0.0f;

void Time::UpdateTime()
{
	float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
}
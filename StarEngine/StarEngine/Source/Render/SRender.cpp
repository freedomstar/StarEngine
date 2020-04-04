#include "SRender.h"

SRender::SRender()
{
}

SRender::~SRender()
{
}

void SRender::Init()
{
	OpenglInit();
}

void SRender::OpenglInit()
{
}

void SRender::DirectX12Init()
{
}

void SRender::Run()
{
	while (true)
	{
		Tick();
	}
}

void SRender::Tick()
{
}
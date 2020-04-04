#pragma once

class SRender
{
public:
	SRender();
	~SRender();
	void Init();
	void Run();

private:
	void OpenglInit();
	void DirectX12Init();
	void Tick();
};

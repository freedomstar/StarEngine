#include "Define.h"
#include "Core/StarEngine/StarEngine.h"
#include "Editor/SWindow/MainEditorWindow.h"

int main(int args, char** AGR)
{
	StarEngine engine;
	engine.Run();
	engine.ShutDown();
	return 0;
}
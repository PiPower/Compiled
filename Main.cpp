#include <Windows.h>
#include "App.h"


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{
	App app(1500, 1100);
	app.DoFrame();
	return 0;
}
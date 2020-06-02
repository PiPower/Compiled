#include <Windows.h>
#include "App.h"


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{
	App app(1300, 1000);
	app.DoFrame();
	return 0;
}
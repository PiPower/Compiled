#include "App.h"
#include <complex>
using namespace std;

App::App(int width, int height)
{
	wnd = new Window(width, height);
	wnd->InitDX11();
	MS = new MandelbrotSet( wnd->Dx11 );
}

int App::DoFrame()
{
	while (true)
	{
		if ( auto code = wnd->ProcessMessages())
		{
			return code;
		}
		wnd->Dx11->BeginFrame();
		//-----------------------
		this->Logic();
		this->Draw();
		//-----------------------
		wnd->Dx11->EndFrame();
	}
}

void App::Logic()
{
	MS->Update(wnd);
}

void App::Draw()
{
	MS->Draw();
}


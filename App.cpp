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
	/*while (!wnd->IsKeyboardEventEmpty())
	{
		const auto e = wnd->ReadKeyEvent();
		if (e.Code == 'E' && e.Type == Window::KeyEvent::Event::Press)
		{
			scale -= 0.1*scale;
		}
		if (e.Code == 'Q' && e.Type == Window::KeyEvent::Event::Press)
		{
			scale += 0.1*scale;
		}
		if (e.Code == 'Z' && e.Type == Window::KeyEvent::Event::Press)
		{
			iterationLimit *= 2;
		}
		if (e.Code == VK_UP && e.Type == Window::KeyEvent::Event::Press)
		{

			Translation+=Vertex{ 0,-0.3*scale};
		}
		if (e.Code == VK_DOWN && e.Type == Window::KeyEvent::Event::Press)
		{

			Translation += Vertex{ 0,0.3 * scale };
		}
		if (e.Code == VK_LEFT && e.Type == Window::KeyEvent::Event::Press)
		{

			Translation += Vertex{- 0.3 * scale,0 };
		}
		if (e.Code == VK_RIGHT && e.Type == Window::KeyEvent::Event::Press)
		{
			Translation += Vertex{ 0.3 * scale,0 };
		}
	}*/
	MS->Update(wnd);
}

void App::Draw()
{
	MS->Draw();
}


#include "App.h"
#include <complex>
using namespace std;

App::App(int width, int height)
{
	wnd = new Window(width, height);
	wnd->InitDX11();
	MS = new MandelbrotSet( wnd->Dx11 );
	auto v1 = Vertex(-1.0f, -0.7f);
	auto v2 = Vertex(1.0f, -0.7f);
	KS = new KochSnowflake(v1, v2, wnd->Dx11);
	KF = new TriangleFractal(Vertex(0.0,1.0), Vertex(-0.5, -1.0), Vertex(0.5, -1.0),wnd->Dx11);
}

App::~App()
{
	delete KF;
	KF = nullptr;
	delete KS;
	KS = nullptr;
	delete MS;
	MS = nullptr;
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
	//MS->Update(wnd);
	//KS->Control(wnd);
}

void App::Draw()
{
//	MS->Draw();
	//KS->Draw();
	KF->Draw();
}


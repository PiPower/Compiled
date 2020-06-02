#include "TrojkatSierpinskiego.h"

int TrojkatSierpinskiego::iteration = 0;

void TrojkatSierpinskiego::Draw(Window* wnd) const
{
	wnd->Dx11->DrawLine(BotomLeft.X, BotomLeft.Y, BottomRight.X, BottomRight.Y, Color(255, 255, 255));
	wnd->Dx11->DrawLine(Top.X, Top.Y, BotomLeft.X, BotomLeft.Y, Color(255, 255, 255));
	wnd->Dx11->DrawLine( BottomRight.X, BottomRight.Y, Top.X, Top.Y, Color(255, 255, 255));

	for (auto& t : Children)
	{
		t.Draw(wnd);
	}
}

void TrojkatSierpinskiego::CreateChildren()
{
	if(!HasChildren)
		{
		Vertex MidLT = (BotomLeft + Top) / 2;
		Vertex MidLR = (BotomLeft + BottomRight) / 2;
		Vertex MidTR = (Top + BottomRight) / 2;
		Children.push_back(TrojkatSierpinskiego(MidLT ,BotomLeft, MidLR));
		Children.push_back(TrojkatSierpinskiego(MidTR, MidLR, BottomRight));
		Children.push_back(TrojkatSierpinskiego(Top, MidLT, MidTR));
		iteration++;
		HasChildren = true;
		}
	else
	{
		for (auto& t : Children)
		{
			t.CreateChildren();
		}
	}
}

void TrojkatSierpinskiego::Control(Window* wnd)
{
	while (!wnd->IsKeyboardEventEmpty())
	{
		const auto e = wnd->ReadKeyEvent();
		if (e.Code == 'E' && e.Type == Window::KeyEvent::Event::Press)
		{
			CreateChildren();
		}
		if (e.Code == 'W' && e.Type == Window::KeyEvent::Event::Press)
		{
			Scale(Vertex{ 1.1, 1.1 });
		}
		if (e.Code == 'S' && e.Type == Window::KeyEvent::Event::Press)
		{
			Scale(Vertex{ 0.9, 0.9 });
		}
		if (e.Code == VK_UP && e.Type == Window::KeyEvent::Event::Press)
		{

			Translation(Vertex{ 0,-3 });
		}
		if (e.Code == VK_DOWN && e.Type == Window::KeyEvent::Event::Press)
		{

			Translation(Vertex{ 0, 3 });
		}
		if (e.Code == VK_LEFT && e.Type == Window::KeyEvent::Event::Press)
		{

			Translation(Vertex{ -3,0 });
		}
		if (e.Code == VK_RIGHT && e.Type == Window::KeyEvent::Event::Press)
		{
			Translation(Vertex{ 3, 0 });
		}

	}
}

void TrojkatSierpinskiego::Scale(Vertex Scalar)
{


	BottomRight *= Scalar;
	BotomLeft *= Scalar;
	Top *= Scalar;

	for (auto& t : Children)
	{
		t.Scale(Scalar);
	}
}

void TrojkatSierpinskiego::Translation(Vertex Trans)
{
	BottomRight += Trans;
	BotomLeft += Trans;
	Top += Trans;
	for (auto& t : Children)
	{
		t.Translation(Trans);
	}
}


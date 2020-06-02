#include "KochSnowflake.h"
#include <vector>
using namespace std;

#define PI 3.141592653589
KochSnowflake::KochSnowflake(Vertex beg, Vertex end)
{
	vertex.emplace_back(beg);
	vertex.emplace_back(end);
	iteration++;
	ver = 2;
}

void KochSnowflake::Devide()
{
	for (auto i = vertex.begin(); i != prev(vertex.end(), 1); )
	{
		iteration++;
		Vertex step = (*next(i, 1) - *i) / 3;
		vector<Vertex> v;
		Vertex v1( *i + step);
		Vertex v2(*i + step * Vertex(2, 2));
       
		Vertex OffV (v2 - v1);
		Vertex vmid(OffV.X * cos(-PI / 3) - OffV.Y * sin(-PI / 3), OffV.X * sin(-PI / 3) + OffV.Y * cos(-PI / 3));
		vmid += v1;
		
		v.push_back(v1);
		v.push_back(vmid);
		v.push_back(v2);
		i++;
		vertex.insert(i, v.begin(), v.end());
		ver += 3;
	}

}

void KochSnowflake::Control(Window* wnd)
{
	while (!wnd->IsKeyboardEventEmpty())
	{
		const auto e = wnd->ReadKeyEvent();
		if (e.Code == 'E' && e.Type == Window::KeyEvent::Event::Press)
		{
		this->Devide();
		}
	}
}

void KochSnowflake::Draw(Window* wnd)
{
	for (auto i = vertex.begin(); i != prev(vertex.end(),1); i++)
	{
		wnd->Dx11->DrawLine(i->X, i->Y, next(i,1)->X, next(i, 1)->Y, Color(255, 255, 255));
	}
}

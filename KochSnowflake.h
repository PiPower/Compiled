#pragma once
#include "Window.h"
#include <list>
#include "Vertex.h"

class KochSnowflake
{
public:
	KochSnowflake()= default;
	KochSnowflake(Vertex beg, Vertex end);
	void Devide();
	void Control(Window* wnd);
	void Draw(Window* wnd);
private:
	std::list<Vertex> vertex;
	unsigned int iteration = 0;
	unsigned int ver;
};


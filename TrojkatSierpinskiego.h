#pragma once
#include "Window.h"
#include "Vertex.h"


class TrojkatSierpinskiego
{
public:
	TrojkatSierpinskiego() = default;
	TrojkatSierpinskiego(Vertex T, Vertex BL, Vertex BR)
		:
		Top(T), BotomLeft(BL), BottomRight(BR)
	{
		HasChildren = false;
		iteration++;
	}
	void Draw(Window* wnd) const;
	void CreateChildren();
	void Control(Window* wnd);
	void Scale(Vertex Scalar);
	void Translation(Vertex Trans);
private:
	std::vector<TrojkatSierpinskiego> Children;
	Vertex Top;
	Vertex BotomLeft;
	Vertex BottomRight;
	bool HasChildren;
	static int iteration;
};


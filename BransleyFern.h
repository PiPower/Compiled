#pragma once
#include "Window.h"
#include "Vertex.h"
#include "Graphics.h"
#include <list>

class BransleyFern
{
private:
	struct Point
	{
		float x, y;
		float r, g, b;
		Point(float x,float y,float r,float g,float b)
			:
			x(x),y(y),r(r),g(g),b(b)
		{}
		bool operator ==(const Point& rhs)
		{
			return x == rhs.x && y == rhs.y;
		}
	};
public:
	BransleyFern() = default;
	BransleyFern(Graphics * GFX,int IterationCount=10000);
	void Control(Window * wnd);
	void Draw();
private:
	Microsoft::WRL::ComPtr<ID3D11InputLayout> pInputLayout;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> pPixelShader;
	Microsoft::WRL::ComPtr<ID3D11VertexShader> pVertexShader;
	Microsoft::WRL::ComPtr<ID3D11Buffer> pVertexBuffer;
	D3D11_VIEWPORT   vp;

	std::vector<Point> Points;
	unsigned int iteration = 0;
	unsigned int PointCount = 0;
	Graphics* gfx = nullptr;

	double OffsetX = 0, OffsetY = 0;;
	double Scale = 1.0f;
};


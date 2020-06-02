#pragma once
#include "Graphics.h"
#include "Window.h"
#include <vector>
class MandelbrotSet
{
public:
	MandelbrotSet() = default;
	MandelbrotSet(Graphics* gfx);
	void Update(Window* wnd);
	void Draw();
private:
	struct Point
	{
		float x, y;
		float a, b;
	};
private:
	Microsoft::WRL::ComPtr<ID3D11InputLayout> pInputLayout;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> pPixelShader;
	Microsoft::WRL::ComPtr<ID3D11VertexShader> pVertexShader;
	Microsoft::WRL::ComPtr<ID3D11Buffer> pVertexBuffer;
	D3D11_VIEWPORT   vp;
	Graphics* gfx;
	std::vector<Point> Points;

	double OffsetX = 0, OffsetY = 0;;
	double Scale = 1.0f;
	int Iterations = 2;
};


#pragma once
#include "Window.h"
#include <list>
#include "Vertex.h"

class KochSnowflake
{
private:
	struct Point
	{
		float x,y;
		float r,g,b;
	};
public:
	KochSnowflake()= default;
	KochSnowflake(Vertex beg, Vertex end, Graphics* GFX);
	void Devide();
	void Control(Window* wnd);
	void Draw();
private:
	Microsoft::WRL::ComPtr<ID3D11InputLayout> pInputLayout;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> pPixelShader;
	Microsoft::WRL::ComPtr<ID3D11VertexShader> pVertexShader;
	Microsoft::WRL::ComPtr<ID3D11Buffer> pVertexBuffer;
	D3D11_VIEWPORT   vp;

	std::list<Vertex> vertex;
	unsigned int iteration = 0;
	unsigned int ver;
	Graphics* gfx = nullptr;
};


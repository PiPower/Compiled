#pragma once
#include "Window.h"
#include "Vertex.h"
#include "Graphics.h"
#include <list>
class TriangleFractal
{
private:
	struct Point
	{
		float x, y;
		float r, g, b;
	};
public:
	TriangleFractal() = default;
	TriangleFractal(Vertex T, Vertex BL, Vertex BR, Graphics* gfx);
	void Draw() const;
	void CreateChildren();
	void Control(Window* wnd);
	void Scale(Vertex Scalar);
	void Translation(Vertex Trans);
private:
	Microsoft::WRL::ComPtr<ID3D11InputLayout> pInputLayout;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> pPixelShader;
	Microsoft::WRL::ComPtr<ID3D11VertexShader> pVertexShader;
	Microsoft::WRL::ComPtr<ID3D11Buffer> pVertexBuffer;
	D3D11_VIEWPORT   vp;

	std::list<Vertex> vertex;
	Graphics* gfx = nullptr;
	bool HasChildren;
	static int iteration;
};


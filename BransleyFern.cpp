#include "BransleyFern.h"
#include <random>
#include <algorithm>

using namespace std;
using namespace Microsoft::WRL;
BransleyFern::BransleyFern(Graphics* GFX, int IterationCount)
	:
gfx(GFX)
{

	std::random_device rd;
	std::mt19937_64 gen(rd());
	std::uniform_int_distribution<int> unif(1, 100);

	float y = 0;
	float x = 0;

	for (int i = 0; i < IterationCount; i++)
	{
		float yn = y;
		float xn = x;
		Points.emplace_back(  2* ((x+2.1820)/4.8403) - 1 ,2*( y/9.983)-1, 0, 1, 0);
		//Points.emplace_back(x , y, 0, 1, 0);
		int result = unif(gen);
		if (result == 1)
		{
			x = 0;
			y = 0.16 * yn ;
		}
		else if (result <= 86)
		{
			x = 0.85 * xn + 0.04 * yn;
			y = -0.04 * xn + 0.85 * yn + 1.6;
		}
		else if (result <= 93)
		{
			x = 0.2 * xn - 0.26 * yn;
			y = 0.23 * xn + 0.22 * yn + 1.6;
		}
		else if (result <= 100)
		{
			x = -0.15*xn + 0.28 * yn;
			y = 0.26 * xn + 0.24 * yn + 0.44;
		}
	}

	HRESULT hr;

	unsigned int lol = Points.size() * sizeof(BransleyFern::Point);
	D3D11_BUFFER_DESC bd = {};
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.CPUAccessFlags = 0;
	bd.ByteWidth = Points.size() * sizeof(BransleyFern::Point);
	bd.StructureByteStride = sizeof(BransleyFern::Point);
	D3D11_SUBRESOURCE_DATA sbd = {};
	sbd.pSysMem = Points.data();
	gfx->pDevice->CreateBuffer(&bd, &sbd, &pVertexBuffer);

	ComPtr<ID3DBlob> pBlob;
	D3DReadFileToBlob(L"TriangleVS.cso", &pBlob);
	hr = gfx->pDevice->CreateVertexShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pVertexShader);

	const D3D11_INPUT_ELEMENT_DESC ied[]
	{
		{"Position",0,DXGI_FORMAT_R32G32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
		{"Color",0,DXGI_FORMAT_R32G32B32_FLOAT,0,8,D3D11_INPUT_PER_VERTEX_DATA,0}
	};
	gfx->pDevice->CreateInputLayout(ied, std::size(ied), pBlob->GetBufferPointer(), pBlob->GetBufferSize(), &pInputLayout);

	D3DReadFileToBlob(L"KSPS.cso", &pBlob);
	hr = gfx->pDevice->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pPixelShader);


	vp.Width = gfx->width;
	vp.Height = gfx->height;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
}

void BransleyFern::Control(Window* wnd)
{
	while (!wnd->IsKeyboardEventEmpty())
	{
		const auto e = wnd->ReadKeyEvent();
		if (e.Code == 'W' && e.Type == Window::KeyEvent::Event::Press)
		{
			Scale *= 1.1;

		}
		if (e.Code == 'S' && e.Type == Window::KeyEvent::Event::Press)
		{
			Scale *= 0.9;

		}
		if (e.Code == VK_UP && e.Type == Window::KeyEvent::Event::Press)
		{

			OffsetY -= 1/Scale * 0.3;
		}
		if (e.Code == VK_DOWN && e.Type == Window::KeyEvent::Event::Press)
		{

			OffsetY += 1/Scale * 0.3;
		}
		if (e.Code == VK_LEFT && e.Type == Window::KeyEvent::Event::Press)
		{

			OffsetX += 1/Scale * 0.3;

		}
		if (e.Code == VK_RIGHT && e.Type == Window::KeyEvent::Event::Press)
		{
			OffsetX -= 1/Scale * 0.3;

		}

	}
}

void BransleyFern::Draw()
{
	const UINT stride = sizeof(BransleyFern::Point);
	const UINT offset = 0u;

	HRESULT hr;
	struct ConstantBuffer
	{
		double dx, dy;
		double scale;
		double pad;
	};

	const ConstantBuffer cbuff{ OffsetX,OffsetY,Scale,0 };
	ComPtr<ID3D11Buffer>cbuffer;
	D3D11_BUFFER_DESC bd = {};
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bd.MiscFlags = 0;
	bd.ByteWidth = sizeof(cbuff);
	bd.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA sbd = {};
	sbd.pSysMem = &cbuff;
	hr = gfx->pDevice->CreateBuffer(&bd, &sbd, &cbuffer);


	gfx->pImmediateContext->IASetInputLayout(pInputLayout.Get());
	gfx->pImmediateContext->IASetVertexBuffers(0, 1, pVertexBuffer.GetAddressOf(), &stride, &offset);
	gfx->pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
	gfx->pImmediateContext->VSSetShader(pVertexShader.Get(), nullptr, 0u);
	gfx->pImmediateContext->VSSetConstantBuffers(0, 1, cbuffer.GetAddressOf());
	gfx->pImmediateContext->PSSetShader(pPixelShader.Get(), nullptr, 0u);
	gfx->pImmediateContext->OMSetRenderTargets(1, gfx->pRenderTargetView.GetAddressOf(), nullptr);
	gfx->pImmediateContext->RSSetViewports(1, &vp);
	gfx->pImmediateContext->Draw(Points.size() , 0u);
}
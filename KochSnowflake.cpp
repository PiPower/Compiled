#include "KochSnowflake.h"
#include <vector>
#include <math.h>
using namespace std;
using namespace Microsoft::WRL;

#define PI 3.141592653589

KochSnowflake::KochSnowflake(Vertex beg, Vertex end,Graphics* GFX)
	:
	gfx(GFX)
{
	vertex.emplace_back(beg);
	vertex.emplace_back(end);
	iteration++;

	std::vector<Point> Points;
	for (auto& p : vertex)
	{
		Points.push_back(KochSnowflake::Point{(float) p.X, (float) p.Y, 1.0f, 1.0f, 1.0f });
	}

	HRESULT hr;

	unsigned int lol = Points.size() * sizeof(KochSnowflake::Point);
	D3D11_BUFFER_DESC bd = {};
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.CPUAccessFlags = 0;
	bd.ByteWidth = Points.size() * sizeof(KochSnowflake::Point);
	bd.StructureByteStride = sizeof(KochSnowflake::Point);
	D3D11_SUBRESOURCE_DATA sbd = {};
	sbd.pSysMem = Points.data();
	gfx->pDevice->CreateBuffer(&bd, &sbd, &pVertexBuffer);

	ComPtr<ID3DBlob> pBlob;
	D3DReadFileToBlob(L"KSVS.cso", &pBlob);
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

void KochSnowflake::Devide()
{
	for (auto i = vertex.begin(); i != prev(vertex.end(), 1); )
	{
		iteration++;
		Vertex step = (*next(i, 1) - *i) / 3;
		//step.X = abs(step.X);
		//step.Y = abs(step.Y);

		vector<Vertex> v;
		Vertex v1( *i + step);
		Vertex v2(*i + step * Vertex(2, 2));
       
		Vertex OffV (v2 - v1);
		//OffV.X = abs(OffV.X);
		//OffV.Y = abs(OffV.Y);

		Vertex vmid(OffV.X * cos(PI / 3) - OffV.Y * sin(PI / 3), OffV.X * sin(PI / 3) + OffV.Y * cos(PI / 3));
		vmid += v1;
		
		v.push_back(v1);
		v.push_back(vmid);
		v.push_back(v2);
		i++;
		vertex.insert(i, v.begin(), v.end());
	}

	std::vector<Point> Points;
	for (auto& p : vertex)
	{
		Points.push_back(KochSnowflake::Point{ (float)p.X, (float)p.Y, 1.0f, 1.0f, 1.0f });
	}

	HRESULT hr;

	unsigned int lol = Points.size() * sizeof(KochSnowflake::Point);
	D3D11_BUFFER_DESC bd = {};
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.CPUAccessFlags = 0;
	bd.ByteWidth = Points.size() * sizeof(KochSnowflake::Point);
	bd.StructureByteStride = sizeof(KochSnowflake::Point);
	D3D11_SUBRESOURCE_DATA sbd = {};
	sbd.pSysMem = Points.data();
	gfx->pDevice->CreateBuffer(&bd, &sbd, &pVertexBuffer);

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

void KochSnowflake::Draw()
{
	const UINT stride = sizeof(KochSnowflake::Point);
	const UINT offset = 0u;


	gfx->pImmediateContext->IASetInputLayout(pInputLayout.Get());
	gfx->pImmediateContext->IASetVertexBuffers(0, 1, pVertexBuffer.GetAddressOf(), &stride, &offset);
	gfx->pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
	gfx->pImmediateContext->VSSetShader(pVertexShader.Get(), nullptr, 0u);
	gfx->pImmediateContext->PSSetShader(pPixelShader.Get(), nullptr, 0u);
	gfx->pImmediateContext->OMSetRenderTargets(1, gfx->pRenderTargetView.GetAddressOf(), nullptr);
	gfx->pImmediateContext->RSSetViewports(1, &vp);
	gfx->pImmediateContext->Draw(vertex.size(), 0u);
}

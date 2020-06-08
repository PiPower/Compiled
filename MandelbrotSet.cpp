#include "MandelbrotSet.h"

using namespace Microsoft::WRL;

MandelbrotSet::MandelbrotSet(Graphics* gfx)
	:
	gfx(gfx)
{
	HRESULT hr;
	for (int y = 0; y < gfx->height; y++)
	{
		for (int x = 0; x < gfx->width; x++)
		{
			float dx = (2 * (float)x) / gfx->width - 1;
			float dy = (-2 * (float)y) / gfx->height + 1;
			//if(dy == 1.0f) 	Points.push_back(Point{ dx, dy, 1,1 });
			Points.push_back(Point{ dx, dy, dx, dy});
		}
	}
	unsigned int lol = Points.size() * sizeof(MandelbrotSet::Point);
	D3D11_BUFFER_DESC bd = {};
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.CPUAccessFlags = 0;
	bd.ByteWidth = Points.size()*sizeof(MandelbrotSet::Point);
	bd.StructureByteStride = sizeof(Point);
	D3D11_SUBRESOURCE_DATA sbd = {};
	sbd.pSysMem = Points.data();
	gfx->pDevice->CreateBuffer(&bd, &sbd, &pVertexBuffer);

	ComPtr<ID3DBlob> pBlob;
	D3DReadFileToBlob(L"MsVs.cso", &pBlob);
	hr = gfx->pDevice->CreateVertexShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pVertexShader);

	const D3D11_INPUT_ELEMENT_DESC ied[]
	{
		{"Position",0,DXGI_FORMAT_R32G32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
		{"Color",0,DXGI_FORMAT_R32G32_FLOAT,0,8,D3D11_INPUT_PER_VERTEX_DATA,0}
	};
	gfx->pDevice->CreateInputLayout(ied, std::size(ied), pBlob->GetBufferPointer(), pBlob->GetBufferSize(), &pInputLayout);

	D3DReadFileToBlob(L"MsPs.cso", &pBlob);
	hr = gfx->pDevice->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pPixelShader);

	vp.Width = gfx->width;
	vp.Height = gfx->height;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
}

void MandelbrotSet::Update(Window* wnd)
{
	float dt = 0.25f;
	if (wnd->IsKeyPressed(VK_UP)) OffsetY += 0.1 * dt * Scale;
	if (wnd->IsKeyPressed(VK_DOWN)) OffsetY -= 0.1 * dt * Scale;
	if (wnd->IsKeyPressed(VK_LEFT)) OffsetX -= 0.1 * dt * Scale;
	if (wnd->IsKeyPressed(VK_RIGHT)) OffsetX += 0.1 * dt * Scale;

	if (wnd->IsKeyPressed('Q')) Scale *= 1.1f;
	if (wnd->IsKeyPressed('E')) Scale *= 0.95f;
	if (wnd->IsKeyPressed('W')) Iterations += 32;
	if (wnd->IsKeyPressed('S')) Iterations -= 32;
}

void MandelbrotSet::Draw()
{
	const UINT stride = sizeof(Point);
	const UINT offset = 0u;
	HRESULT hr;
	struct ConstantBuffer 
	{
		double dx, dy;
		double scale;
		int iterations;
	};

	const ConstantBuffer cbuff{ OffsetX,OffsetY,Scale,Iterations };
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
	hr=gfx->pDevice->CreateBuffer(&bd, &sbd, &cbuffer);


	gfx->pImmediateContext->IASetInputLayout(pInputLayout.Get());
	gfx->pImmediateContext->IASetVertexBuffers(0, 1, pVertexBuffer.GetAddressOf(), &stride, &offset);
	gfx->pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
	gfx->pImmediateContext->VSSetShader(pVertexShader.Get(), nullptr, 0u);
	gfx->pImmediateContext->PSSetShader(pPixelShader.Get(), nullptr, 0u);
	gfx->pImmediateContext->PSSetConstantBuffers(0, 1, cbuffer.GetAddressOf());
	gfx->pImmediateContext->OMSetRenderTargets(1, gfx->pRenderTargetView.GetAddressOf(), nullptr);
	gfx->pImmediateContext->RSSetViewports(1, &vp);
	gfx->pImmediateContext->Draw(Points.size(), 0u);
}

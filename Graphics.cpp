#include "Graphics.h"
#include <dxgi.h>
#include <algorithm>
#include <Windowsx.h>
#include <string>
#include <assert.h>

#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d2d1.lib")
#pragma comment(lib,"D3DCompiler.lib")
#pragma comment(lib,"DXGI.lib")
#pragma comment(lib,"dwrite.lib")

#pragma warning(disable : 4996).

using namespace Microsoft::WRL;
using namespace std;
Graphics::Graphics(HWND hwnd, int height, int width)
	:
	height(height), width(width),timer()
{
	assert(hwnd != nullptr);
	HRESULT hr;
	UINT flags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
//#ifdef NDEBUG
	flags |= D3D11_CREATE_DEVICE_DEBUG;
//#endif 
		DXGI_SWAP_CHAIN_DESC sd = {};
	sd.BufferCount = 1;
	sd.BufferDesc.Width = width;
	sd.BufferDesc.Height = height;
	sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 1;
	sd.BufferDesc.RefreshRate.Denominator = 60;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = hwnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;

	D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE,
		nullptr, flags, nullptr, 0, D3D11_SDK_VERSION,
		&sd, &pSwapChain, &pDevice, nullptr, &pImmediateContext);

	ComPtr<ID3D11Resource> pBackBuffer;
	pSwapChain->GetBuffer(0, __uuidof(ID3D11Resource), &pBackBuffer);
	pDevice->CreateRenderTargetView(pBackBuffer.Get(), nullptr, &pRenderTargetView);

	FLOAT dpiX;
	FLOAT dpiY;
	ComPtr<ID2D1Factory> m_pD2DFactory;
	Microsoft::WRL::ComPtr<IDXGISurface>         pBackBuffer2;

	D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, __uuidof(ID2D1Factory), &m_pD2DFactory);

	m_pD2DFactory->GetDesktopDpi(&dpiX, &dpiY);

	// Create a Direct2D render target which can draw into the surface in the swap chain

	pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer2));

	m_pD2DFactory->GetDesktopDpi(&dpiX, &dpiY);

	D2D1_RENDER_TARGET_PROPERTIES props =
		D2D1::RenderTargetProperties(
			D2D1_RENDER_TARGET_TYPE_DEFAULT,
			D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED),
			dpiX,
			dpiY
		);

	hr = m_pD2DFactory->CreateDxgiSurfaceRenderTarget(pBackBuffer2.Get(), &props, &d2RenderTarget);

	ComPtr<IDWriteFactory> pDWriteFactory;
		hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_ISOLATED,
		__uuidof(IDWriteFactory),&pDWriteFactory );

		hr =pDWriteFactory->CreateTextFormat( L"Gabriola",NULL, DWRITE_FONT_WEIGHT_REGULAR, DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL, 50.0f,	L"en-us",&TextFormat);

		hr = d2RenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White),&SolidColorBrush);
}

Graphics::~Graphics()
{
	if (pImmediateContext) pImmediateContext->ClearState();
}


void Graphics::EndFrame()
{
	HRESULT hr;
	int FPS = ((float)1/timer.Mark());
	wstring FPScounter = L"FPS: "+ to_wstring(FPS);
	D2D1_RECT_F layoutRect;
	layoutRect.left = 40;
	layoutRect.top = 0;
	layoutRect.right = 400;
	layoutRect.bottom = 40;
	d2RenderTarget->DrawText(FPScounter.c_str(), FPScounter.size(), TextFormat.Get(), &layoutRect, SolidColorBrush.Get());

	d2RenderTarget->EndDraw();
	// flip back/front buffers
	FAILED(hr = pSwapChain->Present(1u, 0u));

}



void Graphics::BeginFrame()
{
	const float color[] = { 0,0,0,0 };
	pImmediateContext->ClearRenderTargetView(pRenderTargetView.Get(), color);
	d2RenderTarget->BeginDraw();
}

void Graphics::Resize(HWND hwnd, int width, int height)
{
	/*HRESULT hr;

	this->width = width;
	this->height = height;

	DXGI_SWAP_CHAIN_DESC sd = {};
	sd.BufferCount = 1;
	sd.BufferDesc.Width = width;
	sd.BufferDesc.Height = height;
	sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 1;
	sd.BufferDesc.RefreshRate.Denominator = 60;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = hwnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;

	ComPtr<IDXGIFactory> pFactory;
	CreateDXGIFactory(__uuidof(IDXGIFactory), &pFactory);
	pFactory->CreateSwapChain(pDevice.Get(), &sd, &pSwapChain);

	_aligned_free(pSysBuffer);

	pSysBuffer = reinterpret_cast<unsigned int*>(
		_aligned_malloc(sizeof(unsigned int) * width * height, 16u));

	D3D11_VIEWPORT vp;
	vp.Width = width;
	vp.Height = height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0.0f;
	vp.TopLeftY = 0.0f;
	pImmediateContext->RSSetViewports(1, &vp);

	D3D11_TEXTURE2D_DESC textureDesc = {};
	textureDesc.Width = width;
	textureDesc.Height = height;
	textureDesc.MipLevels = 1;
	textureDesc.ArraySize = 1;
	textureDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.SampleDesc.Quality = 0;
	textureDesc.Usage = D3D11_USAGE_DYNAMIC;
	textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	textureDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	textureDesc.MiscFlags = 0;

	// create the texture
	hr = pDevice->CreateTexture2D(&textureDesc, nullptr, &pSysBufferTexture);

	assert(pSysBufferTexture.Get() != nullptr);

	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	srvDesc.Format = textureDesc.Format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = 1;
	// create the resource view on the texture
	hr = pDevice->CreateShaderResourceView(pSysBufferTexture.Get(),
		&srvDesc, &pSysBufferTextureView);

	ComPtr<ID3D11Resource> pBackBuffer;
	pSwapChain->GetBuffer(0, __uuidof(ID3D11Resource), &pBackBuffer);
	pDevice->CreateRenderTargetView(pBackBuffer.Get(), nullptr, &pRenderTargetView);

	pImmediateContext->OMSetRenderTargets(1, pRenderTargetView.GetAddressOf(), nullptr);*/
}


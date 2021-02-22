#include "pch.h"
#include "D2DRenderer.h"
#include <assert.h>
_Singleton_NULL(D2DRenderer)

D2DRenderer::D2DRenderer()
{
	CreateFactory();
	CreateRenderTarget();
}

D2DRenderer::~D2DRenderer()
{
	mD2DRenderTarget->Release();
	mD2DFactory->Release();
}

void D2DRenderer::CreateFactory()
{
	HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &mD2DFactory);
	assert(SUCCEEDED(hr));
}

void D2DRenderer::CreateRenderTarget()
{
	HRESULT hr;
	HDC hdc = GetDC(_hWnd);

	RECT clientRect;
	GetClientRect(_hWnd, &clientRect);
	float dpiX = (float)GetDeviceCaps(hdc, LOGPIXELSX);
	float dpiY = (float)GetDeviceCaps(hdc, LOGPIXELSY);
	D2D1_RENDER_TARGET_PROPERTIES prop =
		D2D1::RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_DEFAULT,
			D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED), dpiX, dpiY);
	D2D1_SIZE_U size = D2D1::SizeU(clientRect.right - clientRect.left,
		clientRect.bottom - clientRect.top);

	hr = mD2DFactory->CreateHwndRenderTarget
	(
		prop,
		D2D1::HwndRenderTargetProperties(_hWnd, size),
		&mD2DRenderTarget
	);
	assert(SUCCEEDED(hr));
}

void D2DRenderer::BeginRender(const D2D1::ColorF & backgroundColor)
{
	mD2DRenderTarget->BeginDraw();
	mD2DRenderTarget->Clear(backgroundColor);
}

void D2DRenderer::EndRender()
{
	mD2DRenderTarget->EndDraw();
}
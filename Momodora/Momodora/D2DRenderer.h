#pragma once

class D2DRenderer final
{
	_Singleton(D2DRenderer)

private:
	ID2D1Factory* mD2DFactory;
	ID2D1HwndRenderTarget* mD2DRenderTarget;
private:
	D2DRenderer();
	~D2DRenderer();

	void CreateFactory();
	void CreateRenderTarget();
public:
	void BeginRender(const D2D1::ColorF& backgroundColor);
	void EndRender();

	ID2D1RenderTarget* GetRenderTarget()const { return mD2DRenderTarget; }
};

#define D2DRENDERER D2DRenderer::GetInstance()
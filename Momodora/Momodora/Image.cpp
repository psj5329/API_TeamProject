#include "pch.h"
#include "Image.h"
#pragma comment(lib, "msimg32.lib")

Image::Image()
	: mImageBuffer(nullptr), mIsTrans(false), mBlendImageBuffer(nullptr), mBlendFunction(nullptr)
{
}

Image::~Image()
{
	ReleaseBuffer();
}

void Image::ReleaseBuffer()
{
	if (mImageBuffer != nullptr)
	{
		SelectObject(mImageBuffer->hdc, mImageBuffer->oldBitmap);
		DeleteObject(mImageBuffer->bitmap);
		DeleteDC(mImageBuffer->hdc);

		SelectObject(mBlendImageBuffer->hdc, mBlendImageBuffer->oldBitmap);
		DeleteObject(mBlendImageBuffer->bitmap);
		DeleteDC(mBlendImageBuffer->hdc);

		SafeDelete(mImageBuffer);
		SafeDelete(mBlendImageBuffer);
	}

	if (mBlendFunction != nullptr)
		SafeDelete(mBlendFunction);
}

bool Image::CreateEmpty(int width, int height)
{
	if (mImageBuffer != nullptr)
		ReleaseBuffer();

	HDC hdc = GetDC(_hWnd);

	mImageBuffer = new ImageBuffer();
	mImageBuffer->loadType = LoadType::Empty;
	mImageBuffer->registerID = 0;
	mImageBuffer->hdc = CreateCompatibleDC(hdc);
	mImageBuffer->bitmap = CreateCompatibleBitmap(hdc, width, height);
	mImageBuffer->oldBitmap = (HBITMAP)SelectObject(mImageBuffer->hdc, mImageBuffer->bitmap);
	mImageBuffer->width = width;
	mImageBuffer->height = height;

	mBlendFunction = new BLENDFUNCTION();
	mBlendFunction->BlendFlags = 0;
	mBlendFunction->AlphaFormat = 0;
	mBlendFunction->BlendOp = AC_SRC_OVER;

	mBlendImageBuffer = new ImageBuffer();
	mBlendImageBuffer->loadType = LoadType::Empty;
	mBlendImageBuffer->registerID = 0;
	mBlendImageBuffer->hdc = CreateCompatibleDC(hdc);
	mBlendImageBuffer->bitmap = CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	mBlendImageBuffer->oldBitmap = (HBITMAP)SelectObject(mBlendImageBuffer->hdc, mBlendImageBuffer->bitmap);
	mBlendImageBuffer->width = WINSIZEX;
	mBlendImageBuffer->height = WINSIZEY;

	ReleaseDC(_hWnd, hdc);

	if (mImageBuffer->bitmap == nullptr)
	{
		ReleaseBuffer();
		return false;
	}

	return true;
}

bool Image::LoadFromFile(wstring fileName, int width, int height, bool isTrans, COLORREF transColor)
{
	if (fileName.empty())
		return false;

	if (mImageBuffer != nullptr)
		ReleaseBuffer();

	HDC hdc = GetDC(_hWnd);

	mImageBuffer = new ImageBuffer();
	mImageBuffer->loadType = LoadType::File;
	mImageBuffer->registerID = 0;
	mImageBuffer->hdc = CreateCompatibleDC(hdc);
	mImageBuffer->bitmap = (HBITMAP)LoadImage(_hInstance, fileName.c_str(), IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	mImageBuffer->oldBitmap = (HBITMAP)SelectObject(mImageBuffer->hdc, mImageBuffer->bitmap);
	mImageBuffer->width = width;
	mImageBuffer->height = height;
	mImageBuffer->frameX = 1;
	mImageBuffer->frameY = 1;
	mImageBuffer->frameWidth = width;
	mImageBuffer->frameHeight = height;

	mBlendFunction = new BLENDFUNCTION();
	mBlendFunction->BlendFlags = 0;
	mBlendFunction->AlphaFormat = 0;
	mBlendFunction->BlendOp = AC_SRC_OVER;

	mBlendImageBuffer = new ImageBuffer();
	mBlendImageBuffer->loadType = LoadType::Empty;
	mBlendImageBuffer->registerID = 0;
	mBlendImageBuffer->hdc = CreateCompatibleDC(hdc);
	mBlendImageBuffer->bitmap = CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	mBlendImageBuffer->oldBitmap = (HBITMAP)SelectObject(mBlendImageBuffer->hdc, mBlendImageBuffer->bitmap);
	mBlendImageBuffer->width = WINSIZEX;
	mBlendImageBuffer->height = WINSIZEY;

	mFileName = fileName;

	mIsTrans = isTrans;
	mTransColor = transColor;

	ReleaseDC(_hWnd, hdc);

	if (mImageBuffer->bitmap == nullptr)
	{
		ReleaseBuffer();
		return false;
	}

	return true;
}

bool Image::LoadFromFile(wstring fileName, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	if (fileName.empty())
		return false;

	if (mImageBuffer != nullptr)
		ReleaseBuffer();

	HDC hdc = GetDC(_hWnd);

	mImageBuffer = new ImageBuffer();
	mImageBuffer->loadType = LoadType::File;
	mImageBuffer->registerID = 0;
	mImageBuffer->hdc = CreateCompatibleDC(hdc);
	mImageBuffer->bitmap = (HBITMAP)LoadImage(_hInstance, fileName.c_str(), IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	mImageBuffer->oldBitmap = (HBITMAP)SelectObject(mImageBuffer->hdc, mImageBuffer->bitmap);
	mImageBuffer->width = width;
	mImageBuffer->height = height;
	mImageBuffer->frameX = frameX;
	mImageBuffer->frameY = frameY;
	mImageBuffer->frameWidth = width / frameX;
	mImageBuffer->frameHeight = height / frameY;

	mBlendFunction = new BLENDFUNCTION();
	mBlendFunction->BlendFlags = 0;
	mBlendFunction->AlphaFormat = 0;
	mBlendFunction->BlendOp = AC_SRC_OVER;

	mBlendImageBuffer = new ImageBuffer();
	mBlendImageBuffer->loadType = LoadType::Empty;
	mBlendImageBuffer->registerID = 0;
	mBlendImageBuffer->hdc = CreateCompatibleDC(hdc);
	mBlendImageBuffer->bitmap = CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	mBlendImageBuffer->oldBitmap = (HBITMAP)SelectObject(mBlendImageBuffer->hdc, mBlendImageBuffer->bitmap);
	mBlendImageBuffer->width = WINSIZEX;
	mBlendImageBuffer->height = WINSIZEY;

	mFileName = fileName;

	mIsTrans = isTrans;
	mTransColor = transColor;

	ReleaseDC(_hWnd, hdc);

	if (mImageBuffer->bitmap == nullptr)
	{
		ReleaseBuffer();
		return false;
	}

	return true;
}

void Image::Render(HDC hdc, int x, int y)
{
	if (mIsTrans)
		GdiTransparentBlt(hdc, x, y, mImageBuffer->width, mImageBuffer->height,
			mImageBuffer->hdc, 0, 0, mImageBuffer->width, mImageBuffer->height, mTransColor);
	else
		BitBlt(hdc, x, y, mImageBuffer->width, mImageBuffer->height,
			mImageBuffer->hdc, 0, 0, SRCCOPY);
}

void Image::Render(HDC hdc, int x, int y, int tempX, int tempY, int tempWidth, int tempHeight)
{
	if (mIsTrans)
		GdiTransparentBlt(hdc, x, y, tempWidth, tempHeight,
			mImageBuffer->hdc, tempX, tempY, tempWidth, tempHeight, mTransColor);
	else
		BitBlt(hdc, x, y, tempWidth, tempHeight,
			mImageBuffer->hdc, tempX, tempY, SRCCOPY);
}

void Image::FrameRender(HDC hdc, int x, int y, int frameX, int frameY)
{
	if (mIsTrans)
		GdiTransparentBlt(hdc, x, y, mImageBuffer->frameWidth, mImageBuffer->frameHeight,
			mImageBuffer->hdc, mImageBuffer->frameWidth * frameX, mImageBuffer->frameHeight * frameY,
			mImageBuffer->frameWidth, mImageBuffer->frameHeight, mTransColor);
	else
		BitBlt(hdc, x, y, mImageBuffer->frameWidth, mImageBuffer->frameHeight,
			mImageBuffer->hdc, mImageBuffer->frameWidth * frameX, mImageBuffer->frameHeight * frameY, SRCCOPY);
}

void Image::AlphaRender(HDC hdc, int x, int y, float alpha)
{
	mBlendFunction->SourceConstantAlpha = (BYTE)(alpha * 255.f);

	if (mIsTrans)
	{
		BitBlt(mBlendImageBuffer->hdc, 0, 0, mImageBuffer->width, mImageBuffer->height,
			hdc, x, y, SRCCOPY);

		GdiTransparentBlt(mBlendImageBuffer->hdc, 0, 0, mImageBuffer->width, mImageBuffer->height,
			mImageBuffer->hdc, 0, 0, mImageBuffer->width, mImageBuffer->height, mTransColor);

		AlphaBlend(hdc, x, y, mImageBuffer->width, mImageBuffer->height,
			mBlendImageBuffer->hdc, 0, 0, mImageBuffer->width, mImageBuffer->height, *mBlendFunction);
	}
	else
		AlphaBlend(hdc, x, y, mImageBuffer->width, mImageBuffer->height,
			mImageBuffer->hdc, 0, 0, mImageBuffer->width, mImageBuffer->height, *mBlendFunction);
}

void Image::AlphaRender(HDC hdc, int x, int y, int tempX, int tempY, int tempWidth, int tempHeight, float alpha)
{
	mBlendFunction->SourceConstantAlpha = (BYTE)(alpha * 255.f);

	if (mIsTrans)
	{
		BitBlt(mBlendImageBuffer->hdc, 0, 0, mImageBuffer->width, mImageBuffer->height,
			hdc, x, y, SRCCOPY);

		GdiTransparentBlt(mBlendImageBuffer->hdc, 0, 0, tempWidth, tempHeight,
			mImageBuffer->hdc, tempX, tempY, tempWidth, tempHeight, mTransColor);

		AlphaBlend(hdc, x, y, mImageBuffer->width, mImageBuffer->height,
			mBlendImageBuffer->hdc, 0, 0, mImageBuffer->width, mImageBuffer->height, *mBlendFunction);
	}
	else
		AlphaBlend(hdc, x, y, tempWidth, tempHeight,
			mImageBuffer->hdc, 0, 0, mImageBuffer->width, mImageBuffer->height, *mBlendFunction);
}

void Image::AlphaFrameRender(HDC hdc, int x, int y, int frameX, int frameY, float alpha)
{
	mBlendFunction->SourceConstantAlpha = (BYTE)(alpha * 255.f);

	if (mIsTrans)
	{
		BitBlt(mBlendImageBuffer->hdc, 0, 0, mImageBuffer->frameWidth, mImageBuffer->frameHeight,
			hdc, x, y, SRCCOPY);

		GdiTransparentBlt(mBlendImageBuffer->hdc, 0, 0, mImageBuffer->frameWidth, mImageBuffer->frameHeight,
			mImageBuffer->hdc, mImageBuffer->frameWidth * frameX, mImageBuffer->frameHeight * frameY,
			mImageBuffer->frameWidth, mImageBuffer->frameHeight, mTransColor);

		AlphaBlend(hdc, x, y, mImageBuffer->frameWidth, mImageBuffer->frameHeight,
			mBlendImageBuffer->hdc, 0, 0, mImageBuffer->frameWidth, mImageBuffer->frameHeight, *mBlendFunction);
	}
	else
		AlphaBlend(hdc, x, y, mImageBuffer->frameWidth, mImageBuffer->frameHeight,
			mImageBuffer->hdc, 0, 0, mImageBuffer->frameWidth, mImageBuffer->frameHeight, *mBlendFunction);
}

void Image::ScaleRender(HDC hdc, int x, int y, int width, int height)
{
	if (mIsTrans)
		GdiTransparentBlt(hdc, x, y, width, height,
			mImageBuffer->hdc, 0, 0, mImageBuffer->width, mImageBuffer->height, mTransColor);
	else
		StretchBlt(hdc, x, y, width, height,
			mImageBuffer->hdc, 0, 0, mImageBuffer->width, mImageBuffer->height, SRCCOPY);
}

void Image::ScaleFrameRender(HDC hdc, int x, int y, int frameX, int frameY, int width, int height)
{
	if (mIsTrans)
		GdiTransparentBlt(hdc, x, y, width, height,
			mImageBuffer->hdc, mImageBuffer->frameWidth * frameX, mImageBuffer->frameHeight * frameY,
			mImageBuffer->frameWidth, mImageBuffer->frameHeight, mTransColor);
	else
		BitBlt(hdc, x, y, width, height,
			mImageBuffer->hdc, mImageBuffer->frameWidth * frameX, mImageBuffer->frameHeight * frameY, SRCCOPY);
}

void Image::AlphaScaleRender(HDC hdc, int x, int y, int width, int height, float alpha)
{
	mBlendFunction->SourceConstantAlpha = (BYTE)(alpha * 255.f);

	if (mIsTrans)
	{
		BitBlt(mBlendImageBuffer->hdc, 0, 0, width, height,
			hdc, x, y, SRCCOPY);

		GdiTransparentBlt(mBlendImageBuffer->hdc, 0, 0, width, height,
			mImageBuffer->hdc, 0, 0, mImageBuffer->width, mImageBuffer->height, mTransColor);

		AlphaBlend(hdc, x, y, width, height,
			mBlendImageBuffer->hdc, 0, 0, width, height, *mBlendFunction);
	}
	else
		AlphaBlend(hdc, x, y, width, height,
			mImageBuffer->hdc, 0, 0, mImageBuffer->width, mImageBuffer->height, *mBlendFunction);
}

void Image::AlphaScaleFrameRender(HDC hdc, int x, int y, int frameX, int frameY, int width, int height, float alpha)
{
	mBlendFunction->SourceConstantAlpha = (BYTE)(alpha * 255.f);

	if (mIsTrans)
	{
		BitBlt(mBlendImageBuffer->hdc, 0, 0, width, height,
			hdc, x, y, SRCCOPY);

		GdiTransparentBlt(mBlendImageBuffer->hdc, 0, 0, width, height,
			mImageBuffer->hdc, mImageBuffer->frameWidth * frameX, mImageBuffer->frameHeight * frameY,
			mImageBuffer->frameWidth, mImageBuffer->frameHeight, mTransColor);

		AlphaBlend(hdc, x, y, width, height,
			mBlendImageBuffer->hdc, 0, 0, width, height, *mBlendFunction);
	}
	else
		AlphaBlend(hdc, x, y, width, height,
			mImageBuffer->hdc, mImageBuffer->frameWidth * frameX, mImageBuffer->frameHeight * frameY,
			mImageBuffer->frameWidth, mImageBuffer->frameHeight, *mBlendFunction);
}
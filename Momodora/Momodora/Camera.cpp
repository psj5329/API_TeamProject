#include "pch.h"
#include "Camera.h"
#include "Image.h"

void Camera::Init()
{
	mX = WINSIZEX / 2;
	mY = WINSIZEY / 2;
	mSizeX = WINSIZEX;
	mSizeY = WINSIZEY;
	//mPosition.SetX(WINSIZEX / 2);
	//mPosition.SetY(WINSIZEY / 2);
	//mSize.SetX(WINSIZEX);
	//mSize.SetY(WINSIZEY);
	mRect = RectMakeCenter((int)mX, (int)mY, (int)mSizeX, (int)mSizeY);
	//mRect = RectMakeCenter((int)mPosition.GetX(), (int)mPosition.GetY(), (int)mSize.GetX(), (int)mSize.GetY());

	mMode = Mode::Free;
	mTarget = nullptr;
	mMoveSpeed = 5.f;
}

void Camera::Release()
{
}

void Camera::Update()
{
	switch (mMode)
	{
	case Camera::Mode::Follow:
		if (mTarget)
		{
			mX = mTarget->GetX();
			mY = mTarget->GetY();
			//mPosition.SetX(mTarget->GetX());
			//mPosition.SetY(mTarget->GetY());
			mRect = RectMakeCenter((int)mX, (int)mY, (int)mSizeX, (int)mSizeY);
			//mRect = RectMakeCenter((int)mPosition.GetX(), (int)mPosition.GetY(), (int)mSize.GetX(), (int)mSize.GetY());
		}
		break;
	case Camera::Mode::Free:
		if (INPUT->GetKey('A'))
			mX -= mMoveSpeed;
			//mPosition.SetX(mPosition.GetX() - mMoveSpeed);
		if (INPUT->GetKey('D'))
			mX += mMoveSpeed;
			//mPosition.SetX(mPosition.GetX() + mMoveSpeed);
		if (INPUT->GetKey('W'))
			mY -= mMoveSpeed;
			//mPosition.SetY(mPosition.GetY() - mMoveSpeed);
		if (INPUT->GetKey('S'))
			mY += mMoveSpeed;
			//mPosition.SetY(mPosition.GetY() + mMoveSpeed);
		mRect = RectMakeCenter((int)mX, (int)mY, (int)mSizeX, (int)mSizeY);
		//mRect = RectMakeCenter((int)mPosition.GetX(), (int)mPosition.GetY(), (int)mSize.GetX(), (int)mSize.GetY());
		break;
	}
}

void Camera::Render(HDC hdc)
{
}

void Camera::Render(HDC hdc, Image* image, int x, int y)
{
	image->Render(hdc, x - mRect.left, y - mRect.top);
}

void Camera::Render(HDC hdc, Image* image, int x, int y, int tempX, int tempY, int tempWidth, int tempHeight)
{
	image->Render(hdc, x - mRect.left, y - mRect.top, tempX, tempY, tempWidth, tempHeight);
}

void Camera::FrameRender(HDC hdc, Image* image, int x, int y, int frameX, int frameY)
{
	image->FrameRender(hdc, x - mRect.left, y - mRect.top, frameX, frameY);
}

void Camera::AlphaRender(HDC hdc, Image* image, int x, int y, float alpha)
{
	image->AlphaRender(hdc, x - mRect.left, y - mRect.top, alpha);
}

void Camera::AlphaFrameRender(HDC hdc, Image* image, int x, int y, int frameX, int frameY, float alpha)
{
	image->AlphaFrameRender(hdc, x - mRect.left, y - mRect.top, frameX, frameY, alpha);
}

void Camera::ScaleRender(HDC hdc, Image* image, int x, int y, int width, int height)
{
	image->ScaleRender(hdc, x - mRect.left, y - mRect.top, width, height);
}

void Camera::ScaleFrameRender(HDC hdc, Image* image, int x, int y, int frameX, int frameY, int width, int height)
{
	image->ScaleFrameRender(hdc, x - mRect.left, y - mRect.top, frameX, frameY, width, height);
}

void Camera::AlphaScaleRender(HDC hdc, Image* image, int x, int y, int width, int height, float alpha)
{
	image->AlphaScaleRender(hdc, x - mRect.left, y - mRect.top, width, height, alpha);
}

void Camera::AlphaScaleFrameRender(HDC hdc, Image* image, int x, int y, int frameX, int frameY, int width, int height, float alpha)
{
	image->AlphaScaleFrameRender(hdc, x - mRect.left, y - mRect.top, frameX, frameY, width, height, alpha);
}

void Camera::RenderRectInCamera(HDC hdc, RECT rect)
{
	rect.left -= mRect.left;
	rect.right -= mRect.left;
	rect.top -= mRect.top;
	rect.bottom -= mRect.top;
	RenderRect(hdc, rect);
}

void Camera::RenderEllipseInCamera(HDC hdc, float x, float y, float radius)
{
	RenderEllipse(hdc, (int)x - mRect.left, (int)y - mRect.top, (int)radius);
}

bool Camera::IsInCameraArea(float x, float y, float width, float height)
{
	RECT rect = RectMakeCenter((int)x, (int)y, (int)width, (int)height);
	return IsInCameraArea(rect);
}

bool Camera::IsInCameraArea(RECT rect)
{
	if (rect.left > mRect.right)
		return false;
	if (rect.right < mRect.left)
		return false;
	if (rect.top > mRect.bottom)
		return false;
	if (rect.bottom < mRect.top)
		return false;

	return true;
}
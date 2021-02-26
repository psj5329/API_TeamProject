#include "pch.h"
#include "Arrow.h"
#include "Image.h"
#include "Camera.h"
void Arrow::Init()
{

}

void Arrow::Fire(Image* image, float x, float y, float speed, float angle)
{
	mImage = image;
	mX = x;
	mY = y;
	mSpeed = speed;
	mAngle = angle;
	mRect = RectMakeCenter(mX, mY, mImage->GetFrameWidth(), mImage->GetFrameHeight());
	mArrowDamage = 2;
}

void Arrow::Release()
{
}

void Arrow::Update()
{
	mX += cosf(mAngle) * mSpeed * Time::GetInstance()->DeltaTime();
	mY -= sinf(mAngle) * mSpeed * Time::GetInstance()->DeltaTime();
	mRect = RectMakeCenter(mX, mY, mImage->GetFrameWidth(), mImage->GetFrameHeight());
}

void Arrow::Render(HDC hdc)
{
	//CAMERAMANAGER->GetMainCamera()->RenderRectInCamera(hdc, mRect);
	CameraManager::GetInstance()->GetMainCamera()->ScaleFrameRender(hdc, mImage, (int)mRect.left, (int)mRect.top, 0, mArrowIndexY, mImage->GetFrameWidth(), mImage->GetFrameHeight());
}
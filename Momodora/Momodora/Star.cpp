#include "pch.h"
#include "Star.h"

#include "Image.h"
#include "Camera.h"

void Star::Init()
{
	mName = "Star";
	mImage = IMAGEMANAGER->FindImage(L"Star");
	mX = WINSIZEX / 2;
	mY = WINSIZEY / 2;
	mSizeX = mImage->GetWidth() * 2;
	mSizeY = mImage->GetHeight() * 2;

	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);

	mSpeed = 10.f;
	mAngle = 0.f;
	mJumpPower = 10.f;
	mFirstJumpPower = mJumpPower;
}

void Star::Release()
{
}

void Star::Update()
{
	/*mY -= mJumpPower;
	mJumpPower -= 2.f;*/

	mX = cosf(mAngle) * mSpeed * TIME->DeltaTime();
	mY = sinf(mAngle) * mSpeed * TIME->DeltaTime() - 0.5f * 0.2f * TIME->DeltaTime() * TIME->DeltaTime();

	/*if (COLLISIONMANAGER->IsCollideWithPlatform(&mRect))
	{
		
	}*/
}

void Star::Render(HDC hdc)
{
#ifdef DEBUG
	CAMERAMANAGER->GetMainCamera()->RenderRectInCamera(hdc, mRect);
#endif // DEBUG
	CAMERAMANAGER->GetMainCamera()->ScaleRender(hdc, mImage, mRect.left, mRect.top, mSizeX, mSizeY);
}

#include "pch.h"
#include "StarItem.h"

#include "Image.h"
#include "Camera.h"

void StarItem::Init()
{
	mName = "Star";
	mImage = IMAGEMANAGER->FindImage(L"Star");
	mX = WINSIZEX / 2;
	mY = WINSIZEY / 2;
	mSizeX = mImage->GetWidth();
	mSizeY = mImage->GetHeight();

	mSpeed = 200.f;
	mAngle = 0.f;
	mJumpPower = 3.f;
	mFirstJumpPower = mJumpPower;

	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
}

void StarItem::Release()
{
}

void StarItem::Update()
{
	if (mFirstJumpPower >= 0.01f)
	{
		mX += cosf(mAngle) * mSpeed * TIME->DeltaTime();
		mY += -sinf(mAngle) * mSpeed * TIME->DeltaTime() - mJumpPower;
		mJumpPower -= 0.3f;

		if (mJumpPower < 0.f)
			mIsJump = false;
	}

	if (COLLISIONMANAGER->IsCollideWithPlatform(&mRect))
	{
		if (!mIsJump)
		{
			mIsJump = true;
			mJumpPower = mFirstJumpPower / 3;
			mFirstJumpPower = mJumpPower;
		}
	}

	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
}

void StarItem::Render(HDC hdc)
{
#ifdef DEBUG
	CAMERAMANAGER->GetMainCamera()->RenderRectInCamera(hdc, mRect);
#endif // DEBUG

	CAMERAMANAGER->GetMainCamera()->ScaleRender(hdc, mImage, mRect.left, mRect.top, mSizeX, mSizeY);
}

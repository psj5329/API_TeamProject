#include "pch.h"
#include "StarItem.h"

#include "Image.h"
#include "Camera.h"
#include "StarCountUI.h"

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

	mIsColl = false;
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
		mJumpPower -= 0.2f;

		if (mJumpPower < 0.f)
			mIsJump = false;
	}

	int col = 0;

	if (COLLISIONMANAGER->IsCollision(&mRect, ObjectLayer::Platform, col))
	{
		if (col == 1)
		{		
			// 상하 충돌
			if (!mIsJump)
			{
				mIsJump = true;
				mJumpPower = mFirstJumpPower / 3;
				mFirstJumpPower = mJumpPower;
			}
		}
		else if(col == 2)
		{
			// 좌우 충돌
			if (!mIsColl)
			{
				mIsColl = true;
				mAngle = PI - mAngle;
			}
		}
	}

	// 얘는 충돌 판정받고 ui만 바뀐ㄴ거라 ㅆㄴ에 없어도 될 듯
	if (COLLISIONMANAGER->IsCollision(&mRect, ObjectLayer::Player))
	{
		mIsActive = false;
		((StarCountUI*)OBJECTMANAGER->FindObject("StarCountUI"))->SetStarCount(
			((StarCountUI*)OBJECTMANAGER->FindObject("StarCountUI"))->GetStarCount() + 1);
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

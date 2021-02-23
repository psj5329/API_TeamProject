#include "pch.h"
#include "Bomb.h"
#include "Animation.h"
#include "Image.h"
#include "Camera.h"

void Bomb::Init()
{


}

void Bomb::Init(int x, int y, float angle, float targetX, float targetY)
{
	IMAGEMANAGER->LoadFromFile(L"Bomb", Resources(L"Bomb"), 64, 32, 4, 2, true);
	IMAGEMANAGER->LoadFromFile(L"Fire", Resources(L"Explosion"), 560, 62, 8, 1, true);
	mImage = IMAGEMANAGER->FindImage(L"Bomb");
	

	mX = x;
	mY = y;
	mAngle = angle;
	mSpeed = 400;
	mSizeX = mImage->GetFrameWidth() * 2;
	mSizeY = mImage->GetFrameHeight() * 2;
	mTargetX = targetX;
	mTargetY = targetY;
	mStartX = x;
	mStartY = y;
	mGravity = 2;
	mFrameCount = 0;

	mRightMove = new Animation();
	mRightMove->InitFrameByStartEnd(0, 0, 0, 0, false);
	mRightMove->SetIsLoop(false);
	mRightMove->SetFrameUpdateTime(0.2f);

	mLeftMove = new Animation();
	mLeftMove->InitFrameByStartEnd(0, 1, 0, 1, false);
	mLeftMove->SetIsLoop(false);
	mLeftMove->SetFrameUpdateTime(0.2f);

	if (mAngle > PI / 2)
	{
		mCurrentAnimation = mLeftMove;
	}
	else
	{
		mCurrentAnimation = mRightMove;
	}


}

void Bomb::Release()
{


}

void Bomb::Update()
{
	
	mFrameCount += TIME->DeltaTime();
	//mX = mStartX + cosf(mAngle) * mSpeed * mFrameCount;
	//mY = mStartY + sinf(mAngle) * mSpeed * mFrameCount - ((mGravity / 2) * mFrameCount * mFrameCount);

	mX += cosf(mAngle) * mSpeed * TIME->DeltaTime();
	mY -= sinf(mAngle) * mSpeed * TIME->DeltaTime();
	mY += mGravity * TIME->DeltaTime();
	mGravity += 8.f;


	//어디 부딛히면
	//explode();
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	mCurrentAnimation->Update();
}

	
void Bomb::Render(HDC hdc)
{
	CAMERAMANAGER->GetMainCamera()->ScaleFrameRender(hdc, mImage, mRect.left, mRect.top, mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY(), mSizeX, mSizeY);
}

void Bomb::Explode()
{
	mImage = IMAGEMANAGER->FindImage(L"Fire");

}
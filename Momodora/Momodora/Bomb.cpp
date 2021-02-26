#include "pch.h"
#include "Bomb.h"
#include "Animation.h"
#include "Image.h"
#include "Camera.h"
#include "GameObject.h"

void Bomb::Init()
{


}

void Bomb::Init(int x, int y, float angle, float targetX, float targetY)
{
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
	mIsExplode = false;
	mAtk = 20;

	mRightMove = new Animation();
	mRightMove->InitFrameByStartEnd(0, 0, 3, 0, false);
	mRightMove->SetIsLoop(true);
	mRightMove->SetFrameUpdateTime(0.2f);

	mLeftMove = new Animation();
	mLeftMove->InitFrameByStartEnd(0, 1, 3, 1, false);
	mLeftMove->SetIsLoop(true);
	mLeftMove->SetFrameUpdateTime(0.2f);

	mExplosion = new Animation();
	mExplosion->InitFrameByStartEnd(0, 0, 7, 0, false);
	mExplosion->SetIsLoop(false);
	mExplosion->SetFrameUpdateTime(0.1f);
	mExplosion->SetCallbackFunc(bind(&Bomb::EndExplosion, this));
	if (mAngle > PI / 2)
	{
		mCurrentAnimation = mLeftMove;
	}
	else
	{
		mCurrentAnimation = mRightMove;
	}
	mCurrentAnimation->Play();

}

void Bomb::Release()
{
	SafeDelete(mRightMove);
	SafeDelete(mLeftMove);
	SafeDelete(mExplosion);

}

void Bomb::Update()
{
	
	mFrameCount += TIME->DeltaTime();
	//mX = mStartX + cosf(mAngle) * mSpeed * mFrameCount;
	//mY = mStartY + sinf(mAngle) * mSpeed * mFrameCount - ((mGravity / 2) * mFrameCount * mFrameCount);
	if (!mIsExplode)
	{

		mX += cosf(mAngle) * mSpeed * TIME->DeltaTime();
		mY -= sinf(mAngle) * mSpeed * TIME->DeltaTime();
		mY += mGravity * TIME->DeltaTime();
		mGravity += 8.f;
	}


	//어디 부딛히면
	if (COLLISIONMANAGER->IsCollideWithPlatform(&mRect) && !mIsExplode)
	{
		Explode();
		mIsExplode = true;
	}

	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	if (!mIsExplode)
		mHitBox = RectMakeCenter(mX, mY, 30, 30);
	else
		mHitBox = RectMakeCenter(mX, mY, 120, 120);
	mCurrentAnimation->Update();
}

	
void Bomb::Render(HDC hdc)
{
	CAMERAMANAGER->GetMainCamera()->RenderRectInCamera(hdc, mHitBox);
	CAMERAMANAGER->GetMainCamera()->ScaleFrameRender(hdc, mImage, mRect.left, mRect.top, mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY(), mSizeX, mSizeY);
}

void Bomb::Explode()
{
	mImage = IMAGEMANAGER->FindImage(L"Fire");
	mIsExplode = true;
	mSizeX = mImage->GetFrameWidth() * 3;
	mSizeY = mImage->GetFrameHeight() * 3;
	mCurrentAnimation->Stop();
	mCurrentAnimation = mExplosion;
	mCurrentAnimation->Play();
	mY = mRect.top - 50;
}

void Bomb::EndExplosion()
{
	mRect = RectMakeCenter(2000, 2000, 1, 1);
	this->SetIsActive(false);
}
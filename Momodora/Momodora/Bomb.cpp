#include "pch.h"
#include "Bomb.h"
#include "Animation.h"
#include "Image.h"

void Bomb::Init()
{


}

void Bomb::Init(int x, int y, float angle, float targetX, float targetY)
{
	IMAGEMANAGER->LoadFromFile(L"Dagger", Resources(L"Dagger"), 16, 32, 1, 2, true);
	IMAGEMANAGER->LoadFromFile(L"Fire", Resources(L"Explosion"), 560, 62, 8, 1, true);
	mImage = IMAGEMANAGER->FindImage(L"Dagger");
	

	mX = x;
	mY = y;
	mAngle = angle;
	mSpeed = 350;
	mSizeX = mImage->GetFrameWidth() * 2;
	mSizeY = mImage->GetFrameHeight() * 2;
	mTargetX = targetX;
	mTargetY = targetY;

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


}

	
void Bomb::Render(HDC hdc)
{


}
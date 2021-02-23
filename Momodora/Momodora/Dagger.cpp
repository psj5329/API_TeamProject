#include "pch.h"
#include "Dagger.h"
#include "Image.h"
#include "Camera.h"
#include "Animation.h"
void Dagger::Init()
{


}
void Dagger::Init(int x,int y, float angle)
{
	IMAGEMANAGER->LoadFromFile(L"Dagger", Resources(L"Dagger"), 16, 32, 1, 2, true);
	mImage = IMAGEMANAGER->FindImage(L"Dagger");

	mX = x;
	mY = y;
	mAngle = angle;
	mSpeed = 350;
	mSizeX = mImage->GetFrameWidth() * 2;
	mSizeY = mImage->GetFrameHeight() * 2;

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

void Dagger::Release()
{
	SafeDelete(mRightMove);
	SafeDelete(mLeftMove);

}

void Dagger::Update()
{
	mX += cosf(mAngle) * mSpeed * TIME->DeltaTime();

	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
}


void Dagger::Render(HDC hdc)
{
	CAMERAMANAGER->GetMainCamera()->ScaleFrameRender(hdc, mImage, mRect.left, mRect.top, mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY(), mSizeX, mSizeY);
}
#include "pch.h"
#include "Staff.h"
#include "Animation.h"
#include "Image.h"
#include "Camera.h"
void Staff::Init()
{
	mImage = IMAGEMANAGER->FindImage(L"Staff");

	mReturn = false;
	mSizeX = mImage->GetFrameWidth() * 2;
	mSizeY = mImage->GetFrameHeight() * 2;

	mRightMove = new Animation();
	mRightMove->InitFrameByStartEnd(0, 0, 3, 0, false);
	mRightMove->SetIsLoop(true);
	mRightMove->SetFrameUpdateTime(0.1f);

	mLeftMove = new Animation();
	mLeftMove->InitFrameByStartEnd(0, 0, 3, 0, true);
	mLeftMove->SetIsLoop(true);
	mLeftMove->SetFrameUpdateTime(0.1f);
	mCurrentAnimation = mLeftMove;


}
void Staff::Init(int x, int y, float angle)
{
	
	mX = x;
	mY = y;
	mStart.x = x;
	mStart.y = y;
	mAngle = angle;
	mSpeed = 330;
	mReturn = false;
	mDistance = 3;
	mAtk = 25;

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

void Staff::Release()
{
	SafeDelete(mRightMove);
	SafeDelete(mLeftMove);

}

void Staff::Update()
{
	mX += cosf(mAngle) * mSpeed * TIME->DeltaTime();
	mY -= sinf(mAngle) * mSpeed * TIME->DeltaTime();

	//초새기
	mDistance-=TIME->DeltaTime();
	
	//4초후 방향전환
	if (mDistance < 0 && !mReturn)
	{
		mReturn = true;
		mSpeed *= -1;
		
		//if (mCurrentAnimation == mLeftMove)
		//{
		//	mCurrentAnimation->Stop();
		//	mCurrentAnimation = mRightMove;
		//	mCurrentAnimation->Play();
		//}
		//else
		//{
		//	mCurrentAnimation->Stop();
		//	mCurrentAnimation = mLeftMove;
		//	mCurrentAnimation->Play();
		//}
	}
	
	
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	mCurrentAnimation->Update();
}


void Staff::Render(HDC hdc)
{
	CAMERAMANAGER->GetMainCamera()->RenderRectInCamera(hdc, mRect);
	CAMERAMANAGER->GetMainCamera()->ScaleFrameRender(hdc, mImage, mRect.left, mRect.top, mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY(), mSizeX, mSizeY);
}
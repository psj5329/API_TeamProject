#include "pch.h"
#include "Monkey.h"
#include "Image.h"
#include "Camera.h"
//#include "Animation.h"
//#include "Player.h"

void Monkey::Init()
{
	IMAGEMANAGER->LoadFromFile(L"Monkey", Resources(L"Monkey"), 720, 288, 9, 6, true);
	mImage = IMAGEMANAGER->FindImage(L"Monkey");
	mStart.x = WINSIZEX / 2;
	mStart.y = WINSIZEY / 2;
	mX = mStart.x;
	mY = mStart.y;
	mSizeX = mImage->GetFrameWidth();
	mSizeY = mImage->GetFrameHeight();
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	mHitBox = RectMakeCenter(mX, mY, 50, 50);
	mSearchZone = RectMakeCenter(mX - 150, mY - 150, 300, 300);

	mSpeed = 100;
	mAttackSpeed = 100;
	mAtk = 5;
	mDef = 5;
	mHp = 100;
	mRange = 300;

	mFoundPlayer = false;
	mDirection = Direction::Left;
	mEnemyState = EnemyState::Move;
}

void Monkey::Release()
{


}

void Monkey::Update()
{
	if (mFoundPlayer)
	{
		//거리가 멀면
		//플레이어로 이동

		//거리가 가까우면
		//공격!
	}
	else
	{
		if (mEnemyState == EnemyState::Move)
		{
			Patrol();
		}

		SearchPlayer();

	}
	



	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	mHitBox = RectMakeCenter(mX, mY, 100, 100);
}

void Monkey::Render(HDC hdc)
{

	//에니메이션 추가해야함
	CAMERAMANAGER->GetMainCamera()->FrameRender(hdc, mImage, mRect.left, mRect.top, 0, 0);
}

void Monkey::Patrol()
{
	mX += mSpeed * TIME->DeltaTime();
	if (mSpeed < 0) {
		mDirection = Direction::Left;
	}
	else {
		mDirection = Direction::Right;
	}

	if (mX < mStart.x - mRange)
	{
		mSpeed *= -1;
	}
	if (mX > mStart.x + mRange)
	{
		mSpeed *= -1;
	}
}

void Monkey::SearchPlayer()
{
	//플레이어가 searchzone 에 들어오면
	//mFoundPlayer = true;

}
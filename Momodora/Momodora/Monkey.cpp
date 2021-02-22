#include "pch.h"
#include "Monkey.h"
#include "Image.h"
#include "Camera.h"
#include "Animation.h"
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

	mSpeed = 70;
	mAttackSpeed = 100;
	mAtk = 5;
	mDef = 5;
	mHp = 100;
	mRange = 300;

	mFoundPlayer = false;
	mDirection = Direction::Left;
	mEnemyState = EnemyState::Move;

	//애니메이션
	mRightMove = new Animation();
	mRightMove->InitFrameByStartEnd(0, 0, 5, 0, false);
	mRightMove->SetIsLoop(true);
	mRightMove->SetFrameUpdateTime(0.2f);

	mLeftMove = new Animation();
	mLeftMove->InitFrameByStartEnd(0, 1, 5, 1, false);
	mLeftMove->SetIsLoop(true);
	mLeftMove->SetFrameUpdateTime(0.2f);

	mRightAtk = new Animation();
	mRightAtk->InitFrameByStartEnd(0, 2, 8, 2, false);
	mRightAtk->SetIsLoop(false);
	mRightAtk->SetFrameUpdateTime(0.2f);

	mLeftAtk = new Animation();
	mLeftAtk->InitFrameByStartEnd(0, 3, 8, 3, false);
	mLeftAtk->SetIsLoop(false);
	mLeftAtk->SetFrameUpdateTime(0.2f);

	mRightHurt = new Animation();
	mRightHurt->InitFrameByStartEnd(0, 4, 0, 4, false);
	mRightHurt->SetIsLoop(false);
	mRightHurt->SetFrameUpdateTime(0.2f);

	mLeftHurt = new Animation();
	mLeftHurt->InitFrameByStartEnd(0, 5, 0, 5, false);
	mLeftHurt->SetIsLoop(false);
	mLeftHurt->SetFrameUpdateTime(0.2f);
	
	mCurrentAnimation = mRightMove;
	mCurrentAnimation->Play();
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
	
	//얻어맞았으면 
	if (true)
	{

	}

	mCurrentAnimation->Update();


	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	mHitBox = RectMakeCenter(mX, mY, 100, 100);
}

void Monkey::Render(HDC hdc)
{

	//에니메이션 추가해야함
	CAMERAMANAGER->GetMainCamera()->FrameRender(hdc, mImage, mRect.left, mRect.top, mCurrentAnimation->GetNowFrameX(),mCurrentAnimation->GetNowFrameY());
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
		mCurrentAnimation->Stop();
		mCurrentAnimation = mRightMove;
		mCurrentAnimation->Play();
	}
	if (mX > mStart.x + mRange)
	{
		mSpeed *= -1;
		mCurrentAnimation->Stop();
		mCurrentAnimation = mLeftMove;
		mCurrentAnimation->Play();
	}
}

void Monkey::SearchPlayer()
{
	//플레이어가 searchzone 에 들어오면
	//mFoundPlayer = true;

}
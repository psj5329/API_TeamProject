#include "pch.h"
#include "BombImp.h"
#include "Image.h"
#include "Animation.h"
#include "Camera.h"

void BombImp::Init()
{
	IMAGEMANAGER->LoadFromFile(L"Imp", Resources(L"Imp"), 320, 384, 10, 12, true);
	mImage = IMAGEMANAGER->FindImage(L"Imp");

	mStart.x = WINSIZEX / 2;
	mStart.y = WINSIZEY / 2;
	mX = mStart.x;
	mY = mStart.y;
	mSizeX = mImage->GetFrameWidth();
	mSizeY = mImage->GetFrameHeight();
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	mHitBox = RectMakeCenter(mX, mY, 50, 50);
	mAttackSpeed = 0;

	mRightIdle = new Animation();
	mRightIdle->InitFrameByStartEnd(0, 0, 0, 0, false);
	mRightIdle->SetIsLoop(false);
	mRightIdle->SetFrameUpdateTime(0.2f);

	mLeftIdle = new Animation();
	mLeftIdle->InitFrameByStartEnd(0, 1, 0, 1, false);
	mLeftIdle->SetIsLoop(false);
	mLeftIdle->SetFrameUpdateTime(0.2f);

	mRightAtk = new Animation();
	mRightAtk->InitFrameByStartEnd(0, 8, 8, 8, false);
	mRightAtk->SetIsLoop(true);
	mRightAtk->SetFrameUpdateTime(0.2f);
	//mRightAtk->SetCallbackFunc(*(function<void(void)>)EndThrow);

	mLeftAtk = new Animation();
	mLeftAtk->InitFrameByStartEnd(0, 9, 8, 9, false);
	mLeftAtk->SetIsLoop(true);
	mLeftAtk->SetFrameUpdateTime(0.2f);

	mRightHurt = new Animation();
	mRightHurt->InitFrameByStartEnd(0, 10, 0, 10, false);
	mRightHurt->SetIsLoop(false);
	mRightHurt->SetFrameUpdateTime(0.2f);

	mLeftHurt = new Animation();
	mLeftHurt->InitFrameByStartEnd(0, 11, 0, 11, false);
	mLeftHurt->SetIsLoop(false);
	mLeftHurt->SetFrameUpdateTime(0.2f);

	mEnemyState = EnemyState::Idle;
	mDirection = Direction::Left;
	mCurrentAnimation = mLeftIdle;
}

void BombImp::Release()
{


}

void BombImp::Update()
{
	mAttackSpeed += TIME->DeltaTime();

	if (mAttackSpeed > 5)
	{
		mAttackSpeed = 0;
		mEnemyState = EnemyState::Attack;
		SetAnimation();
		ThrowBomb();
	}

	//if(mCurr == 해당모션 && mCurr->getisplay() == false)
	//{EndThrow();}
	
	mCurrentAnimation->Update();

	SearchPlayer();
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
}

void BombImp::Render(HDC hdc)
{
	CAMERAMANAGER->GetMainCamera()->FrameRender(hdc, mImage, mRect.left, mRect.top, mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY());
}

void BombImp::SearchPlayer()
{
	//플레이어가 searchzone 에 들어오면
	//방향설정

}

void BombImp::ThrowBomb()
{


}

void BombImp::EndThrow()
{
	mEnemyState = EnemyState::Idle;
	SetAnimation();
}
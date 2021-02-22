#include "pch.h"
#include "Witch.h"
#include "Image.h"
#include "Animation.h"
#include "Camera.h"

void Witch::Init()
{
	IMAGEMANAGER->LoadFromFile(L"Witchcatch", Resources(L"Enemy/Witchcatch"), 490, 192, 5, 2, true);
	IMAGEMANAGER->LoadFromFile(L"Witchcatch", Resources(L"Enemy/Witchdeath"), 528, 128, 8, 2, true);
	IMAGEMANAGER->LoadFromFile(L"Witchcatch", Resources(L"Enemy/Witchdeath2"), 528, 128, 8, 2, true);
	IMAGEMANAGER->LoadFromFile(L"Witchcatch", Resources(L"Enemy/Witchhurt"), 66, 128, 1, 2, true);
	IMAGEMANAGER->LoadFromFile(L"Witchcatch", Resources(L"Enemy/Witchhurt2"), 66, 128, 1, 2, true);
	IMAGEMANAGER->LoadFromFile(L"Witchcatch", Resources(L"Enemy/Witchidle"), 330, 128, 5, 2, true);
	IMAGEMANAGER->LoadFromFile(L"Witchcatch", Resources(L"Enemy/Witchidle2"), 330, 128, 5, 2, true);
	IMAGEMANAGER->LoadFromFile(L"Witchcatch", Resources(L"Enemy/Witchthrow"), 594, 128, 9, 2, true);

	mImage = IMAGEMANAGER->FindImage(L"ShieldImp");

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

	mRightMove = new Animation();
	mRightMove->InitFrameByStartEnd(0, 2, 4, 2, false);
	mRightMove->SetIsLoop(false);
	mRightMove->SetFrameUpdateTime(0.2f);

	mLeftMove = new Animation();
	mLeftMove->InitFrameByStartEnd(0, 3, 4, 2, false);
	mLeftMove->SetIsLoop(false);
	mLeftMove->SetFrameUpdateTime(0.2f);

	mRightAtk = new Animation();
	mRightAtk->InitFrameByStartEnd(0, 4, 7, 4, false);
	mRightAtk->SetIsLoop(true);
	mRightAtk->SetFrameUpdateTime(0.2f);
	//mRightAtk->SetCallbackFunc(*(function<void(void)>)EndThrow);

	mLeftAtk = new Animation();
	mLeftAtk->InitFrameByStartEnd(0, 5, 7, 5, false);
	mLeftAtk->SetIsLoop(true);
	mLeftAtk->SetFrameUpdateTime(0.2f);

	mRightHurt = new Animation();
	mRightHurt->InitFrameByStartEnd(0, 6, 0, 6, false);
	mRightHurt->SetIsLoop(false);
	mRightHurt->SetFrameUpdateTime(0.2f);

	mLeftHurt = new Animation();
	mLeftHurt->InitFrameByStartEnd(0, 7, 0, 7, false);
	mLeftHurt->SetIsLoop(false);
	mLeftHurt->SetFrameUpdateTime(0.2f);

	mEnemyState = EnemyState::Idle;
	mDirection = Direction::Left;
	mCurrentAnimation = mLeftIdle;
}

void Witch::Release()
{


}

void Witch::Update()
{
	mAttackSpeed += TIME->DeltaTime();

	if (mAttackSpeed > 5)
	{
		mAttackSpeed = 0;
		mEnemyState = EnemyState::Attack;
		SetAnimation();

	}

	//if(mCurr == 해당모션 && mCurr->getisplay() == false)
	//{EndThrow();}

	mCurrentAnimation->Update();

	SearchPlayer();
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
}

void Witch::Render(HDC hdc)
{
	CAMERAMANAGER->GetMainCamera()->FrameRender(hdc, mImage, mRect.left, mRect.top, mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY());
}

void Witch::SearchPlayer()
{
	//플레이어가 searchzone 에 들어오면
	//방향설정

}



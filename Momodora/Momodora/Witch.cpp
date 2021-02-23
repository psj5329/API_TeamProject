#include "pch.h"
#include "Witch.h"
#include "Image.h"
#include "Animation.h"
#include "Camera.h"

void Witch::Init()
{
	IMAGEMANAGER->LoadFromFile(L"Witchcatch", Resources(L"Enemy/Witchcatch"), 490, 192, 5, 2, true);
	IMAGEMANAGER->LoadFromFile(L"Witchdeath", Resources(L"Enemy/Witchdeath"), 528, 128, 8, 2, true);
	IMAGEMANAGER->LoadFromFile(L"Witchdeath2", Resources(L"Enemy/Witchdeath2"), 528, 128, 8, 2, true);
	IMAGEMANAGER->LoadFromFile(L"Witchhurt", Resources(L"Enemy/Witchhurt"), 66, 128, 1, 2, true);
	IMAGEMANAGER->LoadFromFile(L"Witchhurt2", Resources(L"Enemy/Witchhurt2"), 66, 128, 1, 2, true);
	IMAGEMANAGER->LoadFromFile(L"Witchidle", Resources(L"Enemy/Witchidle"), 330, 128, 5, 2, true);
	IMAGEMANAGER->LoadFromFile(L"Witchidle2", Resources(L"Enemy/Witchidle2"), 330, 128, 5, 2, true);
	IMAGEMANAGER->LoadFromFile(L"Witchthrow", Resources(L"Enemy/Witchthrow"), 594, 128, 9, 2, true);

	mImage = IMAGEMANAGER->FindImage(L"Witchidle");

	mStart.x = WINSIZEX / 2;
	mStart.y = WINSIZEY / 2;
	mX = mStart.x;
	mY = mStart.y;
	mSizeX = mImage->GetFrameWidth() *2;
	mSizeY = mImage->GetFrameHeight() *2;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	mHitBox = RectMakeCenter(mX, mY, 50, 50);
	mAttackSpeed = 0;

	mRightIdle = new Animation();
	mRightIdle->InitFrameByStartEnd(0, 0, 4, 0, false);
	mRightIdle->SetIsLoop(true);
	mRightIdle->SetFrameUpdateTime(0.2f);

	mLeftIdle = new Animation();
	mLeftIdle->InitFrameByStartEnd(0, 1, 4, 1, false);
	mLeftIdle->SetIsLoop(true);
	mLeftIdle->SetFrameUpdateTime(0.2f);

	mRightAtk = new Animation();
	mRightAtk->InitFrameByStartEnd(0, 0, 8, 0, false);
	mRightAtk->SetIsLoop(false);
	mRightAtk->SetFrameUpdateTime(0.2f);
	//mRightAtk->SetCallbackFunc(*(function<void(void)>)EndThrow);

	mLeftAtk = new Animation();
	mLeftAtk->InitFrameByStartEnd(0, 1, 8, 1, false);
	mLeftAtk->SetIsLoop(false);
	mLeftAtk->SetFrameUpdateTime(0.2f);

	mRightHurt = new Animation();
	mRightHurt->InitFrameByStartEnd(0, 0, 0, 0, false);
	mRightHurt->SetIsLoop(false);
	mRightHurt->SetFrameUpdateTime(0.2f);

	mLeftHurt = new Animation();
	mLeftHurt->InitFrameByStartEnd(0, 1, 0, 1, false);
	mLeftHurt->SetIsLoop(false);
	mLeftHurt->SetFrameUpdateTime(0.2f);

	mRightCatch = new Animation();
	mRightCatch->InitFrameByStartEnd(0, 0, 4, 0, false);
	mRightCatch->SetIsLoop(false);
	mRightCatch->SetFrameUpdateTime(0.2f);

	mLeftCatch = new Animation();
	mLeftCatch->InitFrameByStartEnd(0, 1, 4, 1, false);
	mLeftCatch->SetIsLoop(false);
	mLeftCatch->SetFrameUpdateTime(0.2f);

	mRightDeath = new Animation();
	mRightDeath->InitFrameByStartEnd(0, 0, 6, 0, false);
	mRightDeath->SetIsLoop(false);
	mRightDeath->SetFrameUpdateTime(0.2f);
		 
	mLeftDeath = new Animation();
	mLeftDeath->InitFrameByStartEnd(0, 1, 6, 1, false);
	mLeftDeath->SetIsLoop(false);
	mLeftDeath->SetFrameUpdateTime(0.2f);



	mEnemyState = EnemyState::Idle;
	mDirection = Direction::Left;
	mCurrentAnimation = mLeftIdle;
	mCurrentAnimation->Play();
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
		mImage = IMAGEMANAGER->FindImage(L"Witchthrow");
		SetDirection();
		SetAnimation();
		mHoldStaff = false;
	}

	//지팡이 잡으면
	if (true)
	{
		//지팡이랙트 없애고
		//mHoldStaff 바꾸고
		//이미지바꾸고
	}

	mCurrentAnimation->Update();

	SearchPlayer();
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
}

void Witch::Render(HDC hdc)
{
	CAMERAMANAGER->GetMainCamera()->ScaleFrameRender(hdc, mImage, mRect.left, mRect.top, mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY(),mSizeX,mSizeY);
}

void Witch::SearchPlayer()
{
}

void Witch::EndAttack()
{
	mEnemyState = EnemyState::Idle;
	mImage = IMAGEMANAGER->FindImage(L"Witchidle2");
	SetAnimation();
}
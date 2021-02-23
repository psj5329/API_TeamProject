#include "pch.h"
#include "ShieldImp.h"
#include "Image.h"
#include "Animation.h"
#include "Camera.h"

void ShieldImp::Init()
{
	IMAGEMANAGER->LoadFromFile(L"ShieldImp", Resources(L"ShieldImp"), 256, 256, 8, 8, true);
	mImage = IMAGEMANAGER->FindImage(L"ShieldImp");

	mStart.x = WINSIZEX / 2;
	mStart.y = WINSIZEY / 2;
	mX = mStart.x;
	mY = mStart.y;
	mSizeX = mImage->GetFrameWidth()*2;
	mSizeY = mImage->GetFrameHeight()*2;
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
	mRightAtk->SetCallbackFunc(bind(&ShieldImp::EndAttack,this));

	mLeftAtk = new Animation();
	mLeftAtk->InitFrameByStartEnd(0, 5, 7, 5, false);
	mLeftAtk->SetIsLoop(true);
	mLeftAtk->SetFrameUpdateTime(0.2f);
	mLeftAtk->SetCallbackFunc(bind(&ShieldImp::EndAttack, this));

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

void ShieldImp::Release()
{
	SafeDelete(mRightIdle);
	SafeDelete(mLeftIdle);
	SafeDelete(mRightMove);
	SafeDelete(mLeftMove);
	SafeDelete(mRightAtk);
	SafeDelete(mLeftAtk);
	SafeDelete(mRightHurt);
	SafeDelete(mLeftHurt);
}

void ShieldImp::Update()
{
	mAttackSpeed += TIME->DeltaTime();
	mSearchSpeed += TIME->DeltaTime();

	//공격
	if (mAttackSpeed > 5)
	{
		mAttackSpeed = 0;
		mEnemyState = EnemyState::Attack;
		SetAnimation();
		ThrowDagger();
	}

	if (mEnemyState == EnemyState::Idle)
	{
		if (mSearchSpeed > 2)
		{
			mSearchSpeed = 0;
			SetDirection();
		}
	}

	//맞으면
	if (true)
	{

	}

	mCurrentAnimation->Update();
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
}

void ShieldImp::Render(HDC hdc)
{
	CAMERAMANAGER->GetMainCamera()->ScaleFrameRender(hdc, mImage, mRect.left, mRect.top, mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY(),mSizeX,mSizeY);
}

void ShieldImp::EndAttack()
{
	mEnemyState = EnemyState::Idle;
	SetAnimation();
}

void ShieldImp::ThrowDagger()
{

}
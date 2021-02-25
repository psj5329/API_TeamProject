#include "pch.h"
#include "Monkey.h"
#include "Image.h"
#include "Camera.h"
#include "Animation.h"
#include "Player.h"

void Monkey::Init()
{
	mImage = IMAGEMANAGER->FindImage(L"Monkey");
	mStart.x = WINSIZEX / 2;
	mStart.y = WINSIZEY / 2;
	mX = mStart.x;
	mY = mStart.y;
	mSizeX = mImage->GetFrameWidth()*2;
	mSizeY = mImage->GetFrameHeight()*2;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	mHitBox = RectMakeCenter(mX, mY, 50, 50);
	mSearchZone = RectMakeCenter(mX - 150, mY - 150, 300, 300);

	mSpeed = 70;
	mAttackSpeed = 100;
	mAtk = 10;
	mDef = 5;
	mHp = 100;
	mRange = 300;
	mAlpha = 1;

	mFoundPlayer = false;
	mDirection = Direction::Left;
	mEnemyState = EnemyState::Move;

	//애니메이션
	mRightIdle = new Animation();
	mRightIdle->InitFrameByStartEnd(0, 0, 0, 0, false);
	mRightIdle->SetIsLoop(false);
	mRightIdle->SetFrameUpdateTime(0.2f);

	mLeftIdle = new Animation();
	mLeftIdle->InitFrameByStartEnd(0, 1, 0, 1, false);
	mLeftIdle->SetIsLoop(false);
	mLeftIdle->SetFrameUpdateTime(0.2f);

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
	mRightAtk->SetCallbackFunc(bind(&Monkey::EndAttack, this));

	mLeftAtk = new Animation();
	mLeftAtk->InitFrameByStartEnd(0, 3, 8, 3, false);
	mLeftAtk->SetIsLoop(false);
	mLeftAtk->SetFrameUpdateTime(0.2f);
	mLeftAtk->SetCallbackFunc(bind(&Monkey::EndAttack, this));

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
	SafeDelete(mRightIdle);
	SafeDelete(mLeftIdle);
	SafeDelete(mRightMove);
	SafeDelete(mLeftMove);
	SafeDelete(mRightAtk);
	SafeDelete(mLeftAtk);
	SafeDelete(mRightHurt);
	SafeDelete(mLeftHurt);
}

void Monkey::Update()
{
	if (mFoundPlayer)
	{
		mAttackSpeed += TIME->DeltaTime();

		//거리가 멀면
		//플레이어로 이동
	

		if (mEnemyState== EnemyState::Move)
		{
			mSearchSpeed += TIME->DeltaTime();

			if (mPlayer->GetX() > mX)
			{
				mX += mSpeed * TIME->DeltaTime();
			}
			else
			{
				mX -= mSpeed * TIME->DeltaTime();
			}
			if (mEnemyState != EnemyState::Move)
			{
				mEnemyState = EnemyState::Move;

				SetAnimation();

			}
		}

		//거리가 가까우면
		//공격!
		if (Math::GetDistance(mPlayer->GetX(), 0, mX, 0) < 30 && mEnemyState != EnemyState::Death)
		{
			if (mAttackSpeed > 4)
			{
				mAttackSpeed = 0;
				Attack();
				mEnemyState = EnemyState::Attack;
				SetAnimation();
			}
		}

		if (Math::GetDistance(mPlayer->GetX(), 0, mX, 0) >= 30)
		{
			if (mEnemyState == EnemyState::Idle)
			{
				mEnemyState = EnemyState::Move;
				SetAnimation();
			}
		}

		if (mSearchSpeed > 2)
		{
			mSearchSpeed = 0;
			SetDirection();
			SetAnimation();
		}

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

	//죽으면
	DeathCheck();


	mCurrentAnimation->Update();
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	mHitBox = RectMakeCenter(mX, mY, 100, 100);


	if (mDirection == Direction::Left) {
		mSearchZone = RectMakeCenter(mX - 110, mY, 220, 200);
	}
	else {
		mSearchZone = RectMakeCenter(mX + 110, mY, 220, 200);
	}
}

void Monkey::Render(HDC hdc)
{
	CAMERAMANAGER->GetMainCamera()->AlphaScaleFrameRender(hdc, mImage, mRect.left, mRect.top, mCurrentAnimation->GetNowFrameX(),mCurrentAnimation->GetNowFrameY(),mSizeX,mSizeY,mAlpha);
	
	////색적
	//CAMERAMANAGER->GetMainCamera()->RenderRectInCamera(hdc, mSearchZone);
	//
	////몽둥이
	//CAMERAMANAGER->GetMainCamera()->RenderRectInCamera(hdc, mAtkBox);
	//
	////플레이어
	//CAMERAMANAGER->GetMainCamera()->RenderRectInCamera(hdc, mPlayer->GetRect());
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
	RECT temp;
	RECT player = mPlayer->GetRect();
	if (IntersectRect(&temp, &player, &mSearchZone))
	{
		mFoundPlayer = true;
	}
}

void Monkey::Attack()
{
	mAtkBox = RectMake(mRect.left, mRect.right, 50, 50);
}

void Monkey::EndAttack()
{
	if (Math::GetDistance(mPlayer->GetX(), 0, mX, 0) < 30)
	{
		mEnemyState = EnemyState::Idle;
	}
	else
	{
		mEnemyState = EnemyState::Move;
	}
	SetDirection();
	SetAnimation();
}
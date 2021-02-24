#include "pch.h"
#include "BombImp.h"
#include "Image.h"
#include "Animation.h"
#include "Camera.h"
#include "Bomb.h"
#include "Player.h"
void BombImp::Init()
{
	mImage = IMAGEMANAGER->FindImage(L"Imp");

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

	mRightAtk = new Animation();
	mRightAtk->InitFrameByStartEnd(0, 8, 8, 8, false);
	mRightAtk->SetIsLoop(false);
	mRightAtk->SetFrameUpdateTime(0.2f);
	mRightAtk->SetCallbackFunc(bind(&BombImp::EndThrow,this));

	mLeftAtk = new Animation();
	mLeftAtk->InitFrameByStartEnd(0, 9, 8, 9, false);
	mLeftAtk->SetIsLoop(false);
	mLeftAtk->SetFrameUpdateTime(0.2f);
	mLeftAtk->SetCallbackFunc(bind(&BombImp::EndThrow, this));

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
	SafeDelete(mRightIdle);
	SafeDelete(mLeftIdle);
	SafeDelete(mRightAtk);
	SafeDelete(mLeftAtk);
	SafeDelete(mRightHurt);
	SafeDelete(mLeftHurt);
}

void BombImp::Update()
{
	mAttackSpeed += TIME->DeltaTime();
	mSearchSpeed += TIME->DeltaTime();

	if (mAttackSpeed > 5)
	{
		mAttackSpeed = 0;
		mEnemyState = EnemyState::Attack;
		SetAnimation();
		mThrown = false;
	}
	if (mEnemyState == EnemyState::Idle)
	{
		if (mSearchSpeed > 2)
		{
			mSearchSpeed = 0;
			SetDirection();
		}
	}

	if (mCurrentAnimation == mRightAtk || mCurrentAnimation == mLeftAtk)
	{
		if (!mThrown)
		{
			if (mCurrentAnimation->GetNowFrameX() == 4)
			{
				ThrowBomb();
				mThrown = true;
			}

		}
	}


	mCurrentAnimation->Update();

	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
}

void BombImp::Render(HDC hdc)
{
	CAMERAMANAGER->GetMainCamera()->ScaleFrameRender(hdc, mImage, mRect.left, mRect.top, mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY(),mSizeX,mSizeY);
}

void BombImp::ThrowBomb()
{
	float angle;
	float distance = Math::GetDistance(mPlayer->GetX(), mPlayer->GetY(), mX, mY);
	//각설정
	//왼쪽
	if (mDirection == Direction::Left)
	{
		//거리 재서
		if (distance > 150)
		{
			angle = PI  * 3 / 4;
		}
		else
		{
			angle = PI * 7 / 8;
		}
	}
	else
	{
		//거리 재서
		if (distance > 150)
		{
			angle = PI / 4;
		}
		else
		{
			angle = PI * 3 / 8;
		}
	}

	//폭탄생성
	Bomb* Bomb1 = new Bomb();
	Bomb1->Init(mX, mY, angle, mPlayer->GetX(),mPlayer->GetY());
	Bomb1->SetObject();
	ObjectManager::GetInstance()->AddObject(ObjectLayer::EnemyProjectile, Bomb1);
}

void BombImp::EndThrow()
{
	mEnemyState = EnemyState::Idle;
	SetAnimation();
}
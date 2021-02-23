#include "pch.h"
#include "DaggerImp.h"
#include "Image.h"
#include "Animation.h"
#include "Camera.h"
#include "Enemy.h"
#include "Dagger.h"

void DaggerImp::Init()
{
	IMAGEMANAGER->LoadFromFile(L"Imp", Resources(L"Imp"), 320, 384, 10, 12, true);
	mImage = IMAGEMANAGER->FindImage(L"Imp");

	mStart.x = WINSIZEX / 2;
	mStart.y = WINSIZEY / 2;
	mX = mStart.x;
	mY = mStart.y;
	mSizeX = mImage->GetFrameWidth()*2;
	mSizeY = mImage->GetFrameHeight()*2;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	mHitBox = RectMakeCenter(mX, mY, 50, 50);
	isGround = true;
	mEnemyState = EnemyState::Jump;
	mDirection = Direction::Left;
	mSpeed = 25;
	mJumpPower = 20;
	mGravity = 2;
	mThrown = false;
	mSearchSpeed = 0;

	bottom = { 0, 602, 600, 650 };

	mRightIdle = new Animation();
	mRightIdle->InitFrameByStartEnd(0, 0, 0, 0, false);
	mRightIdle->SetIsLoop(false);
	mRightIdle->SetFrameUpdateTime(0.2f);

	mLeftIdle = new Animation();
	mLeftIdle->InitFrameByStartEnd(0, 1, 0, 1, false);
	mLeftIdle->SetIsLoop(false);
	mLeftIdle->SetFrameUpdateTime(0.2f);

	mRightJump = new Animation();
	mRightJump->InitFrameByStartEnd(0, 2, 0, 2, false);
	mRightJump->SetIsLoop(true);
	mRightJump->SetFrameUpdateTime(0.2f);

	mLeftJump = new Animation();
	mLeftJump->InitFrameByStartEnd(0, 3, 0, 3, false);
	mLeftJump->SetIsLoop(true);
	mLeftJump->SetFrameUpdateTime(0.2f);

	mRightFall = new Animation();
	mRightFall->InitFrameByStartEnd(0, 4, 5, 4, false);
	mRightFall->SetIsLoop(false);
	mRightFall->SetFrameUpdateTime(0.2f);

	mLeftFall = new Animation();
	mLeftFall->InitFrameByStartEnd(0, 5, 5, 5, false);
	mLeftFall->SetIsLoop(false);
	mLeftFall->SetFrameUpdateTime(0.2f);

	mRightAtk = new Animation();	
	mRightAtk->InitFrameByStartEnd(0, 6, 9, 6, false);
	mRightAtk->SetIsLoop(false);
	mRightAtk->SetFrameUpdateTime(0.1f);
	mRightAtk->SetCallbackFunc(bind(&DaggerImp::EndAttack, this));

	mLeftAtk = new Animation();
	mLeftAtk->InitFrameByStartEnd(0, 7, 9, 7, false);
	mLeftAtk->SetIsLoop(false);
	mLeftAtk->SetFrameUpdateTime(0.2f);
	mLeftAtk->SetCallbackFunc(bind(&DaggerImp::EndAttack, this));

	mRightHurt = new Animation();
	mRightHurt->InitFrameByStartEnd(0, 10, 0, 10, false);
	mRightHurt->SetIsLoop(false);
	mRightHurt->SetFrameUpdateTime(0.2f);

	mLeftHurt = new Animation();
	mLeftHurt->InitFrameByStartEnd(0, 11, 0, 11, false);
	mLeftHurt->SetIsLoop(false);
	mLeftHurt->SetFrameUpdateTime(0.2f);

	mCurrentAnimation = mLeftJump;
	mCurrentAnimation->Play();
}

void DaggerImp::Release()
{
	SafeDelete(mRightIdle);
	SafeDelete(mLeftIdle);
	SafeDelete(mRightJump);
	SafeDelete(mLeftJump);
	SafeDelete(mRightFall);
	SafeDelete(mLeftFall);
	SafeDelete(mRightAtk);
	SafeDelete(mLeftAtk);
	SafeDelete(mRightHurt);
	SafeDelete(mLeftHurt);

}

void DaggerImp::Update()
{
	mSearchSpeed++;

	//점프
	if (mEnemyState == EnemyState::Jump || mEnemyState==EnemyState::Fall)
	{
		JumpAround();
		mX += mSpeed * TIME->DeltaTime();

	}

	//땅에 닿으면
	if (mEnemyState == EnemyState::Idle)
	{
		//4분의1확률로 공격RANDOM->RandomInt(4) == 1
		if (RANDOM->RandomInt(3) == 1)
		{
			//공격
			mEnemyState = EnemyState::Attack;
			SetAnimation();
			mThrown = false;
		}
		else
		{
			mEnemyState = EnemyState::Jump;
			mJumpPower = 100;
			SetAnimation();
		}
		//좌우로 랜덤하게 이동
		if (RANDOM->RandomInt(4) == 1)
		{
			mSpeed *= -1;
		}
	}

	if (mCurrentAnimation == mRightAtk || mCurrentAnimation == mLeftAtk)
	{
		if (!mThrown)
		{
			if (mCurrentAnimation->GetNowFrameX() == 4)
			{
				ThrowDagger();
				mThrown = true;
			}

		}
	}

	//맞으면
	if (true)
	{

	}

	//플레이어 찾고 방향세팅
	if (mEnemyState == EnemyState::Idle || mEnemyState == EnemyState::Jump)
	{
		if (mSearchSpeed > 2)
		{
			mSearchSpeed = 0;
			SetDirection();
		}
	}

	mCurrentAnimation->Update();

	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
}

void DaggerImp::Render(HDC hdc)
{
	CAMERAMANAGER->GetMainCamera()->ScaleFrameRender(hdc, mImage, mRect.left, mRect.top, mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY(),mSizeX,mSizeY);
	//CAMERAMANAGER->GetMainCamera()->RenderRectInCamera(hdc, mRect);
}

void DaggerImp::JumpAround()
{
	mY -= mJumpPower * TIME->DeltaTime();
	mJumpPower -= mGravity;
	
	if (mJumpPower ==0)
	{
		mEnemyState = EnemyState::Fall;
		SetAnimation();
	}

	//좌표로 떄려박았음 여기 충돌체크해야햄
	if (mY > 600 - mSizeY /2)
	{
		mY = 600 - mSizeY /2;
		mEnemyState = EnemyState::Idle;
		SetAnimation();
		mJumpPower = 0;
	}
	
	//RECT temp;
	//if (IntersectRect(&temp, &mRect, &bottom)) {
	//	mRect.bottom = bottom.top;
	//
	//	mRect.top = mRect.bottom - mSizeY;
	//	mY = mRect.top + mSizeY/2;
	//	mEnemyState = EnemyState::Idle;
	//}
}

void DaggerImp::ThrowDagger()
{
	float angle;
	if (mDirection == Direction::Left)
	{
		angle = PI;
	}
	else
	{
		angle = 0;
	}
	Dagger* Dagger1 = new Dagger();
	Dagger1->Init(mX, mY, angle);
	Dagger1->SetObject();
	ObjectManager::GetInstance()->AddObject(ObjectLayer::EnemyProjectile, Dagger1);
}

void DaggerImp::EndAttack()
{
	mEnemyState = EnemyState::Idle;
	SetAnimation();
}
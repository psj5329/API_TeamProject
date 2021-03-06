#include "pch.h"
#include "DaggerImp.h"
#include "Image.h"
#include "Animation.h"
#include "Camera.h"
#include "Enemy.h"
#include "Dagger.h"

void DaggerImp::Init()
{
	mImage = IMAGEMANAGER->FindImage(L"Imp");

	mStart.x = -2000;
	mStart.y = 2000;
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
	mHp = 60;
	bottom = { 0, 602, 600, 650 };
	mAlpha = 1;
	isHit = false;
	mHurtCounter = 0;
	mName = "DaggerImp";

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
	mLeftAtk->SetFrameUpdateTime(0.1f);
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

	//����
	if (mEnemyState == EnemyState::Jump || mEnemyState==EnemyState::Fall)
	{
		JumpAround();
		mX += mSpeed * TIME->DeltaTime();

	}

	//���� ������
	if (mEnemyState == EnemyState::Idle)
	{
		//4����1Ȯ���� ����RANDOM->RandomInt(4) == 1
		if (RANDOM->RandomInt(3) == 1)
		{
			//����
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
		//�¿�� �����ϰ� �̵�
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
	//������
	if (mEnemyState == EnemyState::Hurt)
	{
		HurtRectMove();
	}


	//������
	DeathCheck();


	//�÷��̾� ã�� ���⼼��
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
	mHitBox = RectMakeCenter(mX, mY+4, mSizeX-20, mSizeY-20);
	mPrevRect = mRect;
}

void DaggerImp::Render(HDC hdc)
{
	//CAMERAMANAGER->GetMainCamera()->RenderRectInCamera(hdc, mHitBox);
	CAMERAMANAGER->GetMainCamera()->AlphaScaleFrameRender(hdc, mImage, mRect.left, mRect.top, mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY(),mSizeX,mSizeY,mAlpha);
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
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);

	//��ǥ�� �����ھ��� ���� �浹üũ�ؾ���
	//if (mY > 600 - mSizeY /2)
	//{
	//	mEnemyState = EnemyState::Idle;
	//	mY = 600 - mSizeY /2;
	//	SetAnimation();
	//	mJumpPower = 0;
	//}
	


	if (COLLISIONMANAGER->IsCollideWithPlatform(&mRect))
	{
		mEnemyState = EnemyState::Idle;
		SetAnimation();
		mJumpPower = 0;
	}
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
	ObjectManager::GetInstance()->AddObject(ObjectLayer::EnemyDagger, Dagger1);

	//�Ҹ�
	SOUNDMANAGER->Play(L"Imp2", 0.02f);
}

void DaggerImp::EndAttack()
{
	mEnemyState = EnemyState::Idle;
	SetAnimation();
}


void DaggerImp::HurtRectMove()
{
	float angle;
	
	//�¾����� ��������
	if (mHurtCounter == 0)
	{
		mHurtY = mY;
	}

	mHurtCounter += TIME->DeltaTime();

	//��������
	if (mHurtCounter < 0.05)
	{
		if (mDirection == Direction::Left)
		{
			angle = PI * 25 / 16;

			mX += cos(angle) * 500 * TIME->DeltaTime();
			mY -= sin(angle) * 250 * TIME->DeltaTime();
		}
		if (mDirection == Direction::Right)
		{
			angle = PI * 23 / 16;

			mX += cos(angle) * 500 * TIME->DeltaTime();
			mY -= sin(angle) * 250 * TIME->DeltaTime();
		}
	}
	//�ö����
	else
	{
		if (mDirection == Direction::Left)
		{
			angle = PI * 1 / 4;

			mX += cos(angle) * 300 * TIME->DeltaTime();
			mY -= sin(angle) * 100 * TIME->DeltaTime();
		}
		if (mDirection == Direction::Right)
		{
			angle = PI * 3 / 4;

			mX += cos(angle) * 300 * TIME->DeltaTime();
			mY -= sin(angle) * 100 * TIME->DeltaTime();
		}
		if (mY <= mHurtY)
		{
			mY = mHurtY;
			mEnemyState = EnemyState::Idle;
			SetAnimation();
			mHurtCounter = 0;

		}
	}
}
#include "pch.h"
#include "Witch.h"
#include "Image.h"
#include "Animation.h"
#include "Camera.h"
#include "Player.h"
#include "Staff.h"

void Witch::Init()
{
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
	mHoldStaff = true;
	mHp = 0;

	//������
	mStaff = new Staff();
	mStaff->Init();
	ObjectManager::GetInstance()->AddObject(ObjectLayer::EnemyProjectile, mStaff);
	mStaff->SetObject();
	mStaff->SetIsActive(false);



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
	mRightAtk->SetCallbackFunc(bind(&Witch::EndAttack,this));

	mLeftAtk = new Animation();
	mLeftAtk->InitFrameByStartEnd(0, 1, 8, 1, false);
	mLeftAtk->SetIsLoop(false);
	mLeftAtk->SetFrameUpdateTime(0.2f);
	mLeftAtk->SetCallbackFunc(bind(&Witch::EndAttack, this));

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
	mRightCatch->SetCallbackFunc(bind(&Witch::EndCatch, this));

	mLeftCatch = new Animation();
	mLeftCatch->InitFrameByStartEnd(0, 1, 4, 1, false);
	mLeftCatch->SetIsLoop(false);
	mLeftCatch->SetFrameUpdateTime(0.2f);
	mLeftCatch->SetCallbackFunc(bind(&Witch::EndCatch, this));

	mRightDeath = new Animation();
	mRightDeath->InitFrameByStartEnd(0, 0, 6, 0, false);
	mRightDeath->SetIsLoop(false);
	mRightDeath->SetFrameUpdateTime(0.2f);
	mRightDeath->SetCallbackFunc(bind(&Witch::EndDeath, this));

	mLeftDeath = new Animation();
	mLeftDeath->InitFrameByStartEnd(0, 1, 6, 1, false);
	mLeftDeath->SetIsLoop(false);
	mLeftDeath->SetFrameUpdateTime(0.2f);
	mLeftDeath->SetCallbackFunc(bind(&Witch::EndDeath, this));

	mEnemyState = EnemyState::Idle;
	mDirection = Direction::Left;
	mCurrentAnimation = mLeftIdle;
	mCurrentAnimation->Play();
}

void Witch::Release()
{
	SafeDelete(mRightIdle);
	SafeDelete(mLeftIdle);
	SafeDelete(mRightAtk);
	SafeDelete(mLeftAtk);
	SafeDelete(mRightHurt);
	SafeDelete(mLeftHurt);
	SafeDelete(mRightCatch);
	SafeDelete(mLeftCatch);
	SafeDelete(mRightDeath);
	SafeDelete(mLeftDeath);

}

void Witch::Update()
{

	//������
	if (mEnemyState == EnemyState::Idle && mHoldStaff)
	{
		mAttackSpeed += TIME->DeltaTime();
		if (mAttackSpeed > 2)
		{
			mAttackSpeed = 0;
			mEnemyState = EnemyState::Attack;
			mImage = IMAGEMANAGER->FindImage(L"Witchthrow");
			SetDirection();
			SetAnimation();
			mThrown = false;
		}
	}

	//�����̰� ���ƿ��� ���̰�
	if (mStaff->GetIsReturn())
	{
		//������ �ȵ���ְ�
		if (!mHoldStaff)
		{
			//�����̿� �Ÿ��� ���������
			if (Math::GetDistance(mX, mY, mStaff->GetX(), mStaff->GetY()) < 4)
			{
				//�����̷�Ʈ ���ְ�
				RECT temp = RectMakeCenter(2000, 2000, 1, 1);
				mStaff->SetRect(temp);
				mStaff->SetIsActive(false);

				//mHoldStaff �ٲٰ�
				mHoldStaff = true;

				//�̹����ٲٰ�
				//SetDirection();
				mImage = IMAGEMANAGER->FindImage(L"Witchcatch");

				//ũ������
				mSizeX = mImage->GetFrameWidth() * 2;
				mSizeY = mImage->GetFrameHeight() * 2;

				//���ϸ��̼� �����ϰ�
				if (mDirection == Direction::Left)
				{
					mCurrentAnimation->Stop();
					mCurrentAnimation = mLeftCatch;
					mCurrentAnimation->Play();

				}
				else
				{
					mCurrentAnimation->Stop();
					mCurrentAnimation = mRightCatch;
					mCurrentAnimation->Play();

				}
			}

		}
	}


	//����ü �����ϴ±���
	if (mCurrentAnimation == mRightAtk || mCurrentAnimation == mLeftAtk)
	{
		if (!mThrown)
		{
			if (mCurrentAnimation->GetNowFrameX() == 4)
			{
				Attack();
				mThrown = true;
				mHoldStaff = false;
			}

		}
	}


	//������


	//������
	if (mHp <= 0 && mEnemyState != EnemyState::Death)
	{
		mEnemyState = EnemyState::Death;
		if (mHoldStaff)
			mImage = IMAGEMANAGER->FindImage(L"Witchdeath");
		else
			mImage = IMAGEMANAGER->FindImage(L"Witchdeath2");

		mCurrentAnimation->Stop();
		if (mDirection == Direction::Left)
			mCurrentAnimation = mLeftDeath;
		else
			mCurrentAnimation = mRightDeath;
		mCurrentAnimation->Play();
	}




	mCurrentAnimation->Update();
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	mHitBox = RectMakeCenter(mX, mY, 50, 80);
}

void Witch::Render(HDC hdc)
{
	//CAMERAMANAGER->GetMainCamera()->RenderRectInCamera(hdc, mHitBox);
	CAMERAMANAGER->GetMainCamera()->ScaleFrameRender(hdc, mImage, mRect.left, mRect.top, mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY(),mSizeX,mSizeY);
	
}

void Witch::SearchPlayer()
{
}

//������ ���¹ٲٱ�
void Witch::EndAttack()
{
	mEnemyState = EnemyState::Idle;
	mImage = IMAGEMANAGER->FindImage(L"Witchidle2");
	SetAnimation();
}

//������������ ���¹ٲٱ�
void Witch::EndCatch()
{
	mEnemyState = EnemyState::Idle;
	mImage = IMAGEMANAGER->FindImage(L"Witchidle");
	mSizeX = mImage->GetFrameWidth() * 2;
	mSizeY = mImage->GetFrameHeight() * 2;
	SetAnimation();
}

//�����̴�����
void Witch::Attack()
{
	float angle = Math::GetAngle(mX, mY, mPlayer->GetX(), mPlayer->GetY());
	mStaff->Init(mX, mY, angle);
	
	mStaff->SetIsActive(true);
}

void Witch::EndDeath()
{
	this->SetIsDestroy(true);
}
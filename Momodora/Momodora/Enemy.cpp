#include "pch.h"
#include "Enemy.h"
#include "Animation.h"
#include "Player.h"
#include "StarItem.h"

Enemy::Enemy()
	: GameObject()
{
}

Enemy::Enemy(float x, float y)
	: GameObject(x, y)
{
}

void Enemy::Init()
{

}

void Enemy::Release()
{

}

void Enemy::Update()
{

}

void Enemy::Render(HDC hdc)
{

}

void Enemy::SetPosition(float startX, float startY)
{
	mStart.x = startX;
	mStart.y = startY - ((mHitBox.bottom - mHitBox.top)) ;
	mX = mStart.x;
	mY = mStart.y;
}

void Enemy::SetAnimation()
{
	if (mDirection == Direction::Left)
	{
		if (mEnemyState == EnemyState::Move)
		{
			mCurrentAnimation->Stop();
			mCurrentAnimation = mLeftMove;
			mCurrentAnimation->Play();
		}
		if (mEnemyState == EnemyState::Jump)
		{
			mCurrentAnimation->Stop();
			mCurrentAnimation = mLeftJump;
			mCurrentAnimation->Play();
		}
		if (mEnemyState == EnemyState::Fall)
		{
			mCurrentAnimation->Stop();
			mCurrentAnimation = mLeftFall;
			mCurrentAnimation->Play();
		}
		if (mEnemyState == EnemyState::Idle)
		{
			mCurrentAnimation->Stop();
			mCurrentAnimation = mLeftIdle;
			mCurrentAnimation->Play();
		}
		if (mEnemyState == EnemyState::Attack)
		{
			mCurrentAnimation->Stop();
			mCurrentAnimation = mLeftAtk;
			mCurrentAnimation->Play();
		}
		if (mEnemyState == EnemyState::Hurt || mEnemyState == EnemyState::Death)
		{
			mCurrentAnimation->Stop();
			mCurrentAnimation = mLeftHurt;
			mCurrentAnimation->Play();
		}
	}
	if (mDirection == Direction::Right)
	{
		if (mEnemyState == EnemyState::Move)
		{
			mCurrentAnimation->Stop();
			mCurrentAnimation = mRightMove;
			mCurrentAnimation->Play();
		}

		if (mEnemyState == EnemyState::Jump)
		{
			mCurrentAnimation->Stop();
			mCurrentAnimation = mRightJump;
			mCurrentAnimation->Play();
		}
		if (mEnemyState == EnemyState::Fall)
		{
			mCurrentAnimation->Stop();
			mCurrentAnimation = mRightFall;
			mCurrentAnimation->Play();
		}
		if (mEnemyState == EnemyState::Idle)
		{
			mCurrentAnimation->Stop();
			mCurrentAnimation = mRightIdle;
			mCurrentAnimation->Play();
		}
		if (mEnemyState == EnemyState::Attack)
		{
			mCurrentAnimation->Stop();
			mCurrentAnimation = mRightAtk;
			mCurrentAnimation->Play();
		}
		if (mEnemyState == EnemyState::Hurt || mEnemyState == EnemyState::Death)
		{
			mCurrentAnimation->Stop();
			mCurrentAnimation = mRightHurt;
			mCurrentAnimation->Play();
		}
	}
}


void Enemy::EndAttack()
{

}


void Enemy::SetDirection()
{
	if (mPlayer->GetX() > mX)
	{
		mDirection = Direction::Right;
		SetAnimation();
	}
	else if (mPlayer->GetX() < mX)
	{
		mDirection = Direction::Left;
		SetAnimation();
	}

}

void Enemy::Attack()
{

}

void Enemy::DeathCheck()
{
	//체력 0 이하면
	if (mHp <= 0 && mEnemyState != EnemyState::Death)
	{
		//상태바꾸고
		mEnemyState = EnemyState::Death;
		SetAnimation();
		//돈떨궈
		DropGold();

		//소리
		if (mName == "DaggerImp" || mName == "BombImp" ||mName == "ShieldImp")
		{
			//소리
			SOUNDMANAGER->Play(L"ImpDeath", 0.05f);
		}
	}
	if (mEnemyState == EnemyState::Death)
	{
		//알파값낮추다가
		mAlpha -= TIME->DeltaTime() * 2;
		if (mAlpha < 0)
		{
			//없애
			this->SetIsDestroy(true);
		}
	}
}

void Enemy::DropGold()
{
	int numb = RANDOM->RandomInt(4, 10);
	for (int i = 0; i < numb;i++)
	{
		StarItem* star = new StarItem;
		star->Init();
		star->SetX(mX);
		star->SetY(mY);
		star->SetAngle((rand() % 180) * PI / 180.f);
		OBJECTMANAGER->AddObject(ObjectLayer::Item, star);
	}
}
void Enemy::DropGold(int goldNum)
{
	for (int i = 0; i < goldNum;i++)
	{
		StarItem* star = new StarItem;
		star->Init();
		star->SetX(mX);
		star->SetY(mY);
		star->SetAngle((rand() % 180) * PI / 180.f);
		OBJECTMANAGER->AddObject(ObjectLayer::Item, star);
	}
}

void Enemy::Hurt(Direction direction)
{
	mDirection = direction;
	mEnemyState = EnemyState::Hurt;
	SetAnimation();

}

void Enemy::HurtRectMove()
{
	float angle;
	mHurtCounter += TIME->DeltaTime();

	//내려가고
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
	//올라오고
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
		if (mY <= mStart.y)
		{
			mY = mStart.y;
			mEnemyState = EnemyState::Idle;
			SetAnimation();
			mHurtCounter = 0;

		}
	}
}
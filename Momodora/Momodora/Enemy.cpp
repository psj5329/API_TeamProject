#include "pch.h"
#include "Enemy.h"
#include "Animation.h"
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

void Enemy::SetPosition(int startX, int startY)
{
	mStart.x = startX;
	mStart.y = startY;
	mX = mStart.x;
	mY = mStart.y;
}

void Enemy::SetAnimation()
{
	if (mDirection == Direction::Left)
	{
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
		if (mEnemyState == EnemyState::Hurt)
		{
			mCurrentAnimation->Stop();
			mCurrentAnimation = mLeftHurt;
			mCurrentAnimation->Play();
		}
	}
	if (mDirection == Direction::Right)
	{
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
		if (mEnemyState == EnemyState::Hurt)
		{
			mCurrentAnimation->Stop();
			mCurrentAnimation = mRightHurt;
			mCurrentAnimation->Play();
		}
	}
}
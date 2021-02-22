#include "pch.h"
#include "Enemy.h"

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
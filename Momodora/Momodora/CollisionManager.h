#pragma once
#include "ObjectManager.h"
#include "GameObject.h"

class CollisionManager
{
	_Singleton(CollisionManager)

public:
	void Update();

public:
	bool IsCollision(RECT* rect1, RECT* rect2);
	bool IsCollision(RECT* rect1, RECT* rect2, int& direction); // 1: 상하충돌, 2: 좌우충돌
 	bool IsCollision(RECT* rect, ObjectLayer layer);
	bool IsCollision(RECT* rect, ObjectLayer layer, int& direction); // 1: 상하충돌, 2: 좌우충돌
	bool IsCollideWithPlatform(RECT* rect, bool normal = true);
	bool IsCollideWithPlatform(RECT* rect, int& direction); // 1: 상하충돌, 2: 좌우충돌
	bool IsInRangeDownjumpPlatform(RECT* rect); // 점프 플랫폼 범위 안에 들어오는지
	RECT* CollideWithPlatform(RECT* rect, RECT* prevRect, float sizeX, float sizeY);
	RECT* CollideWithDownjumpPlatform(RECT* rect, RECT* prevRect, float sizeX, float sizeY);
	Direction CheckSide(RECT* player, RECT* projectile);		//플레이어와 무언가 충돌시 1오른쪽 2왼쪽 리턴 0안부딛힘
};

#define COLLISIONMANAGER CollisionManager::GetInstance()
#pragma once
#include "ObjectManager.h"

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
	RECT* CollideWithPlatform(RECT* rect, RECT* prevRect, float sizeX, float sizeY);
	RECT* CollideWithDownjumpPlatform(RECT* rect, RECT* prevRect, float sizeX, float sizeY); // 하강 중일 때만 들어와야 함
};

#define COLLISIONMANAGER CollisionManager::GetInstance()
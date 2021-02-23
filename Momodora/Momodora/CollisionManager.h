#pragma once
#include "ObjectManager.h"

class CollisionManager
{
	_Singleton(CollisionManager)

public:
	void Update();

public:
	bool IsCollision(RECT* rect1, RECT* rect2);
 	bool IsCollision(RECT* rect, ObjectLayer layer);
	bool IsCollideWithPlatform(RECT* rect);
	RECT* CollideWithPlatform(RECT* rect, RECT* prevRect, float sizeX, float sizeY);
};

#define COLLISIONMANAGER CollisionManager::GetInstance()
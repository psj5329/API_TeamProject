#pragma once

class CollisionManager
{
	_Singleton(CollisionManager)

public:
	void Update();

public:
	bool IsCollideWithPlatform(RECT* rect);
	RECT* CollideWithPlatform(RECT* rect, RECT* prevRect, float sizeX, float sizeY);
};

#define COLLISIONMANAGER CollisionManager::GetInstance()
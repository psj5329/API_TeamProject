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
	bool IsCollision(RECT* rect1, RECT* rect2, int& direction); // 1: �����浹, 2: �¿��浹
 	bool IsCollision(RECT* rect, ObjectLayer layer);
	bool IsCollision(RECT* rect, ObjectLayer layer, int& direction); // 1: �����浹, 2: �¿��浹
	bool IsCollideWithPlatform(RECT* rect, bool normal = true);
	bool IsCollideWithPlatform(RECT* rect, int& direction); // 1: �����浹, 2: �¿��浹
	bool IsInRangeDownjumpPlatform(RECT* rect); // ���� �÷��� ���� �ȿ� ��������
	RECT* CollideWithPlatform(RECT* rect, RECT* prevRect, float sizeX, float sizeY);
	RECT* CollideWithDownjumpPlatform(RECT* rect, RECT* prevRect, float sizeX, float sizeY);
	Direction CheckSide(RECT* player, RECT* projectile);		//�÷��̾�� ���� �浹�� 1������ 2���� ���� 0�Ⱥε���
};

#define COLLISIONMANAGER CollisionManager::GetInstance()
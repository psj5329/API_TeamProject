#include "pch.h"
#include "CollisionManager.h"
#include "GameObject.h"
#include "ObjectManager.h"
#include "Platform.h"
_Singleton_NULL(CollisionManager)

void CollisionManager::Update()
{
}

bool CollisionManager::IsCollision(RECT* rect1, RECT* rect2)
{
	RECT tempRect;

	if (IntersectRect(&tempRect, rect1, rect2))
		return true;

	return false;
}

bool CollisionManager::IsCollision(RECT* rect1, RECT* rect2, int& direction)
{
	RECT tempRect;
	int width = 0;
	int height = 0;

	if (IntersectRect(&tempRect, rect1, rect2))
	{
		width = tempRect.right - tempRect.left;
		height = tempRect.bottom - tempRect.top;

		if (width > height)
			direction = 1; // 1: 상하충돌
		else
			direction = 2; // 2: 좌우충돌

		return true;
	}

	return false;
}

bool CollisionManager::IsCollision(RECT* rect, ObjectLayer layer)
{
	vector<GameObject*> layerList = OBJECTMANAGER->GetObjectList(layer);
	RECT tempRect;
	RECT layerRect;

	vector<GameObject*>::iterator iter = layerList.begin();
	for (; iter != layerList.end(); ++iter)
	{
		layerRect = (*iter)->GetRect();

		if (IntersectRect(&tempRect, rect, &layerRect))
			return true;
	}

	return false;
}

bool CollisionManager::IsCollision(RECT* rect, ObjectLayer layer, int& direction)
{
	vector<GameObject*> layerList = OBJECTMANAGER->GetObjectList(layer);
	RECT tempRect;
	RECT layerRect;
	int width = 0;
	int height = 0;

	vector<GameObject*>::iterator iter = layerList.begin();
	for (; iter != layerList.end(); ++iter)
	{
		layerRect = (*iter)->GetRect();

		if (IntersectRect(&tempRect, rect, &layerRect))
		{
			width = tempRect.right - tempRect.left;
			height = tempRect.bottom - tempRect.top;

			if (width > height)
				direction = 1; // 1: 상하충돌
			else
				direction = 2; // 2: 좌우충돌

			return true;
		}
	}

	return false;
}

bool CollisionManager::IsCollideWithPlatform(RECT* rect, bool normal)
{
	vector<GameObject*> platformList = OBJECTMANAGER->GetObjectList(ObjectLayer::Platform);
	RECT tempRect;
	RECT platformRect;

	vector<GameObject*>::iterator iter = platformList.begin();
	for (; iter != platformList.end(); ++iter)
	{
		platformRect = (*iter)->GetRect();

		if (IntersectRect(&tempRect, rect, &platformRect))
			return true;
		else if (platformRect.top == rect->bottom && platformRect.left < rect->right && platformRect.right > rect->left)
			return true;
	}

	return false;
}

bool CollisionManager::IsCollideWithPlatform(RECT* rect, int& direction)
{
	vector<GameObject*> platformList = OBJECTMANAGER->GetObjectList(ObjectLayer::Platform);
	RECT tempRect;
	RECT platformRect;
	int width = 0;
	int height = 0;

	vector<GameObject*>::iterator iter = platformList.begin();
	for (; iter != platformList.end(); ++iter)
	{
		platformRect = (*iter)->GetRect();

		if (IntersectRect(&tempRect, rect, &platformRect))
		{
			width = tempRect.right - tempRect.left;
			height = tempRect.bottom - tempRect.top;

			if (width > height)
				direction = 1; // 1: 상하충돌
			else
				direction = 2; // 2: 좌우충돌

			return true;
		}
	}

	return false;
}

bool CollisionManager::IsInRangeDownjumpPlatform(RECT* rect)
{
	vector<GameObject*> platformList = OBJECTMANAGER->GetObjectList(ObjectLayer::Platform);
	RECT tempRect;
	RECT platformRect;
	int width = 0;
	int height = 0;

	vector<GameObject*>::iterator iter = platformList.begin();
	for (; iter != platformList.end(); ++iter)
	{
		if (((Platform*)(*iter))->GetPlatformType() == PlatformType::Normal)
			continue;

		platformRect = (*iter)->GetRect();

		if (IntersectRect(&tempRect, rect, &platformRect))
		{
			width = tempRect.right - tempRect.left;
			height = tempRect.bottom - tempRect.top;

			if (width > height)
				if ((*iter)->GetRect().top <= rect->bottom && rect->top <= (*iter)->GetRect().bottom)
					return true;
		}
	}

	return false;
}

RECT* CollisionManager::CollideWithPlatform(RECT* rect, RECT* prevRect, float sizeX, float sizeY)
{
	vector<GameObject*> platformList = OBJECTMANAGER->GetObjectList(ObjectLayer::Platform);
	RECT tempRect;
	RECT platformRect;
	float centerX;
	float centerY;

	vector<GameObject*>::iterator iter = platformList.begin();
	for (; iter != platformList.end(); ++iter)
	{
		if (((Platform*)(*iter))->GetPlatformType() == PlatformType::DownJump)
			continue;

		platformRect = (*iter)->GetRect();

		if (IntersectRect(&tempRect, rect, &platformRect))
		{
			centerX = ((*rect).left + (*rect).right) / 2.f;
			centerY = ((*rect).top + (*rect).bottom) / 2.f;

			if (platformRect.top >= (*prevRect).bottom)
			{
				centerY = platformRect.top - sizeY / 2.f;
				(*rect) = RectMakeCenter((int)centerX, (int)centerY, (int)sizeX, (int)sizeY);
			}
			else if (platformRect.left >= (*prevRect).right)
			{
				centerX = platformRect.left - sizeX / 2.f - 1.f;
				(*rect) = RectMakeCenter((int)centerX, (int)centerY, (int)sizeX, (int)sizeY);
			}
			else if (platformRect.right <= (*prevRect).left)
			{
				centerX = platformRect.right + sizeX / 2.f + 1.f;
				(*rect) = RectMakeCenter((int)centerX, (int)centerY, (int)sizeX, (int)sizeY);
			}
			else if (platformRect.bottom <= (*prevRect).top)
			{
				centerY = platformRect.bottom + sizeY / 2.f + 1.f;
				(*rect) = RectMakeCenter((int)centerX, (int)centerY, (int)sizeX, (int)sizeY);
			}
		}
	}

	return rect;
}

RECT* CollisionManager::CollideWithDownjumpPlatform(RECT* rect, RECT* prevRect, float sizeX, float sizeY)
{
	if (rect->bottom <= prevRect->bottom) // 하강 중이 아니므로 돌려보내기
		return rect;

	vector<GameObject*> platformList = OBJECTMANAGER->GetObjectList(ObjectLayer::Platform);
	RECT tempRect;
	RECT platformRect;
	float centerX;
	float centerY;

	vector<GameObject*>::iterator iter = platformList.begin();
	for (; iter != platformList.end(); ++iter)
	{
		if (((Platform*)(*iter))->GetPlatformType() == PlatformType::Normal)
			continue;

		platformRect = (*iter)->GetRect();

		if (IntersectRect(&tempRect, rect, &platformRect))
		{
			centerX = ((*rect).left + (*rect).right) / 2.f;
			centerY = ((*rect).top + (*rect).bottom) / 2.f;

			if (platformRect.top >= (*prevRect).bottom)
			{
				centerY = platformRect.top - sizeY / 2.f;
				(*rect) = RectMakeCenter((int)centerX, (int)centerY, (int)sizeX, (int)sizeY);
			}
			else if (platformRect.left >= (*prevRect).right)
			{
				centerX = platformRect.left - sizeX / 2.f - 1.f;
				(*rect) = RectMakeCenter((int)centerX, (int)centerY, (int)sizeX, (int)sizeY);
			}
			else if (platformRect.right <= (*prevRect).left)
			{
				centerX = platformRect.right + sizeX / 2.f + 1.f;
				(*rect) = RectMakeCenter((int)centerX, (int)centerY, (int)sizeX, (int)sizeY);
			}
		}
	}

	return rect;
}

Direction CollisionManager::CheckSide(RECT* player, RECT* projectile)
{
	RECT tempRect;
	RECT layerRect;
	int tempX = 0;
	//플레이어 중심점
	int playerX = (player->left + player->right) / 2;
	Direction direction = Direction::Left;

	if (IntersectRect(&tempRect, player, projectile))
	{
		//충돌부분 중심점
		tempX = (tempRect.right + tempRect.left) / 2;

		if (playerX < tempX)
			direction = Direction::Right; // 우
		else
			direction = Direction::Left; // 좌
	}

	return direction;
}
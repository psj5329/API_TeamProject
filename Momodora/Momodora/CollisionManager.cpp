#include "pch.h"
#include "CollisionManager.h"
#include "GameObject.h"
#include "ObjectManager.h"
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

bool CollisionManager::IsCollideWithPlatform(RECT* rect)
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
				centerX = platformRect.top - sizeX / 2.f;
				(*rect) = RectMakeCenter((int)centerX, (int)centerY, (int)sizeX, (int)sizeY);
			}
			else if (platformRect.right <= (*prevRect).left)
			{
				centerX = platformRect.top + sizeX / 2.f;
				(*rect) = RectMakeCenter((int)centerX, (int)centerY, (int)sizeX, (int)sizeY);
			}
			else if (platformRect.bottom <= (*prevRect).top)
			{
				centerY = platformRect.bottom + sizeY / 2.f;
				(*rect) = RectMakeCenter((int)centerX, (int)centerY, (int)sizeX, (int)sizeY);
			}
		}
	}

	return rect;
}
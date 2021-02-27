#pragma once
#include "Image.h"

class Scene
{
protected:
	int mSceneSizeX;
	int mSceneSizeY;
	Image* mMapImage;

public:
	virtual void Init() = 0;
	virtual void Release() = 0;
	virtual void Update() = 0;
	virtual void Render(HDC hdc) = 0;

public:
	inline int GetSceneSizeX()const { return mSceneSizeX; }
	inline void SetSceneSizeX(int x) { mSceneSizeX = x; }
	inline int GetSceneSizeY()const { return mSceneSizeY; }
	inline void SetSceneSizeY(int y) { mSceneSizeY = y; }
	inline void SetSceneSize(int x, int y) { mSceneSizeX = x; mSceneSizeY = y; }
};
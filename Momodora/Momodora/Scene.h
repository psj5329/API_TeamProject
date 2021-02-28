#pragma once
#include "Image.h"

class Scene
{
protected:
	int mSceneSizeX;
	int mSceneSizeY;
	Image* mMapImage;
	int mEntrance; // 0 미등록 1 왼쪽 2 오른쪽

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
	inline bool GetEntrance()const { return mEntrance; }
	inline void SetEntrance(int entrance) { mEntrance = entrance; }
};
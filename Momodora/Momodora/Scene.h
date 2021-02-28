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

	//적생성
	void AddMonkey(float x, float y); //y에 플랫폼의 랙트의 탑
	void AddWitch(float x, float y); //y에 플랫폼의 랙트의 탑
	void AddBombImp(float x, float y); //y에 플랫폼의 랙트의 탑
	void AddShieldImp(float x, float y); //y에 플랫폼의 랙트의 탑
	void AddDaggerImp(float x, float y); //y에 플랫폼의 랙트의 탑
	void AddFennel(float x, float y);

	//물약생성
	void AddPotion(float x, float y);

	//충돌처리
	void AllCollision();
};
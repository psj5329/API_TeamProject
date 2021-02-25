#pragma once
#include "GameObject.h"
class Animation;
class Image;
class Staff :
	public GameObject
{

	Image* mImage;
	Animation* mLeftMove;
	Animation* mRightMove;
	Animation* mCurrentAnimation;

	float mAtk;
	float mAngle;
	float mSpeed;
	RECT mPrevRect;
	POINT mStart;
	float mDistance; //지팡이이동거리
	bool mReturn;

public:
	void Init()override;
	void Init(int x, int y, float angle);
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
	bool GetIsReturn() { return mReturn; }
};



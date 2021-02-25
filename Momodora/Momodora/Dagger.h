#pragma once
#include "GameObject.h"

class Animation;
class Dagger :
	public GameObject
{
	Image* mImage;
	Player* mPlayer;
	Animation* mLeftMove;
	Animation* mRightMove;
	Animation* mCurrentAnimation;

	float mAngle;
	float mSpeed;
	int mAtk;
	RECT mPrevRect;
	POINT mTarget;

public:
	void Init()override;
	void Init(int x, int y, float angle);
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
};


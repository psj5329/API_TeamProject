#pragma once
#include "GameObject.h"

class Player;
class Animation;
class Bomb :
	public GameObject
{
	Player* mPlayer;
	float mAngle;
	float mSpeed;
	RECT mPrevRect;
	float mTargetX;
	float mTargetY;
	float mStartX;
	float mStartY;
	float mGravity;
	bool mIsExplode;
	float mFrameCount;
	int mAtk;

	Image* mImage;
	Image* mFireImage;
	Animation* mLeftMove;
	Animation* mRightMove;
	Animation* mExplosion;
	Animation* mCurrentAnimation;

public:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
	void Init(int x, int y, float angle,float targetX,float targetY);
	void Explode();
	void EndExplosion();
};
#pragma once

#include "GameObject.h"

enum class State : int
{
	LeftIdle,
	LeftRun,
	LeftJump,
	LeftCrouch,

	RightIdle,
	RightRun,
	RightJump,
	RightCrouch,

	Roll,
	Ladder
};

class Image;
class Animation;

class Player : public GameObject
{
	State mState = State::RightIdle;
	float mSpeed = 250.f;
	float mJumpPower;
	float mGravity = 0.2f;

	bool invincibility = 0;
	int isinvincible = 1;
	bool stopmove = 0;

	Image* mIdleImage;
	Image* mRunImage;
	Image* mTurnImage;
	Image* mJumpImage;
	Image* mFallImage;
	Image* mCrouchImage;
	Image* mRiseImage;
	Image* mRollImage;
	Image* mLadderUpImage;
	Image* mLadderDownImage;

	Image* mCurrentImage;

	Animation* mLeftIdleAnimation;
	Animation* mLeftRunStartAnimation;
	Animation* mLeftRunAnimation;
	Animation* mLeftTurnAnimation;
	Animation* mLeftJumpAnimation;
	Animation* mLeftFallAnimation;
	Animation* mLeftCrouchAnimation;
	Animation* mLeftRiseAnimation;
	Animation* mLeftRollAnimation;

	Animation* mRightIdleAnimation;
	Animation* mRightRunStartAnimation;
	Animation* mRightRunAnimation;
	Animation* mRightTurnAnimation;
	Animation* mRightJumpAnimation;
	Animation* mRightFallAnimation;
	Animation* mRightCrouchAnimation;
	Animation* mRightRiseAnimation;
	Animation* mRightRollAnimation;

	Animation* mLadderUpAnimation;
	Animation* mLadderDownAnimation;

	Animation* mCurrentAnimation;	//ÇöÀç ¾Ö´Ï¸ÞÀÌ¼Ç


public:

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
	RECT GetRect() { return mRect; }
  
	void SetStateRun();
};




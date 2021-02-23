#pragma once

#include "GameObject.h"

enum class State : int
{
	LeftIdle,
	LeftRun,
	LeftJump,
	LeftFall,
	LeftCrouch,
	LeftRoll,
	LeftEnterLadder,

	RightIdle,
	RightRun,
	RightJump,
	RightFall,
	RightCrouch,
	RightRoll,
	RightEnterLadder,

	LadderUp,
	LadderDown
};

class Image;
class Animation;

class Player : public GameObject
{
	State mState = State::RightIdle;
	float mSpeed = 400.f;
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
	Image* mLadderEnterImage;
	Image* mLadderLeaveImage;

	Image* mCurrentImage; //현재 이미지

	Animation* mLeftIdleAnimation;
	Animation* mLeftRunStartAnimation;
	Animation* mLeftRunAnimation;
	Animation* mLeftTurnAnimation;
	Animation* mLeftJumpAnimation;
	Animation* mLeftFallAnimation;
	Animation* mLeftCrouchAnimation;
	Animation* mLeftRiseAnimation;
	Animation* mLeftRollAnimation;
	Animation* mLeftLadderEnterAnimation;
	Animation* mLeftLadderLeaveAnimation;

	Animation* mRightIdleAnimation;
	Animation* mRightRunStartAnimation;
	Animation* mRightRunAnimation;
	Animation* mRightTurnAnimation;
	Animation* mRightJumpAnimation;
	Animation* mRightFallAnimation;
	Animation* mRightCrouchAnimation;
	Animation* mRightRiseAnimation;
	Animation* mRightRollAnimation;
	Animation* mRightLadderEnterAnimation;
	Animation* mRightLadderLeaveAnimation;

	Animation* mLadderUpAnimation;
	Animation* mLadderDownAnimation;

	Animation* mCurrentAnimation;	//현재 애니메이션


public:

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
	RECT GetRect() { return mRect; }
  
	void SetStateRun();
	void SetStateIdle();
	void SetStateFall();
	void SetStateLadderUp();
	void SetStateLadderDown();
};




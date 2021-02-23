#pragma once

#include "GameObject.h"

enum class State : int
{
	LeftIdle,
	LeftRun,
	LeftJump,
	LeftFall,
	LeftCrouch,
	LeftRise,
	LeftRoll,
	LeftEnterLadder,

	RightIdle,
	RightRun,
	RightJump,
	RightFall,
	RightCrouch,
	RightRise,
	RightRoll,
	RightEnterLadder,

	LadderUp,
	LadderDown
};

class Image;
class Animation;

class Player : public GameObject
{
	vector<class Arrow*> mArrow;
	float mArrowSpeed = 600.f;
	Image* mArrowImage;

	State mState = State::RightIdle;
	float mSpeed = 400.f;
	float mJumpPower;
	float mGravity = 0.2f;

	bool invincibility = 0;
	int isinvincible = 1;
	bool stopmove = 0;
	bool stoproll = 0;

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
	Image* mBowImage;
	Image* mAirBowImage;
	Image* mCrouchBowImage;

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
	Animation* mLeftBowAnimation;
	Animation* mLeftAirBowAnimation;
	Animation* mLeftCrouchBowAnimation;

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
	Animation* mRightBowAnimation;
	Animation* mRightAirBowAnimation;
	Animation* mRightCrouchBowAnimation;

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




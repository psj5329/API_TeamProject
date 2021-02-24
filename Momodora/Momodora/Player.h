#pragma once
#include "GameObject.h"

enum class State : int
{
	LeftIdle,
	LeftRun,
	LeftTurn,
	LeftBrake,
	LeftJump,
	LeftFall,
	LeftLandSoft,
	LeftCrouch,
	LeftRise,
	LeftRoll,
	LeftLadderEnter,
	LeftAttack1,
	LeftAttack2,
	LeftAttack3,
	LeftAirAttack,

	RightIdle,
	RightRun,
	RightTurn,
	RightBrake,
	RightJump,
	RightFall,
	RightLandSoft,
	RightCrouch,
	RightRise,
	RightRoll,
	RightLadderEnter,
	RightAttack1,
	RightAttack2,
	RightAttack3,
	RightAirAttack,

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
	float mJumpPower = 0;
	float mGravity = 0;

	bool invincibility = 0;
	bool stopmove = 0;
	bool stoproll = 0; //불값 추가 질문
	bool onground = 0;

	RECT mPrevRect;

	Image* mIdleImage;
	Image* mRunImage;
	Image* mBrakeImage;
	Image* mTurnImage;
	Image* mJumpImage;
	Image* mFallImage;
	Image* mLandSoftImage;
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
	Image* mAttack1Image;
	Image* mAttack2Image;
	Image* mAttack3Image;
	Image* mAirAttackImage;

	Image* mCurrentImage; //현재 이미지

	Animation* mLeftIdleAnimation;
	Animation* mLeftRunStartAnimation;
	Animation* mLeftRunAnimation;
	Animation* mLeftBrakeAnimation;
	Animation* mLeftTurnAnimation;
	Animation* mLeftJumpAnimation;
	Animation* mLeftFallAnimation;
	Animation* mLeftLandSoftAnimation;
	Animation* mLeftCrouchAnimation;
	Animation* mLeftRiseAnimation;
	Animation* mLeftRollAnimation;
	Animation* mLeftLadderEnterAnimation;
	Animation* mLeftLadderLeaveAnimation;
	Animation* mLeftBowAnimation;
	Animation* mLeftAirBowAnimation;
	Animation* mLeftCrouchBowAnimation;
	Animation* mLeftAttack1Animation;
	Animation* mLeftAttack2Animation;
	Animation* mLeftAttack3Animation;
	Animation* mLeftAirAttackAnimation;

	Animation* mRightIdleAnimation;
	Animation* mRightRunStartAnimation;
	Animation* mRightRunAnimation;
	Animation* mRightBrakeAnimation;
	Animation* mRightTurnAnimation;
	Animation* mRightJumpAnimation;
	Animation* mRightFallAnimation;
	Animation* mRightLandSoftAnimation;
	Animation* mRightCrouchAnimation;
	Animation* mRightRiseAnimation;
	Animation* mRightRollAnimation;
	Animation* mRightLadderEnterAnimation;
	Animation* mRightLadderLeaveAnimation;
	Animation* mRightBowAnimation;
	Animation* mRightAirBowAnimation;
	Animation* mRightCrouchBowAnimation;
	Animation* mRightAttack1Animation;
	Animation* mRightAttack2Animation;
	Animation* mRightAttack3Animation;
	Animation* mRightAirAttackAnimation;

	Animation* mLadderUpAnimation;
	Animation* mLadderDownAnimation;

	Animation* mCurrentAnimation;	//현재 애니메이션


public:
	Player();

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
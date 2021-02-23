#pragma once

#include "GameObject.h"

enum class State : int	//추가
{
	Left,
	Right
};

class Image;
class Animation;

class Player : public GameObject
{
	State mState;
	float mSpeed;
	float mJumpPower;
	float mGravity;

	Image* mIdleImage;
	Image* mRunImage;
	Image* mJumpImage;
	Image* mFallImage;
	Image* mCrouchImage;
	Image* mRiseImage;

	Image* mCurrentImage;

	Animation* mLeftIdleAnimation;
	Animation* mLeftRunStartAnimation;
	Animation* mLeftRunAnimation;
	Animation* mLeftJumpAnimation;
	Animation* mLeftFallAnimation;
	Animation* mLeftCrouchAnimation;
	Animation* mLeftRiseAnimation;

	Animation* mRightIdleAnimation;
	Animation* mRightRunStartAnimation;
	Animation* mRightRunAnimation;
	Animation* mRightJumpAnimation;
	Animation* mRightFallAnimation;
	Animation* mRightCrouchAnimation;
	Animation* mRightRiseAnimation;

	Animation* mCurrentAnimation;	//현재 애니메이션


public:

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
	RECT GetRect() { return mRect; }


	void SetStateRun();
};




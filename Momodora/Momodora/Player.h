#pragma once

#include "GameObject.h"

enum class State : int
{
	Left,
	Right
};

class Player : public GameObject
{
	State mState = State::Right;
	float mSpeed = 200.f;

	class Image* mIdleImage;
	class Image* mRunImage;
	class Image* mJumpImage;

	class Animation* mLeftIdleAnimation;
	class Animation* mLeftRunAnimation;
	class Animation* mLeftJumpAnimation;
	class Animation* mLeftFallAnimation;

	class Animation* mRightIdleAnimation;
	class Animation* mRightRunAnimation;
	class Animation* mRightJumpAnimation;
	class Animation* mRightFallAnimation;

	class Animation* mCurrentAnimation;	//���� �ִϸ��̼�

public:

	void Init()override;
	void Update()override;
	void Render(HDC hdc)override;
	RECT GetRect() { return mRect; }
};


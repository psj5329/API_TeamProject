#pragma once
#include "Enemy.h"
class DaggerImp :
	public Enemy
{
	float mJumpPower;
	float mGravity;

	bool isGround;
	bool mThrown;
	RECT bottom;
	RECT mPrevRect;


public:
	void Init() override;
	void Release()override;
	void Update() override;
	void Render(HDC hdc) override;

	void JumpAround();
	void ThrowDagger();
	void EndAttack()override;
};


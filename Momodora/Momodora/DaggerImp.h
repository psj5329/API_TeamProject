#pragma once
#include "Enemy.h"
class DaggerImp :
	public Enemy
{
	float mJumpPower;
	float mGravity;

	bool isGround;
	RECT bottom;


public:
	void Init() override;
	void Release()override;
	void Update() override;
	void Render(HDC hdc) override;

	void JumpAround();

};


#pragma once
#include "GameObject.h"

class Image;
class StarItem : public GameObject
{
	Image* mImage;

	float mSpeed;
	float mAngle;
	float mJumpPower;
	float mFirstJumpPower;
	bool mIsJump;

public:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

public:
	void SetAngle(float angle) { mAngle = angle; }
};


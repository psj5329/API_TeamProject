#pragma once
#include "GameObject.h"

class Image;
class Player;
class StarItem : public GameObject
{
	Image* mImage;
	Player* mPlayer;

	float mSpeed;
	float mAngle;
	float mJumpPower;
	float mFirstJumpPower;
	bool mIsJump;
	bool mIsColl;

	float mFrameCount;

public:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;


public:
	void SetAngle(float angle) { mAngle = angle; }
	void Magnet();
};


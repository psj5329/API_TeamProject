#pragma once
#include "GameObject.h"

enum class BulletPattern { PatternIdle, PatternBulletDown, PatternBulletUp, PatternBulletTarget };

class Image;
class BossBullet : public GameObject
{
	Image* mImage;
	BulletPattern mPattern;
	float mAngle;
	float mSpeed;

	float mShootTime;
	bool mIsShoot;
	bool mIsShow;

public:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

public:
	BulletPattern GetPattern() { return mPattern; }
	bool GetShoot() { return mIsShoot; }

	void SetAngle(float angle) { mAngle = angle; }
	void SetPattern(BulletPattern pattern) { mPattern = pattern; }
};
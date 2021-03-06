#pragma once
#include "UI.h"

class Image;
class BossHpUI : public UI
{
	Image* mBackImage;
	Image* mLessImage;
	Image* mNameImage;

	int mMaxHp;
	int mHp;
	int mPreHp;

	float mLessHpSizeX;

public:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

public:
	void SetHp(int hp) { mMaxHp = hp; mHp = hp; mPreHp = hp; }
};
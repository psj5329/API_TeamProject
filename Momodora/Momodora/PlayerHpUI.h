#pragma once
#include "UI.h"

class Image;
class PlayerHpUI : public UI
{
	Image* mBackImage;
	Image* mLessImage;

	int mMaxHp;
	int mHp;

public:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

public:
	void SetHp(int hp) { mMaxHp = hp; mHp = hp; }
};


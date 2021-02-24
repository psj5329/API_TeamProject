#pragma once
#include "UI.h"

class Image;
class StarCountUI : public UI
{
	Image* mHundredImage;
	Image* mTenImage;
	Image* mOneImage;

	int mStarCount;

	float mHundredSizeX;
	float mHundredSizeY;
	float mTenSizeX;
	float mTenSizeY;
	float mOneSizeX;
	float mOneSizeY;

public:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

public:
	void SetStarCount(int count) { mStarCount = count; }

	int GetStarCount() { return mStarCount; }
};


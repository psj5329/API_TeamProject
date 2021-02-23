#pragma once
#include "GameObject.h"

enum class PlatformType : int
{
	Normal = 0,
	DownJump,
	End
};

class Platform : public GameObject
{
	PlatformType mPlatformType;

public:
	Platform();
	Platform(float x, float y);

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

	PlatformType GetPlatformType()const { return mPlatformType; }
	void SetPlatformType(PlatformType platformType) { mPlatformType = platformType; }

	void SetPlatform (int left, int top, int right, int bottom, PlatformType platformType) {
		mRect.left = left; mRect.top = top; mRect.right = right; mRect.bottom = bottom; mPlatformType = platformType; }
};
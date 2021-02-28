#pragma once
#include "Scene.h"

class Scene09 final : public Scene
{
	Image* mPlatformImage;
	Image* mPlatformImage2;
	bool mIsBossDead;
	bool mIsBossAppearanceEvent;
	bool mIsChangeImage;
	float mChangeImageTime;
	bool mCameraFix;

public:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
};
#pragma once
#include "Scene.h"

class Scene05 : public Scene
{
	Image* mPlatformImage;
	Image* mPlatformImage2;
	bool mIsBossDead;
	bool mIsBossAppearanceEvent;
	bool mIsChangeImage;
	float mChangeImageTime;
	bool mCameraFix;

	Image* mFixDia;
	Image* mFixRect;

	int mImageDR[20];
	float mImageAlpha[20];
	int mOrder;
	int mImageX[480];
	int mImageY[480];
	float mImageCreateDelay;

	int mBlockStart;

public:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

public:
	void PlaceRect2();
};
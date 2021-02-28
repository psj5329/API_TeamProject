#pragma once
#include "Scene.h"

class Scene04 : public Scene
{
	bool FennelIntro;

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
	void PlaceRect();
	void PlaceRect2();
	void RemoveRect3();
};
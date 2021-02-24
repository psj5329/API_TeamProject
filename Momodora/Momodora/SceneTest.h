#pragma once
#include "Scene.h"

class Image;
class Platform;

class SceneTest final : public Scene
{
	Image* mMapTest;
	Image* mRectEff[100];
	float mAlpha[100];
	bool mA[100];
	int a;

	int mx[1000];
	int my[1000];

	float createTime;

	vector<int> crea;

public:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
};
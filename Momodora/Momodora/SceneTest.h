#pragma once
#include "Scene.h"

class Image;
class Platform;

class SceneTest final : public Scene
{
	Image* mMapTest;
	Image* mFixDia;
	Image* mFixRect;

	int mImageDR[20]; // 0이면 비활성화, 1이면 다이아, 2면 렉트
	float mImageAlpha[20]; // 24개 동시에 운영하는 알파값
	int mOrder; // 순번
	int mImageX[480]; // 24 * 순번 개수
	int mImageY[480]; // 24 * 순번 개수
	float mImageCreateDelay; // 0.5초마다 24개 동시 생성

public:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
};
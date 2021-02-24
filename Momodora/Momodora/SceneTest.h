#pragma once
#include "Scene.h"

class Image;
class Platform;

class SceneTest final : public Scene
{
	Image* mMapTest;
	Image* mFixDia;
	Image* mFixRect;

	int mImageDR[20]; // 0�̸� ��Ȱ��ȭ, 1�̸� ���̾�, 2�� ��Ʈ
	float mImageAlpha[20]; // 24�� ���ÿ� ��ϴ� ���İ�
	int mOrder; // ����
	int mImageX[480]; // 24 * ���� ����
	int mImageY[480]; // 24 * ���� ����
	float mImageCreateDelay; // 0.5�ʸ��� 24�� ���� ����

public:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
};
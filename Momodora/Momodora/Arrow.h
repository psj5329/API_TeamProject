#pragma once
#include "GameObject.h"

class Arrow :public GameObject
{
	float mX;
	float mY;
	float mSpeed;
	float mAngle;
	RECT mRect;
	int mArrowIndexY = 0;
	int mArrowDamage = 0;

	Image* mImage;

public:
	void Init()override;
	void Fire(class Image* image, float x, float y, float speed, float angle);
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
	//RECT GetRect() { return mRect; };
	void SetArrowIndexY(int IndexY) { mArrowIndexY = IndexY; }

	int GetArrowDamage() { return mArrowDamage; }
};
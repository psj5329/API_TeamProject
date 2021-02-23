#pragma once

class Arrow
{
	float mX;
	float mY;
	float mSpeed;
	float mAngle;
	RECT mRect;
	int mArrowIndexY = 0;

	Image* mImage;

public:
	void Fire(class Image* image, float x, float y, float speed, float angle);
	void Release();
	void Update();
	void Render(HDC hdc);
	RECT GetRect() { return mRect; };
	void SetArrowIndexY(int IndexY) { mArrowIndexY = IndexY; }
};
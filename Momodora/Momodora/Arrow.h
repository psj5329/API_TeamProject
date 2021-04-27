#pragma once
#include "GameObject.h"

class Arrow : public GameObject
{
    float mSpeed;
    float mAngle;
    int mArrowIndexY = 0;
    int mArrowDamage = 0;

    Image* mImage;

public:
	void Fire(class Image* image, float x, float y, float speed, float angle);

	void Init()override {}
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

	void SetArrowIndexY(int IndexY) { mArrowIndexY = IndexY; }

    int GetArrowDamage() { return mArrowDamage; }
};
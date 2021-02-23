#pragma once
#include "GameObject.h"

class Ladder : public GameObject
{
public:
	Ladder();
	Ladder(float x, float y);

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

	void SetLadder(int left, int top, int right, int bottom) { mRect.left = left; mRect.top = top; mRect.right = right; mRect.bottom = bottom; }
};
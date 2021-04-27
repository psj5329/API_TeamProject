#pragma once
#include "GameObject.h"

class Animation;
class Effect :
	public GameObject
{
	int frameCount;
	int frameUpdateCount;
	int frameIndexX;

	Animation* mAnimation;
	Animation* mCurrentAnimation;

	class Image* mImage;

	bool mIsEnd;	//������????
public:
	void Init(wstring imageKey, float x, float y, int startFrameX, int endFrameX, float frameUpdateTime);
	void Init()override {};
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

	void EndEffect();
};
#pragma once
#include "GameObject.h"

class Image;
class Animation;

class Leaf : public GameObject
{
	Image* mLeafImage01;
	Image* mLeafImage02;
	Image* mLeafImage03;
	Image* mCurrentImage;

	Animation* mLeaf01Left;
	Animation* mLeaf01Right;
	Animation* mLeaf02Left;
	Animation* mLeaf02Right;
	Animation* mLeaf03Left;
	Animation* mLeaf03Right;
	Animation* mCurrentAnimation;

public:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
};
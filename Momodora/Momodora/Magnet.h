#pragma once
#include "GameObject.h"
class Magnet :
	public GameObject
{

	Image* mImage;
	Player* mPlayer;

public:
	Magnet();
	Magnet(float x, float y);
	void Init()override;
	void Init(float x, float y);	//x,y ´Â ÁÂÇ¥
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
};
#pragma once
#include "GameObject.h"
class Player;
class Potion :
	public GameObject
{
	Image* mImage;
	Player* mPlayer;
	int mType;
	
public:
	Potion();
	Potion(float x, float y);
	void Init()override;
	void Init(float x, float y, int type);	//x,y 는 좌표, 0은 체력 1는 공격력
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
};


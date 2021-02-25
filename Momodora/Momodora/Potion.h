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
	void Init(float x, float y, int type);	//x,y �� ��ǥ, 0�� ü�� 1�� ���ݷ�
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
};


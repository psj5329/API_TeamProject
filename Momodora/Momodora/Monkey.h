#pragma once
#include "Enemy.h"
class Monkey :
	public Enemy
{
	int mRange;		//패트롤 반경

public:
	void Init() override;
	void Release()override;
	void Update() override;
	void Render(HDC hdc) override;
	//void AddMonkey(int startX, int startY);


	void Patrol();
	void SearchPlayer();
	void Attack()override;
	void EndAttack()override;
	RECT GetAtkBox() { return mAttackBox; }
};


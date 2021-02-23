#pragma once
#include "Enemy.h"
class Fennel :
	public Enemy
{

	Animation* mRightBuff;
	Animation* mLeftBuff;
	Animation* mRightAtk2;
	Animation* mLeftAtk2;
	Animation* mRightBackflip;
	Animation* mLeftBackflip;
	Animation* mRightPlunge;
	Animation* mLeftPlunge;
	Animation* mRightDeath;
	Animation* mLeftDeath;
	Animation* mRightThunder;
	Animation* mLeftThunder;
	Animation* mRightJumpReady;
	Animation* mLeftJumpReady;
	Animation* mRightDash;
	Animation* mLeftDash;




public:
	void Init() override;
	void Release()override;
	void Update() override;
	void Render(HDC hdc) override;

	//void SearchPlayer();
	void EndAttack()override;

};


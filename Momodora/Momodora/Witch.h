#pragma once
#include "Enemy.h"

class Animation;
class Witch :
	public Enemy
{
	Animation* mRightDeath;
	Animation* mLeftDeath;
	Animation* mRightCatch;
	Animation* mLeftCatch;

	bool mHoldStaff;

public:
	void Init() override;
	void Release()override;
	void Update() override;
	void Render(HDC hdc) override;

	void SearchPlayer();
	void EndAttack()override;
};


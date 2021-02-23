#pragma once
#include "Enemy.h"

class Staff;
class Animation;
class Witch :
	public Enemy
{
	Animation* mRightDeath;
	Animation* mLeftDeath;
	Animation* mRightCatch;
	Animation* mLeftCatch;

	Staff* mStaff;

	bool mHoldStaff;
	bool mThrown;
public:
	void Init() override;
	void Release()override;
	void Update() override;
	void Render(HDC hdc) override;

	void SearchPlayer();
	void EndAttack()override;
	void EndCatch();
	void Attack()override;
};


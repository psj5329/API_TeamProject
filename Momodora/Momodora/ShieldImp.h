#pragma once
#include "Enemy.h"
class ShieldImp :
	public Enemy
{
	bool mThrown;

public:
	void Init() override;
	void Release()override;
	void Update() override;
	void Render(HDC hdc) override;

	void ThrowDagger();
	void EndAttack() override;
	void SetPosition(float x, float y)override;
};


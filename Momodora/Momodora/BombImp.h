#pragma once
#include "Enemy.h"
class BombImp :
	public Enemy
{
	bool mThrown;

public:
	void Init() override;
	void Release()override;
	void Update() override;
	void Render(HDC hdc) override;

	void ThrowBomb();		//공격
	void EndThrow();	//공격애니메이션끝나고 실행할함수

	void SetPosition(float startX, float startY)override;

};


#pragma once
#include "Enemy.h"
class BombImp :
	public Enemy
{


public:
	void Init() override;
	void Release()override;
	void Update() override;
	void Render(HDC hdc) override;

	void ThrowBomb();		//공격
	void SearchPlayer();	//플레이어 찾아서 방향정하기
	void EndThrow();	//공격애니메이션끝나고 실행할함수
};


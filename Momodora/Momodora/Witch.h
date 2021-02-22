#pragma once
#include "Enemy.h"
class Witch :
	public Enemy
{

public:
	void Init() override;
	void Release()override;
	void Update() override;
	void Render(HDC hdc) override;

	void SearchPlayer();

};


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

	void ThrowBomb();		//����
	void EndThrow();	//���ݾִϸ��̼ǳ����� �������Լ�
};


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

	void ThrowBomb();		//����
	void SearchPlayer();	//�÷��̾� ã�Ƽ� �������ϱ�
	void EndThrow();	//���ݾִϸ��̼ǳ����� �������Լ�
};

#pragma once
#include "Enemy.h"

enum class FennelState
{
	Idle,
	Attack,
	Attack2,
	Hurt,
	Jump,
	JumpReady,
	Death,
	Plunge,
	Thunder,
	Buff,
	Dash,
	BackFlip
};

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


	FennelState mFennelState;


	RECT mImpact;
	Image* mImpactImg;
	Animation* mImpactAni;
	Animation* mCurrentImpact;

	RECT mThunder;
	Image* mThunderImg;

	RECT mSword;



public:
	void Init() override;
	void Release()override;
	void Update() override;
	void Render(HDC hdc) override;

	//void SearchPlayer();
	void SetImageAnimation();	//���¿����� �̹����� �ִϸ��̼� ����
	
	//������
	void Attack();
	void Attack2();
	void Backflip();
	void Plunge();
	void Thunder();
	void Hurt();
	void Buff();
	void Death();
	void Dash();

	//�ݹ���ģ����
	void EndAttack()override;
	void EndAttack2();
	void EndMove();
	void JumpReadytoJump();
	void JumptoPlunge();
	void EndPlunge();
};


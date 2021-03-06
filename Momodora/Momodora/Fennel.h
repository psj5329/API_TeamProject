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
	BackFlip,
	Intro
};

struct AfterImage
{
	Image* cImage;
	RECT cRect;
	Animation* cAnimation;
	float cAlpha;
	int cFrameX;
	int cFrameY;
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
	Animation* mIntro1;
	Animation* mIntro2;
	Animation* mIntro3;

	FennelState mFennelState;

	//내려찍기
	RECT mImpact;
	Image* mImpactImg;
	Animation* mImpactAni;
	Animation* mCurrentImpact;

	//번개
	RECT mThunder;
	Image* mThunderImg;
	Animation* mThunderAni;
	Animation* mCurrentThunder;
	POINT mTarget;

	//버프
	Image* mFloorEffectImg;
	Animation* mFloorAni;
	Animation* mCurrentFloor;
	POINT mFloorEffect;

	float mTimer;

	vector <AfterImage> mAfterImages;

	bool mIntroEnd;	//인트로가 끝났나

public:
	void Init() override;
	void Release()override;
	void Update() override;
	void Render(HDC hdc) override;

	//void SearchPlayer();
	void SetImageAnimation();	//상태에따라 이미지와 애니메이션 설정

	//움직임
	void Attack();
	void Attack2();
	void Backflip();
	void Plunge();
	void Thunder();
	void Hurt();
	void Buff();
	void Death();
	void Dash();

	//m렉트조정
	void AttackRect();
	void Attack2Rect();
	void BackflipRect();
	void JumpRect();
	void PlungeRect();
	void ThunderRect();
	void DashRect();

	//칼렉트설정
	void AttackSword();
	void Attack2Sword();

	//콜백할친구들
	void EndAttack()override;
	void EndAttack2();
	void EndMove();
	void JumpReadytoJump();
	void JumptoPlunge();
	void EndPlunge();
	void EndBuff();
	void EndDeath();
	void EndIntro1();
	void EndIntro2();
	void EndIntro3();

	void SetAfterImages(int frame1, int frame2, int frame3);

	//랙트겟
	RECT GetThunderRect(void) { return mThunder; }
	RECT GetImpactRect(void) { return mImpact; }

	//인트로끝났니?
	bool GetIntroEnd() { return mIntroEnd; }

};


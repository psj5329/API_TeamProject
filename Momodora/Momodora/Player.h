#pragma once
#include "GameObject.h"

enum class PlayerState : int
{
	Idle,
	Run,
	Brake,
	Turn,
	Jump,
	Fall,
	LandSoft,
	Crouch,
	Rise,
	Roll,
	LadderEnter,
	LadderUp, // 좌우없음
	LadderDown, // 좌우없음
	//LadderLeave,		// 필요한지 물어보기
	Bow,				// 없어도 되는지 물어보기
	AirBow,			// 없어도 되는지 물어보기
	CrouchBow,		// 없어도 되는지 물어보기
	Attack1,
	Attack2,
	Attack3,
	AirAttack,
	Hurt,
	Death
};

class Image;
class Animation;
class Leaf;

class Player : public GameObject
{
	vector<class Arrow*> mArrow;
	float mArrowSpeed;
	Image* mArrowImage;

	PlayerState mState;
	float mSpeed;
	float mJumpPower;
	float mGravity;

	int mHp;
	int mAttackDamage;

	bool invincibility;
	bool stopmove;
	bool stoproll;

	bool mHitAttack;

	RECT mPrevRect;

	bool mHaveMagnet;
	Leaf* mLeaf;

	Image* mIdleImage;
	Image* mRunImage;
	Image* mBrakeImage;
	Image* mTurnImage;
	Image* mJumpImage;
	Image* mFallImage;
	Image* mLandSoftImage;
	Image* mCrouchImage;
	Image* mRiseImage;
	Image* mRollImage;
	Image* mLadderUpImage;
	Image* mLadderDownImage;
	Image* mLadderEnterImage;
	Image* mLadderLeaveImage;
	Image* mBowImage;
	Image* mAirBowImage;
	Image* mCrouchBowImage;
	Image* mAttack1Image;
	Image* mAttack2Image;
	Image* mAttack3Image;
	Image* mAirAttackImage;
	Image* mHurtImage;
	Image* mDeathImage;

	Image* mCurrentImage;

	Animation* mLeftIdleAnimation;
	Animation* mLeftRunStartAnimation;
	Animation* mLeftRunAnimation;
	Animation* mLeftBrakeAnimation;
	Animation* mLeftTurnAnimation;
	Animation* mLeftJumpAnimation;
	Animation* mLeftFallAnimation;
	Animation* mLeftLandSoftAnimation;
	Animation* mLeftCrouchAnimation;
	Animation* mLeftRiseAnimation;
	Animation* mLeftRollAnimation;
	Animation* mLeftLadderEnterAnimation;
	Animation* mLeftLadderLeaveAnimation;
	Animation* mLeftBowAnimation;
	Animation* mLeftAirBowAnimation;
	Animation* mLeftCrouchBowAnimation;
	Animation* mLeftAttack1Animation;
	Animation* mLeftAttack2Animation;
	Animation* mLeftAttack3Animation;
	Animation* mLeftAirAttackAnimation;
	Animation* mLeftHurtAnimation;
	Animation* mLeftDeathAnimation;

	Animation* mRightIdleAnimation;
	Animation* mRightRunStartAnimation;
	Animation* mRightRunAnimation;
	Animation* mRightBrakeAnimation;
	Animation* mRightTurnAnimation;
	Animation* mRightJumpAnimation;
	Animation* mRightFallAnimation;
	Animation* mRightLandSoftAnimation;
	Animation* mRightCrouchAnimation;
	Animation* mRightRiseAnimation;
	Animation* mRightRollAnimation;
	Animation* mRightLadderEnterAnimation;
	Animation* mRightLadderLeaveAnimation;
	Animation* mRightBowAnimation;
	Animation* mRightAirBowAnimation;
	Animation* mRightCrouchBowAnimation;
	Animation* mRightAttack1Animation;
	Animation* mRightAttack2Animation;
	Animation* mRightAttack3Animation;
	Animation* mRightAirAttackAnimation;
	Animation* mRightHurtAnimation;
	Animation* mRightDeathAnimation;

	Animation* mLadderUpAnimation;
	Animation* mLadderDownAnimation;

	Animation* mCurrentAnimation;

public:
	Player();

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

public:
	void FindPlayerImage();
	void ReadyPlayerAnimation();
	void InitPlayerVar(); // 플레이어가 가진 각종 변수들 초기화 하는 함수

	void SafeDeletePlayerAnimation();

public:
	void SetStateRun();
	void SetStateIdle();
	void SetStateLadderUp();
	void SetStateLadderDown();

	void SetEndAttack();
	void SetEndAirAttack();
	void SetEndCrouchAttack();

public:
	int GetAttackDamage() { return mAttackDamage; }
	int GetHp() { return mHp; }
	void SetHp(int i) { mHp = i; }
	bool GetHitAttack() { return mHitAttack; }
	PlayerState GetState() { return mState; }

	//void SetImageAnimation();

	inline bool GetHaveMagnet()const { return mHaveMagnet; }
	inline void SetHaveMagnet(bool haveMagnet) { mHaveMagnet = haveMagnet; }
};
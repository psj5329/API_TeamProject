#pragma once
#include "GameObject.h"

//상태들
enum class Direction
{
	Right,
	Left
};
enum class EnemyState
{
	Idle,
	Move,
	Attack,
	Hurt,
	Jump,
	Fall,
	Death
};

class Image;
class Player;
class Animation;

class Enemy :
	public GameObject
{
protected:
	Image* mImage;
	Player* mPlayer;

	RECT mHitBox;			//히트박스
	RECT mSearchZone;		//색적범위
	Direction mDirection;	//방향
	EnemyState mEnemyState;	//상태

	POINT mStart;	//시작점
	int mHp;	//체력
	int mAtk;	//공격력
	int mDef;	//방어력
	int mSpeed;
	float mAttackSpeed;	//공격빈도
	int mDistance;		//플레이어와 거리

	bool mFoundPlayer;	//플레이어를 만났나? 만났으면 전투상태로
	
	Animation* mRightIdle;
	Animation* mLeftIdle;
	Animation* mRightMove;
	Animation* mLeftMove;
	Animation* mRightAtk;
	Animation* mLeftAtk;
	Animation* mRightHurt;
	Animation* mLeftHurt;
	Animation* mRightJump;
	Animation* mLeftJump;
	Animation* mRightFall;
	Animation* mLeftFall;
	Animation* mCurrentAnimation;

public:
	virtual void Init() override;
	virtual void Release()override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	inline RECT GetHitBox() { return mHitBox; }
	inline int GetAtk() { return mAtk; }
	inline int GetDef() { return mDef; }
	inline int GetHP() { return mHp; }
	inline void SetHp(int hp) { mHp = hp; }
	void SetPosition(int startX, int startY);

	void Stun();
	void CalculateHp(int attack) { mHp -= attack - mDef; }
	void SetAnimation();
};


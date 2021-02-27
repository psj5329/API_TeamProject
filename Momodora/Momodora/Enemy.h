#pragma once
#include "GameObject.h"

//상태들
enum class EnemyState : int
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
		
	RECT mSearchZone;		//색적범위
	EnemyState mEnemyState;	//상태

	POINT mStart;	//시작점
	int mHp;	//체력
	int mAtk;	//공격력
	int mDef;	//방어력
	int mSpeed;
	float mAttackSpeed;	//공격빈도
	float mSearchSpeed; //플레이어 위치 갱신속도
	int mDistance;		//플레이어와 거리

	bool mFoundPlayer;	//플레이어를 만났나? 만났으면 전투상태로
	bool isHit;
	float mAlpha;

	float mHurtCounter; //경직시간

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
	Enemy();
	Enemy(float x, float y);

	virtual void Init() override;
	virtual void Release()override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	inline int GetAtk() { return mAtk; }
	inline int GetDef() { return mDef; }
	inline int GetHP() { return mHp; }
	inline void SetHp(int hp) { mHp = hp; }
	inline void TakeHp(int hp) { mHp -= hp; }
	inline void SetPlayerPtr(Player* player) { mPlayer = player; }
	inline void SetIsHit(bool hit) { isHit = hit; }
	inline bool GetIsHit() { return isHit; }

	virtual void SetPosition(float startX, float startY); //위치설정 Y에 플랫폼의 top 

	//virtual void Stun(); 
	virtual void EndAttack();
	void CalculateHp(int attack) { mHp -= attack - mDef; }
	void SetAnimation();	//상태에따라 애니메이션 설정
	void SetDirection();	//플레이어위치에따라 좌우설정
	virtual void Attack();
	virtual void DeathCheck();
	void DropGold();	//돈랜덤뿌리기
	void DropGold(int goldNum);	//돈인자만큼뿌리기
	void Hurt();
	void HurtRectMove();
};
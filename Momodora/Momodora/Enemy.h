#pragma once
#include "GameObject.h"

//���µ�
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
		
	RECT mSearchZone;		//��������
	EnemyState mEnemyState;	//����

	POINT mStart;	//������
	int mHp;	//ü��
	int mAtk;	//���ݷ�
	int mDef;	//����
	int mSpeed;
	float mAttackSpeed;	//���ݺ�
	float mSearchSpeed; //�÷��̾� ��ġ ���żӵ�
	int mDistance;		//�÷��̾�� �Ÿ�

	bool mFoundPlayer;	//�÷��̾ ������? �������� �������·�
	bool isHit;
	float mAlpha;

	float mHurtCounter; //�����ð�

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

	virtual void SetPosition(float startX, float startY); //��ġ���� Y�� �÷����� top 

	//virtual void Stun(); 
	virtual void EndAttack();
	void CalculateHp(int attack) { mHp -= attack - mDef; }
	void SetAnimation();	//���¿����� �ִϸ��̼� ����
	void SetDirection();	//�÷��̾���ġ������ �¿켳��
	virtual void Attack();
	virtual void DeathCheck();
	void DropGold();	//�������Ѹ���
	void DropGold(int goldNum);	//�����ڸ�ŭ�Ѹ���
	void Hurt();
	void HurtRectMove();
};
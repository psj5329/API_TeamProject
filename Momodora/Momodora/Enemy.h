#pragma once
#include "GameObject.h"

//���µ�
enum class Direction
{
	Right,
	Left
};
enum class EnemyState
{
	Idle,
	Move,
	Patrol,
	Attack,
	Hurt,
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

	RECT mHitBox;			//��Ʈ�ڽ�
	RECT mSearchZone;		//��������
	Direction mDirection;	//����
	EnemyState mEnemyState;	//����

	POINT mStart;	//������
	int mHp;	//ü��
	int mAtk;	//���ݷ�
	int mDef;	//����
	int mSpeed;
	int mAttackSpeed;	//���ݺ�
	int mDistance;		//�÷��̾�� �Ÿ�

	bool mFoundPlayer;	//�÷��̾ ������? �������� �������·�
	
	virtual void Init() override;
	virtual void Release()override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

public:
	inline RECT GetHitBox() { return mHitBox; }
	inline int GetAtk() { return mAtk; }
	inline int GetDef() { return mDef; }
	inline int GetHP() { return mHp; }
	inline void SetHp(int hp) { mHp = hp; }

	void Stun();
	void CalculateHp(int attack) { mHp -= attack - mDef; }

};


#pragma once
#include "Enemy.h"

// ���� ���� 5�ʿ� �� ���� ���´�
// ������
// 1. bullet 4�� ���� ���� �ΰ� 1234 ������� ����� ������� ������
// 2. bullet 2�� �÷��̾� ��ġ���� ���� � Ÿ�� ���� �ö�
// 3. �级�� �Ʒ��� �������� �� ������ bullet 4���� ���� ���� �ΰ� ��Ÿ���� ���� �ð� �� �÷��̾� ��ġ�� ���ư�

enum class AttackPattern { PatternIdle, PatternBulletDown, PatternBulletUp, PatternBulletTarget };

struct Body {
	Image* image;
	int x;			// ������Ʈ �������� ��ġ�� �ٽ� ��´�
	int y;
	int sizeX;
	int sizeY;
	RECT rc;
	float moveTime;		// ���� �ð����� �������� ���´�
	int moveCount;
	bool move;			// ���Ʒ� �Ǻ� ��
};

class Image;
class BossBullet;
class Boss : public Enemy
{
	Body mBody;					// ������ �� �༮
	Body mBackHair;				// �޸Ӹ�
	Body mHead;					// �Ӹ�
	Body mChest;				// ����
	Body mEyes;					// ����
	Body mPupil;				// ������
	Body mLeftArm;				// ����
	Body mRightArm;				// ������

	bool mIsCloseEyes;
	float mCloseEyesTime;

	bool mIsHit;				// �ǰ� ���ߴ���
	bool mIsInvincibility;		// ��������
	int mHitMoveCount;
	float mHitFrameTime;

	AttackPattern mPattern;
	float mAttackTime;			// �� ������ ������ 5�ʸ��� ������ ���´�

	vector<BossBullet*> mVecBullet;

public:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

public:
	void ImageSetting();
	void MotionFrame();
	void Pattern(AttackPattern pattern);
};


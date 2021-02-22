#pragma once
#include "GameObject.h"

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
class Boss : public GameObject
{
	Body mBody;					// ������ �� �༮
	Body mBackHair;				// �޸Ӹ�
	Body mHead;					// �Ӹ�
	Body mChest;				// ����
	Body mEyes;					// ����
	Body mPupil;				// ������
	Body mLeftArm;				// ����
	Body mRightArm;				// ������

	int mFrameX;				// �Ӹ� ������
	float mFrameTime;


	bool mIsHit;				// �ǰ� ���ߴ���
	float mHitFrameTime;

	float mInvincibilityTime;	// ���� �ð�

public:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

public:
	void ImageSetting();
	void MotionFrame();
};


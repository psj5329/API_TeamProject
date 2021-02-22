#pragma once
#include "GameObject.h"

struct Body {
	Image* image;
	int x;			// 오브젝트 기준으로 위치를 다시 잡는다
	int y;
	int sizeX;
	int sizeY;
	RECT rc;
	float moveTime;		// 일정 시간마다 움직임을 갖는다
	int moveCount;
	bool move;			// 위아래 판별 용
};

class Image;
class Boss : public GameObject
{
	Body mBody;					// 몸통이 될 녀석
	Body mBackHair;				// 뒷머리
	Body mHead;					// 머리
	Body mChest;				// 가슴
	Body mEyes;					// 눈알
	Body mPupil;				// 눈동자
	Body mLeftArm;				// 왼팔
	Body mRightArm;				// 오른팔

	int mFrameX;				// 머리 프레임
	float mFrameTime;


	bool mIsHit;				// 피격 당했는지
	float mHitFrameTime;

	float mInvincibilityTime;	// 무적 시간

public:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

public:
	void ImageSetting();
	void MotionFrame();
};


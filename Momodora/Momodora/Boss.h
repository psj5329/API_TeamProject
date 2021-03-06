#pragma once
#include "Enemy.h"

// 보스 패턴 5초에 한 번씩 나온다
// 패턴은
// 1. bullet 4개 일정 간격 두고 1234 순서대로 생기고 순서대로 떨어짐
// 2. bullet 2개 플레이어 위치에서 생성 곡선 타고 위로 올라감
// 3. 루벨라가 아래로 내려가고 양 옆에서 bullet 4개씩 일정 간격 두고 나타나며 일정 시간 후 플레이어 위치로 날아감

enum class AttackPattern { PatternIdle, PatternBulletDown, PatternBulletUp, PatternBulletTarget };

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
class BossBullet;
class Boss : public Enemy
{
	Body mBody;					// 몸통이 될 녀석
	Body mBackHair;				// 뒷머리
	Body mHead;					// 머리
	Body mChest;				// 가슴
	Body mEyes;					// 눈알
	Body mPupil;				// 눈동자
	Body mLeftArm;				// 왼팔
	Body mRightArm;				// 오른팔

	bool mIsCloseEyes;
	float mCloseEyesTime;

	bool mIsHit;				// 피격 당했는지
	bool mIsInvincibility;		// 무적인지
	int mHitMoveCount;
	float mHitFrameTime;
	bool mIsMoveChest;

	AttackPattern mPattern;		// 공격 패턴
	float mAttackTime;			// 한 패턴이 끝나고 5초마다 패턴이 나온다
	int mAttackCount;			// 두번 패턴 끝나고 타겟패턴
	int mBulletCreateCount;
	float mBulletCreateTime;
	bool mIsDown;
	bool mIsDownSound;
	float mJumpPower;

	vector<BossBullet*> mVecBullet;

	bool mIsEndEvent;

	Image* mBackImage;
	vector<POINT> mVecEraseCenter;
	vector<POINT> mVecBackEraseCenter;
	int mEraseSize;
	float mEraseTime;

public:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

public:
	void ImageSetting();
	void MotionFrame();
	void Pattern();
	void Hit();
	void EraseBossImage();

public:
	bool GetInvincibility() { return mIsInvincibility; }
	bool GetEndEvent() { return mIsEndEvent; }
	Image* GetImage() { return mImage; }
	Image* GetBackImage() { return mBackImage; }
	Animation* GetCurrentAnimation() { return mCurrentAnimation; }
	bool GetEvent() { return mIsEvent; }

	void SetInvincibility(bool b) { mIsInvincibility = b; }
	void SetEndEvent(bool b) { mIsEndEvent = b; }
};
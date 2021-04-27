#include "pch.h"
#include "Boss.h"

#include "Image.h"
#include "Camera.h"
#include "Animation.h"
#include "ObjectManager.h"
#include "BossBullet.h"
#include "Player.h"

#include "GameEvent.h"

void Boss::Init()
{
	srand(unsigned int((NULL)));
	// 보스의 위치는 Body가 기준이지만 Rect는 가슴으로 정한다
	mName = "Boss";
	mImage = IMAGEMANAGER->FindImage(L"Boss");
	mBackImage = IMAGEMANAGER->FindImage(L"Boss_back");
	mX = WINSIZEX / 2;
	mY = 1600 + mImage->GetHeight() * 2;
	mSizeX = 630;//IMAGEMANAGER->FindImage(L"Boss_Chest")->GetWidth();	// 셋팅했을 때 기준 * 2 (크기 두배라)
	mSizeY = 960;//IMAGEMANAGER->FindImage(L"Boss_Chest")->GetHeight();

	ImageSetting();

	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	mHitBox = mChest.rc;

	mIsCloseEyes = false;
	mCloseEyesTime = 0.f;

	mIsHit = false;
	mIsInvincibility = false;
	mHitMoveCount = 0;
	mHitFrameTime = 0.f;

	mLeftIdle = new Animation();
	mLeftIdle->InitFrameByStartEnd(0, 0, 4, 0, false);
	mLeftIdle->SetIsLoop(true);
	mLeftIdle->SetFrameUpdateTime(0.2f);

	// enemy 상속
	mHp = 500;
	mAtk = 10;
	mDef = 50;

	// 얘네는 머리 애니메이션때문에
	mEnemyState = EnemyState::Idle;
	mDirection = Direction::Left;
	mCurrentAnimation = mLeftIdle;

	// 공격 패턴 및 총알 생성
	mPattern = AttackPattern::PatternIdle;		// 아무것도 안하는 상태
	mAttackTime = 0.f;
	mAttackCount = 0;
	mBulletCreateCount = 0;
	mBulletCreateTime = 0.f;

	mIsDown = false;
	mJumpPower = 15.f;

	mIsEndEvent = false;
	mIsEvent = true;

	mEraseSize = 2.f;
	int num = sqrtf(WINSIZEX * WINSIZEX + WINSIZEY * WINSIZEY) / 2;// / mEraseSize;

	for (int i = 0; i < num; ++i)
	{
		//POINT p = { WINSIZEX / num * i, WINSIZEY / num * i };
		POINT p = { i * 2 - WINSIZEX / 3, i * 2 + WINSIZEY / 3 };
		mVecEraseCenter.push_back(p);
	}
	mVecBackEraseCenter = mVecEraseCenter;

	mEraseTime = 0.f;
}

void Boss::Release()
{
}

void Boss::Update()
{
	if (mIsEvent)
	{
		MotionFrame();
		return;
	}

	if (mIsEndEvent)
	{
		mEraseTime += TIME->DeltaTime();

		if (mCurrentAnimation->GetCurrentFrameIndex() == 0)
			mCurrentAnimation->Stop();
		//EraseBossImage();
		MotionFrame();
		return;
	}

	if (mPattern == AttackPattern::PatternIdle)
		mAttackTime += TIME->DeltaTime();

	if (mAttackTime >= 4.f)		// 테스트용 2초
	{
		mAttackCount++;
		mAttackTime = 0.f;
		if (mAttackCount != 3)
		{
			int num = rand() % 2;
			if (num == 0)
				mPattern = AttackPattern::PatternBulletDown;
			else if (num == 1)
				mPattern = AttackPattern::PatternBulletUp;
		}
		else
		{
			mAttackCount = 0;
			mPattern = AttackPattern::PatternBulletTarget;
			mIsDown = true;
		}
	}

	Pattern();

	mCurrentAnimation->Update();		// 머리 애니메이션
	MotionFrame();

	vector<BossBullet*>::iterator iter = mVecBullet.begin();
	for (; iter != mVecBullet.end(); )
	{
		if (!(*iter)->GetIsActive())
		{
			(*iter)->SetIsActive(false);
			iter = mVecBullet.erase(iter);
		}
		else
			iter++;
	}

	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	mHitBox = mChest.rc;
}

void Boss::Render(HDC hdc)
{
#ifdef DEBUG
	CAMERAMANAGER->GetMainCamera()->RenderRectInCamera(hdc, mBackHair.rc);
	CAMERAMANAGER->GetMainCamera()->RenderRectInCamera(hdc, mLeftArm.rc);
	CAMERAMANAGER->GetMainCamera()->RenderRectInCamera(hdc, mRightArm.rc);
	CAMERAMANAGER->GetMainCamera()->RenderRectInCamera(hdc, mBody.rc);
	CAMERAMANAGER->GetMainCamera()->RenderRectInCamera(hdc, mHead.rc);
	CAMERAMANAGER->GetMainCamera()->RenderRectInCamera(hdc, mChest.rc);

	if (!mIsCloseEyes)
	{
		CAMERAMANAGER->GetMainCamera()->RenderRectInCamera(hdc, mEyes.rc);
		CAMERAMANAGER->GetMainCamera()->RenderRectInCamera(hdc, mPupil.rc);
	}
#endif // DEBUG

	if (!mIsEndEvent)
	{
		CAMERAMANAGER->GetMainCamera()->ScaleRender(hdc, mBackHair.image, mBackHair.rc.left, mBackHair.rc.top, mBackHair.sizeX, mBackHair.sizeY);
		CAMERAMANAGER->GetMainCamera()->ScaleRender(hdc, mLeftArm.image, mLeftArm.rc.left, mLeftArm.rc.top, mLeftArm.sizeX, mLeftArm.sizeY);
		CAMERAMANAGER->GetMainCamera()->ScaleRender(hdc, mRightArm.image, mRightArm.rc.left, mRightArm.rc.top, mRightArm.sizeX, mRightArm.sizeY);
		CAMERAMANAGER->GetMainCamera()->ScaleRender(hdc, mBody.image, mBody.rc.left, mBody.rc.top, mBody.sizeX, mBody.sizeY);
		CAMERAMANAGER->GetMainCamera()->ScaleFrameRender(hdc, mHead.image, mHead.rc.left, mHead.rc.top, mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY(), mHead.sizeX, mHead.sizeY);
		CAMERAMANAGER->GetMainCamera()->ScaleRender(hdc, mChest.image, mChest.rc.left, mChest.rc.top, mChest.sizeX, mChest.sizeY);

		if (!mIsCloseEyes)
		{
			CAMERAMANAGER->GetMainCamera()->ScaleRender(hdc, mEyes.image, mEyes.rc.left, mEyes.rc.top, mEyes.sizeX, mEyes.sizeY);
			CAMERAMANAGER->GetMainCamera()->ScaleRender(hdc, mPupil.image, mPupil.rc.left, mPupil.rc.top, mPupil.sizeX, mPupil.sizeY);
		}
	}
	else
	{
		CAMERAMANAGER->GetMainCamera()->ScaleRender(hdc, mBackImage, mRect.left, mRect.top, mSizeX, mSizeY);
		CAMERAMANAGER->GetMainCamera()->ScaleRender(hdc, mImage, mRect.left, mRect.top, mSizeX, mSizeY);
	}
}

void Boss::ImageSetting()
{
	// 몸통
	mBody.image = IMAGEMANAGER->FindImage(L"Boss_Body");
	mBody.sizeX = mBody.image->GetWidth() * 3;
	mBody.sizeY = mBody.image->GetHeight() * 3;
	mBody.x = 47 * 3 + mBody.sizeX / 2;
	mBody.y = 144 * 3 + mBody.sizeY / 2;
	mBody.rc = RectMakeCenter(mX - mSizeX / 2 + mBody.x, mY - mSizeY / 2 + mBody.y, mBody.sizeX, mBody.sizeY);
	mBody.move = true;
	mBody.moveTime = 0.f;
	mBody.moveCount = 0;

	// 뒷머리
	mBackHair.image = IMAGEMANAGER->FindImage(L"Boss_BackHair");
	mBackHair.sizeX = mBackHair.image->GetWidth() * 3;
	mBackHair.sizeY = mBackHair.image->GetHeight() * 3;
	mBackHair.x = 7 * 3 + mBackHair.sizeX / 2;
	mBackHair.y = 60 * 3 + mBackHair.sizeY / 2;;
	mBackHair.rc = RectMakeCenter(mX - mSizeX / 2 + mBackHair.x, mY - mSizeY / 2 + mBackHair.y, mBackHair.sizeX, mBackHair.sizeY);
	mBackHair.move = true;
	mBackHair.moveTime = 0.f;
	mBackHair.moveCount = 0;

	// 머리
	mHead.image = IMAGEMANAGER->FindImage(L"Boss_Head");
	mHead.sizeX = mHead.image->GetWidth() * 3 / 5;
	mHead.sizeY = mHead.image->GetHeight() * 3;
	mHead.x = 5 * 3 + mHead.sizeX / 2;
	mHead.y = 5 * 3 + mHead.sizeY / 2;
	mHead.rc = RectMakeCenter(mX - mSizeX / 2 + mHead.x, mY - mSizeY / 2 + mHead.y, mHead.sizeX, mHead.sizeY);
	mHead.move = true;
	mHead.moveTime = 0.f;
	mHead.moveCount = 0;

	// 가슴
	mChest.image = IMAGEMANAGER->FindImage(L"Boss_Chest");
	mChest.sizeX = mChest.image->GetWidth() * 3;
	mChest.sizeY = mChest.image->GetHeight() * 3;
	mChest.x = 54 * 3 + mChest.sizeX / 2;
	mChest.y = 194 * 3 + mChest.sizeY / 2;
	mChest.rc = RectMakeCenter(mX - mSizeX / 2 + mChest.x, mY - mSizeY / 2 + mChest.y, mChest.sizeX, mChest.sizeY);
	mChest.move = true;
	mChest.moveTime = 0.f;
	mChest.moveCount = 0;

	// 눈알
	mEyes.image = IMAGEMANAGER->FindImage(L"Boss_Eyes");
	mEyes.sizeX = mEyes.image->GetWidth() * 3;
	mEyes.sizeY = mEyes.image->GetHeight() * 3;
	mEyes.x = 74 * 3 + mEyes.sizeX / 2;
	mEyes.y = 112 * 3 + mEyes.sizeY / 2;
	mEyes.rc = RectMakeCenter(mX - mSizeX / 2 + mEyes.x, mY - mSizeY / 2 + mEyes.y, mEyes.sizeX, mEyes.sizeY);
	mEyes.move = true;
	mEyes.moveTime = 0.f;
	mEyes.moveCount = 0;

	// 눈동자
	mPupil.image = IMAGEMANAGER->FindImage(L"Boss_Pupil");
	mPupil.sizeX = mPupil.image->GetWidth() * 3;
	mPupil.sizeY = mPupil.image->GetHeight() * 3;
	mPupil.x = 80 * 3 + mPupil.sizeX / 2;
	mPupil.y = 114 * 3 + mPupil.sizeY / 2;
	mPupil.rc = RectMakeCenter(mX - mSizeX / 2 + mPupil.x, mY - mSizeY / 2 + mPupil.y, mPupil.sizeX, mPupil.sizeY);
	mPupil.move = true;
	mPupil.moveTime = 0.f;
	mPupil.moveCount = 0;

	// 왼팔
	mLeftArm.image = IMAGEMANAGER->FindImage(L"Boss_LeftArm");
	mLeftArm.sizeX = mLeftArm.image->GetWidth() * 3;
	mLeftArm.sizeY = mLeftArm.image->GetHeight() * 3;
	mLeftArm.x = 45 * 3 + mLeftArm.sizeX / 2;
	mLeftArm.y = 175 * 3 + mLeftArm.sizeY / 2;
	mLeftArm.rc = RectMakeCenter(mX - mSizeX / 2 + mLeftArm.x, mY - mSizeY / 2 + mLeftArm.y, mLeftArm.sizeX, mLeftArm.sizeY);
	mLeftArm.move = true;
	mLeftArm.moveTime = 0.f;
	mLeftArm.moveCount = 0;

	// 오른팔
	mRightArm.image = IMAGEMANAGER->FindImage(L"Boss_RightArm");
	mRightArm.sizeX = mRightArm.image->GetWidth() * 3;
	mRightArm.sizeY = mRightArm.image->GetHeight() * 3;
	mRightArm.x = 123 * 3 + mRightArm.sizeX / 2;
	mRightArm.y = 175 * 3 + mRightArm.sizeY / 2;
	mRightArm.rc = RectMakeCenter(mX - mSizeX / 2 + mRightArm.x, mY - mSizeY / 2 + mRightArm.y, mRightArm.sizeX, mRightArm.sizeY);
	mRightArm.move = true;
	mRightArm.moveTime = 0.f;
	mRightArm.moveCount = 0;
}

void Boss::MotionFrame()
{
	// 몸은 움직이지 않음
	mBody.rc = RectMakeCenter(mX - mSizeX / 2 + mBody.x, mY - mSizeY / 2 + mBody.y, mBody.sizeX, mBody.sizeY);

	// 머리, 눈
	if (mHead.move)		// true일 때 내려오는 모션
	{
		mHead.moveTime += TIME->DeltaTime();

		if (mHead.moveCount < 3)
		{
			if (mHead.moveTime >= 0.3f)
			{
				mHead.y -= 1;
				mBackHair.y -= 1;
				mEyes.y -= 1;
				mPupil.y -= 1;
				mHead.moveTime = 0.f;
				mHead.moveCount++;
			}
		}
		else
		{
			if (mHead.moveTime >= 0.5f)
			{
				mHead.move = false;
				mHead.moveTime = 0.f;
				mHead.moveCount = 0;
			}
		}
	}
	else
	{
		mHead.moveTime += TIME->DeltaTime();

		if (mHead.moveCount < 3)
		{
			if (mHead.moveTime >= 0.3f)
			{
				mHead.y += 1;
				mBackHair.y += 1;
				mEyes.y += 1;
				mPupil.y += 1;
				mHead.moveTime = 0.f;
				mHead.moveCount++;
			}
		}
		else
		{
			if (mHead.moveTime >= 0.5f)
			{
				mHead.move = true;
				mHead.moveTime = 0.f;
				mHead.moveCount = 0;
			}
		}
	}

	mCloseEyesTime += TIME->DeltaTime();
	if (mCloseEyesTime >= 2.f && mCloseEyesTime < 2.1f)	// 눈 감는 시간 테스트
		mIsCloseEyes = true;
	else if (mCloseEyesTime >= 2.1f)
	{
		mCloseEyesTime = 0.f;
		mIsCloseEyes = false;
	}

	mHead.rc = RectMakeCenter(mX - mSizeX / 2 + mHead.x, mY - mSizeY / 2 + mHead.y, mHead.sizeX, mHead.sizeY);
	mBackHair.rc = RectMakeCenter(mX - mSizeX / 2 + mBackHair.x, mY - mSizeY / 2 + mBackHair.y, mBackHair.sizeX, mBackHair.sizeY);
	mEyes.rc = RectMakeCenter(mX - mSizeX / 2 + mEyes.x, mY - mSizeY / 2 + mEyes.y, mEyes.sizeX, mEyes.sizeY);
	mPupil.rc = RectMakeCenter(mX - mSizeX / 2 + mPupil.x, mY - mSizeY / 2 + mPupil.y, mPupil.sizeX, mPupil.sizeY);

	// 가슴
	if (mChest.move)		// true일 때 내려오는 모션
	{
		mChest.moveTime += TIME->DeltaTime();

		if (mChest.moveCount < 2)
		{
			if (mChest.moveTime >= 0.3f)
			{
				mChest.y -= 2;
				mChest.moveTime = 0.f;
				mChest.moveCount++;
			}
		}
		else
		{
			if (mChest.moveTime >= 0.5f)
			{
				mChest.move = false;
				mChest.moveTime = 0.f;
				mChest.moveCount = 0;
			}
		}
	}
	else
	{
		mChest.moveTime += TIME->DeltaTime();

		if (mChest.moveCount < 2)
		{
			if (mChest.moveTime >= 0.3f)
			{
				mChest.y += 2;
				mChest.moveTime = 0.f;
				mChest.moveCount++;
			}
		}
		else
		{
			if (mChest.moveTime >= 1.f)
			{
				mChest.move = true;
				mChest.moveTime = 0.f;
				mChest.moveCount = 0;
			}
		}
	}

	if (mIsHit)		// 피격 순간
	{
		mIsHit = false;
		mIsInvincibility = true;

		if (!mIsMoveChest)
		{
			mIsMoveChest = true;
			mChest.y -= 10;
		}
	}

	if (mIsInvincibility)	// 피격 후 무적 시간
	{
		mHitFrameTime += TIME->DeltaTime();

		if (mHitFrameTime >= 0.2f)
		{
			if (mIsMoveChest)
			{
				mHitMoveCount++;
				mHitFrameTime = 0.f;
				mChest.y += 5;
			}

			if (mHitMoveCount >= 2)
			{
				mIsInvincibility = false;
				mHitMoveCount = 0;
				mIsMoveChest = false;
			}
		}
	}

	mChest.rc = RectMakeCenter(mX - mSizeX / 2 + mChest.x, mY - mSizeY / 2 + mChest.y, mChest.sizeX, mChest.sizeY);

	// 팔
	if (mLeftArm.move)		// true일 때 내려오는 모션
	{
		mLeftArm.moveTime += TIME->DeltaTime();

		if (mLeftArm.moveCount < 2)
		{
			if (mLeftArm.moveTime >= 0.3f)
			{
				mLeftArm.y -= 2;
				mRightArm.y -= 2;
				mLeftArm.moveTime = 0.f;
				mLeftArm.moveCount++;
			}
		}
		else
		{
			if (mLeftArm.moveTime >= 0.5f)
			{
				mLeftArm.move = false;
				mLeftArm.moveTime = 0.f;
				mLeftArm.moveCount = 0;
			}
		}
	}
	else
	{
		mLeftArm.moveTime += TIME->DeltaTime();

		if (mLeftArm.moveCount < 2)
		{
			if (mLeftArm.moveTime >= 0.3f)
			{
				mLeftArm.y += 2;
				mRightArm.y += 2;
				mLeftArm.moveTime = 0.f;
				mLeftArm.moveCount++;
			}
		}
		else
		{
			if (mLeftArm.moveTime >= 1.f)
			{
				mLeftArm.move = true;
				mLeftArm.moveTime = 0.f;
				mLeftArm.moveCount = 0;
			}
		}
	}

	mLeftArm.rc = RectMakeCenter(mX - mSizeX / 2 + mLeftArm.x, mY - mSizeY / 2 + mLeftArm.y, mLeftArm.sizeX, mLeftArm.sizeY);
	mRightArm.rc = RectMakeCenter(mX - mSizeX / 2 + mRightArm.x, mY - mSizeY / 2 + mRightArm.y, mRightArm.sizeX, mRightArm.sizeY);
}

void Boss::Pattern()
{
	switch (mPattern)
	{
	case AttackPattern::PatternIdle:
		break;
	case AttackPattern::PatternBulletDown:
		mBulletCreateTime += TIME->DeltaTime();
		if (mBulletCreateTime >= 0.1f)				// 일정 시간마다 bullet 생성
		{
			for (int i = mBulletCreateCount; i < 4; )
			{
				mBulletCreateCount++;
				mBulletCreateTime = 0.f;

				BossBullet* bullet = new BossBullet;
				bullet->Init();
				bullet->SetX(WINSIZEX / 5 * (i + 1));
				bullet->SetY(1000.f);
				bullet->SetAngle(PI * 1.5f);		// 그냥 아래로 떨어지게
				bullet->SetPattern(BulletPattern::PatternBulletDown);
				bullet->SetObject();
				mVecBullet.push_back(bullet);
				OBJECTMANAGER->AddObject(ObjectLayer::BossBullet, bullet);

				if (mBulletCreateCount == 4)
				{
					mBulletCreateCount = 0;
					mBulletCreateTime = 0.f;
					mPattern = AttackPattern::PatternIdle;
				}
				break;
			}
		}
		break;
	case AttackPattern::PatternBulletUp:
		mBulletCreateTime += TIME->DeltaTime();
		if (mBulletCreateTime >= 0.2f)				// 일정 시간마다 bullet 생성
		{
			for (int i = mBulletCreateCount; i < 2; )
			{
				mBulletCreateCount++;
				mBulletCreateTime = 0.f;

				float angle = rand() % 30 / 10.f;
				BossBullet* bullet = new BossBullet;
				bullet->Init();
				bullet->SetX(OBJECTMANAGER->GetPlayer()->GetX());
				bullet->SetY(1490.f);
				bullet->SetAngle(angle);
				bullet->SetPattern(BulletPattern::PatternBulletUp);
				bullet->SetObject();
				mVecBullet.push_back(bullet);
				OBJECTMANAGER->AddObject(ObjectLayer::BossBullet, bullet);

				if (mBulletCreateCount == 2)
				{
					mBulletCreateCount = 0;
					mBulletCreateTime = 0.f;
					mPattern = AttackPattern::PatternIdle;
				}
				break;
			}
		}
		break;
	case AttackPattern::PatternBulletTarget:
		if (mIsDown)
		{
			if (mY - mSizeY / 2 < 1600)
			{
				if (!mIsDownSound)
				{
					mIsDownSound = true;
					SOUNDMANAGER->Play(L"Dive", 0.1f);
				}

				mY -= mJumpPower;
				mJumpPower -= 1.f;
			}
			else
			{
				mIsDownSound = false;

				int n = rand() % 3;
				if (n == 0)
					mX = WINSIZEX / 4;
				if (n == 1)
					mX = WINSIZEX / 4 * 2;
				if (n == 2)
					mX = WINSIZEX / 4 * 3;

				for (int i = mBulletCreateCount; i < 8; ++i)
				{
					mBulletCreateCount++;

					BossBullet* bullet = new BossBullet;

					if (i % 2 == 0)		// 왼쪽서 생성하는 애들
					{
						bullet->Init();
						bullet->SetX(-(bullet->GetSizeX()) * (i / 2 + i / 2));
						bullet->SetY(1000.f);
						bullet->SetAngle(0.f);
						bullet->SetPattern(BulletPattern::PatternBulletTarget);
						bullet->SetObject();
					}
					else				// 오른쪽서 생성하는 애들
					{
						bullet->Init();
						bullet->SetX(WINSIZEX + (bullet->GetSizeX()) * (i / 2 + i / 2));
						bullet->SetY(1000.f + bullet->GetSizeY() / 2);
						bullet->SetAngle(PI);
						bullet->SetPattern(BulletPattern::PatternBulletTarget);
						bullet->SetObject();
					}
					mVecBullet.push_back(bullet);
					OBJECTMANAGER->AddObject(ObjectLayer::BossBullet, bullet);
				}

				if (mVecBullet.size() == 0)
				{
					mIsDown = false;
				}
			}
		}
		else
		{
			mY += mJumpPower;
			mJumpPower += 1.f;

			if (mY <= 1600 - mSizeY / 3 - 50)
			{
				mY = 1600 - mSizeY / 3 - 50;
				mJumpPower = 15.f;
				mBulletCreateCount = 0;
				mPattern = AttackPattern::PatternIdle;
			}
		}
		break;
	}
}

void Boss::Hit()
{
	if (!mIsInvincibility)
	{
		mIsHit = true;
		//mHp -= 30;
	}
}

void Boss::EraseBossImage()
{
	//for (int i = 0; i < mVecEraseCenter.size(); ++i)
	//{
	//	float speed = (rand() % 9 + 1) / 10.f;
	//	mVecEraseCenter[i].x += cosf(30.f * PI / 180.f) * speed * 2;
	//	mVecEraseCenter[i].y += -sinf(30.f * PI / 180.f) * speed * 2;

	//	HBRUSH brush = CreateSolidBrush(RGB(255, 0, 255));
	//	HPEN pen = CreatePen(PS_SOLID, 1, RGB(255, 0, 255));

	//	if (mVecEraseCenter[i].x >= 0 && mVecEraseCenter[i].x <= WINSIZEX && mVecEraseCenter[i].y <= WINSIZEY && mVecEraseCenter[i].y >= 0)
	//	{
	//		HBRUSH oldBrush = (HBRUSH)SelectObject(mImage->GetHDC(), brush);
	//		HPEN oldPen = (HPEN)SelectObject(mImage->GetHDC(), pen);

	//		COLORREF pixelColor = GetPixel(mImage->GetHDC(), mVecEraseCenter[i].x, mVecEraseCenter[i].y);

	//		RenderEllipse(mImage->GetHDC(), mVecEraseCenter[i].x, mVecEraseCenter[i].y, mEraseSize * 3);

	//		SelectObject(mImage->GetHDC(), oldPen);
	//		SelectObject(mImage->GetHDC(), oldBrush);
	//	}
	//	
	//	if (mEraseTime >= 0.1f)
	//	{
	//		float speed = (rand() % 9 + 1) / 10.f;
	//		mVecBackEraseCenter[i].x += cosf(30.f * PI / 180.f) * speed * 2;
	//		mVecBackEraseCenter[i].y += -sinf(30.f * PI / 180.f) * speed * 2;

	//		if (mVecBackEraseCenter[i].x >= 0 && mVecBackEraseCenter[i].x <= WINSIZEX && mVecBackEraseCenter[i].y <= WINSIZEY && mVecBackEraseCenter[i].y >= 0)
	//		{
	//			HBRUSH oldBrush = (HBRUSH)SelectObject(mBackImage->GetHDC(), brush);
	//			HPEN oldPen = (HPEN)SelectObject(mBackImage->GetHDC(), pen);

	//			COLORREF pixelColor = GetPixel(mBackImage->GetHDC(), mVecBackEraseCenter[i].x, mVecBackEraseCenter[i].y);

	//			RenderEllipse(mBackImage->GetHDC(), mVecBackEraseCenter[i].x, mVecBackEraseCenter[i].y, mEraseSize * 3);

	//			SelectObject(mBackImage->GetHDC(), oldPen);
	//			SelectObject(mBackImage->GetHDC(), oldBrush);
	//		}
	//	}

	//	/*// 몸통
	//	HBRUSH oldBrush = (HBRUSH)SelectObject(mBody.image->GetHDC(), brush);
	//	HPEN oldPen = (HPEN)SelectObject(mBody.image->GetHDC(), pen);

	//	COLORREF pixelColor = GetPixel(mBody.image->GetHDC(), mVecEraseCenter[i].x, mVecEraseCenter[i].y);

	//	RenderEllipse(mBody.image->GetHDC(), mVecEraseCenter[i].x, mVecEraseCenter[i].y, mEraseSize * 5);

	//	SelectObject(mBody.image->GetHDC(), oldPen);
	//	SelectObject(mBody.image->GetHDC(), oldBrush);

	//	// 뒷머리
	//	oldBrush = (HBRUSH)SelectObject(mBackHair.image->GetHDC(), brush);
	//	oldPen = (HPEN)SelectObject(mBackHair.image->GetHDC(), pen);

	//	pixelColor = GetPixel(mBackHair.image->GetHDC(), mVecEraseCenter[i].x, mVecEraseCenter[i].y);

	//	RenderEllipse(mBackHair.image->GetHDC(), mVecEraseCenter[i].x, mVecEraseCenter[i].y, mEraseSize * 5);

	//	SelectObject(mBackHair.image->GetHDC(), oldPen);
	//	SelectObject(mBackHair.image->GetHDC(), oldBrush);

	//	// 머리는 프레임 봐야하는데
	//	oldBrush = (HBRUSH)SelectObject(mHead.image->GetHDC(), brush);
	//	oldPen = (HPEN)SelectObject(mHead.image->GetHDC(), pen);

	//	pixelColor = GetPixel(mHead.image->GetHDC(), mVecEraseCenter[i].x, mVecEraseCenter[i].y);
	//	
	//	RenderEllipse(mHead.image->GetHDC(), mVecEraseCenter[i].x, mVecEraseCenter[i].y, mEraseSize * 5);

	//	SelectObject(mHead.image->GetHDC(), oldPen);
	//	SelectObject(mHead.image->GetHDC(), oldBrush);

	//	// 가슴
	//	oldBrush = (HBRUSH)SelectObject(mChest.image->GetHDC(), brush);
	//	oldPen = (HPEN)SelectObject(mChest.image->GetHDC(), pen);

	//	pixelColor = GetPixel(mChest.image->GetHDC(), mVecEraseCenter[i].x, mVecEraseCenter[i].y);

	//	RenderEllipse(mChest.image->GetHDC(), mVecEraseCenter[i].x, mVecEraseCenter[i].y, mEraseSize * 5);

	//	SelectObject(mChest.image->GetHDC(), oldPen);
	//	SelectObject(mChest.image->GetHDC(), oldBrush);


	//	// 눈알
	//	oldBrush = (HBRUSH)SelectObject(mEyes.image->GetHDC(), brush);
	//	oldPen = (HPEN)SelectObject(mEyes.image->GetHDC(), pen);

	//	pixelColor = GetPixel(mEyes.image->GetHDC(), mVecEraseCenter[i].x, mVecEraseCenter[i].y);

	//	RenderEllipse(mEyes.image->GetHDC(), mVecEraseCenter[i].x, mVecEraseCenter[i].y, mEraseSize * 5);
	//	
	//	SelectObject(mEyes.image->GetHDC(), oldPen);
	//	SelectObject(mEyes.image->GetHDC(), oldBrush);

	//	oldBrush = (HBRUSH)SelectObject(mPupil.image->GetHDC(), brush);
	//	oldPen = (HPEN)SelectObject(mPupil.image->GetHDC(), pen);

	//	pixelColor = GetPixel(mPupil.image->GetHDC(), mVecEraseCenter[i].x, mVecEraseCenter[i].y);

	//	RenderEllipse(mPupil.image->GetHDC(), mVecEraseCenter[i].x, mVecEraseCenter[i].y, mEraseSize * 5);

	//	SelectObject(mPupil.image->GetHDC(), oldPen);
	//	SelectObject(mPupil.image->GetHDC(), oldBrush);

	//	// 왼팔
	//	oldBrush = (HBRUSH)SelectObject(mLeftArm.image->GetHDC(), brush);
	//	oldPen = (HPEN)SelectObject(mLeftArm.image->GetHDC(), pen);

	//	pixelColor = GetPixel(mLeftArm.image->GetHDC(), mVecEraseCenter[i].x, mVecEraseCenter[i].y);

	//	RenderEllipse(mLeftArm.image->GetHDC(), mVecEraseCenter[i].x, mVecEraseCenter[i].y, mEraseSize * 5);

	//	SelectObject(mLeftArm.image->GetHDC(), oldPen);
	//	SelectObject(mLeftArm.image->GetHDC(), oldBrush);

	//	// 오른팔
	//	oldBrush = (HBRUSH)SelectObject(mRightArm.image->GetHDC(), brush);
	//	oldPen = (HPEN)SelectObject(mRightArm.image->GetHDC(), pen);

	//	pixelColor = GetPixel(mRightArm.image->GetHDC(), mVecEraseCenter[i].x, mVecEraseCenter[i].y);

	//	RenderEllipse(mRightArm.image->GetHDC(), mVecEraseCenter[i].x, mVecEraseCenter[i].y, mEraseSize * 5);

	//	SelectObject(mRightArm.image->GetHDC(), oldPen);
	//	SelectObject(mRightArm.image->GetHDC(), oldBrush);*/

	//	DeleteObject(pen);
	//	DeleteObject(brush);
	//}
}
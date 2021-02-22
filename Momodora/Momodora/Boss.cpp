#include "pch.h"
#include "Boss.h"

#include "Image.h"
#include "Camera.h"

void Boss::Init()
{
	// 보스의 위치는 Body가 기준이지만 Rect는 가슴으로 정한다
	mName = "Boss";
	mX = 0;// WINSIZEX / 2;
	mY = 0;// WINSIZEY / 2;
	mSizeX = IMAGEMANAGER->FindImage(L"Boss_Chest")->GetWidth();
	mSizeY = IMAGEMANAGER->FindImage(L"Boss_Chest")->GetHeight();

	ImageSetting();

	mRect = mChest.rc;

	mFrameX = 0;
	mFrameTime = 0.f;

	mIsHit = false;
	mIsInvincibility = false;
	mHitMoveCount = 0;
	mHitFrameTime = 0.f;
}

void Boss::Release()
{
}

void Boss::Update()
{
	if (INPUT->GetKeyDown(VK_SPACE))
	{
		if(!mIsInvincibility)
			mIsHit = true;
	}

	MotionFrame();

	mFrameTime += TIME->DeltaTime();
	if (mFrameTime >= 0.2f)
	{
		mFrameTime = 0.f;
		mFrameX++;

		if (mFrameX >= 5)
			mFrameX = 0;
	}
}

void Boss::Render(HDC hdc)
{
#ifdef DEBUG
	RenderRect(hdc, mBackHair.rc);
	RenderRect(hdc, mLeftArm.rc);
	RenderRect(hdc, mRightArm.rc);
	RenderRect(hdc, mBody.rc);
	RenderRect(hdc, mHead.rc);
	RenderRect(hdc, mChest.rc);
	RenderRect(hdc, mEyes.rc);
	RenderRect(hdc, mPupil.rc);

#endif // DEBUG


	CAMERAMANAGER->GetMainCamera()->ScaleRender(hdc, mBackHair.image, mBackHair.rc.left, mBackHair.rc.top, mBackHair.sizeX, mBackHair.sizeY);
	CAMERAMANAGER->GetMainCamera()->ScaleRender(hdc, mLeftArm.image, mLeftArm.rc.left, mLeftArm.rc.top, mLeftArm.sizeX, mLeftArm.sizeY);
	CAMERAMANAGER->GetMainCamera()->ScaleRender(hdc, mRightArm.image, mRightArm.rc.left, mRightArm.rc.top, mRightArm.sizeX, mRightArm.sizeY);
	CAMERAMANAGER->GetMainCamera()->ScaleRender(hdc, mBody.image, mBody.rc.left, mBody.rc.top, mBody.sizeX, mBody.sizeY);
	CAMERAMANAGER->GetMainCamera()->ScaleFrameRender(hdc, mHead.image, mHead.rc.left, mHead.rc.top, mFrameX, 0, mHead.sizeX, mHead.sizeY);
	CAMERAMANAGER->GetMainCamera()->ScaleRender(hdc, mChest.image, mChest.rc.left, mChest.rc.top, mChest.sizeX, mChest.sizeY);
	CAMERAMANAGER->GetMainCamera()->ScaleRender(hdc, mEyes.image, mEyes.rc.left, mEyes.rc.top, mEyes.sizeX, mEyes.sizeY);
	CAMERAMANAGER->GetMainCamera()->ScaleRender(hdc, mPupil.image, mPupil.rc.left, mPupil.rc.top, mPupil.sizeX, mPupil.sizeY);
}

void Boss::ImageSetting()
{
	// 몸통
	mBody.image = IMAGEMANAGER->FindImage(L"Boss_Body");
	mBody.x = 47 * 2;
	mBody.y = 144 * 2;
	mBody.sizeX = mBody.image->GetWidth() * 2;
	mBody.sizeY = mBody.image->GetHeight() * 2;
	mBody.rc = RectMakeCenter(mX - mSizeX / 2 + mBody.x + mBody.sizeX / 2, mY - mSizeY / 2 + mBody.y + mBody.sizeY / 2, mBody.sizeX, mBody.sizeY);
	mBody.move = true;
	mBody.moveTime = 0.f;
	mBody.moveCount = 0;

	// 뒷머리
	mBackHair.image = IMAGEMANAGER->FindImage(L"Boss_BackHair");
	mBackHair.x = 7 * 2;
	mBackHair.y = 60 * 2;
	mBackHair.sizeX = mBackHair.image->GetWidth() * 2;
	mBackHair.sizeY = mBackHair.image->GetHeight() * 2;
	mBackHair.rc = RectMakeCenter(mX - mSizeX / 2 + mBackHair.x + mBackHair.sizeX / 2, mY - mSizeY / 2 + mBackHair.y + mBackHair.sizeY / 2, mBackHair.sizeX, mBackHair.sizeY);
	mBackHair.move = true;
	mBackHair.moveTime = 0.f;
	mBackHair.moveCount = 0;

	// 머리
	mHead.image = IMAGEMANAGER->FindImage(L"Boss_Head");
	mHead.x = 5 * 2;
	mHead.y = 5 * 2;
	mHead.sizeX = mHead.image->GetWidth() * 2 / 5;
	mHead.sizeY = mHead.image->GetHeight() * 2;
	mHead.rc = RectMakeCenter(mX - mSizeX / 2 + mHead.x + mHead.sizeX / 2, mY - mSizeY / 2 + mHead.y + mHead.sizeY / 2, mHead.sizeX, mHead.sizeY);
	mHead.move = true;
	mHead.moveTime = 0.f;
	mHead.moveCount = 0;

	// 가슴
	mChest.image = IMAGEMANAGER->FindImage(L"Boss_Chest");
	mChest.x = 54 * 2;
	mChest.y = 194 * 2;
	mChest.sizeX = mChest.image->GetWidth() * 2;
	mChest.sizeY = mChest.image->GetHeight() * 2;
	mChest.rc = RectMakeCenter(mX - mSizeX / 2 + mChest.x + mChest.sizeX / 2, mY - mSizeY / 2 + mChest.y + mChest.sizeY / 2, mChest.sizeX, mChest.sizeY);
	mChest.move = true;
	mChest.moveTime = 0.f;
	mChest.moveCount = 0;

	// 눈알
	mEyes.image = IMAGEMANAGER->FindImage(L"Boss_Eyes");
	mEyes.x = 74 * 2;
	mEyes.y = 112 * 2;
	mEyes.sizeX = mEyes.image->GetWidth() * 2;
	mEyes.sizeY = mEyes.image->GetHeight() * 2;
	mEyes.rc = RectMakeCenter(mX - mSizeX / 2 + mEyes.x + mEyes.sizeX / 2, mY - mSizeY / 2 + mEyes.y + mEyes.sizeY / 2, mEyes.sizeX, mEyes.sizeY);
	mEyes.move = true;
	mEyes.moveTime = 0.f;
	mEyes.moveCount = 0;
	
	// 눈동자
	mPupil.image = IMAGEMANAGER->FindImage(L"Boss_Pupil");
	mPupil.x = 80 * 2;
	mPupil.y = 114 * 2;
	mPupil.sizeX = mPupil.image->GetWidth() * 2;
	mPupil.sizeY = mPupil.image->GetHeight() * 2;
	mPupil.rc = RectMakeCenter(mX - mSizeX / 2 + mPupil.x + mPupil.sizeX / 2, mY - mSizeY / 2 + mPupil.y + mPupil.sizeY / 2, mPupil.sizeX, mPupil.sizeY);
	mPupil.move = true;
	mPupil.moveTime = 0.f;
	mPupil.moveCount = 0;

	// 왼팔
	mLeftArm.image = IMAGEMANAGER->FindImage(L"Boss_LeftArm");
	mLeftArm.x = 45 * 2;
	mLeftArm.y = 175 * 2;
	mLeftArm.sizeX = mLeftArm.image->GetWidth() * 2;
	mLeftArm.sizeY = mLeftArm.image->GetHeight() * 2;
	mLeftArm.rc = RectMakeCenter(mX - mSizeX / 2 + mLeftArm.x + mLeftArm.sizeX / 2, mY - mSizeY / 2 + mLeftArm.y + mLeftArm.sizeY / 2, mLeftArm.sizeX, mLeftArm.sizeY);
	mLeftArm.move = true;
	mLeftArm.moveTime = 0.f;
	mLeftArm.moveCount = 0;

	// 오른팔
	mRightArm.image = IMAGEMANAGER->FindImage(L"Boss_RightArm");
	mRightArm.x = 123 * 2;
	mRightArm.y = 175 * 2;
	mRightArm.sizeX = mRightArm.image->GetWidth() * 2;
	mRightArm.sizeY = mRightArm.image->GetHeight() * 2;
	mRightArm.rc = RectMakeCenter(mX - mSizeX / 2 + mRightArm.x + mRightArm.sizeX / 2, mY - mSizeY / 2 + mRightArm.y + mRightArm.sizeY / 2, mRightArm.sizeX, mRightArm.sizeY);
	mRightArm.move = true;
	mRightArm.moveTime = 0.f;
	mRightArm.moveCount = 0;
}

void Boss::MotionFrame()
{
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

	mHead.rc = RectMakeCenter(mX - mSizeX / 2 + mHead.x + mHead.sizeX / 2
		, mY - mSizeY / 2 + mHead.y + mHead.sizeY / 2, mHead.sizeX, mHead.sizeY);
	mBackHair.rc = RectMakeCenter(mX - mSizeX / 2 + mBackHair.x + mBackHair.sizeX / 2
		, mY - mSizeY / 2 + mBackHair.y + mBackHair.sizeY / 2, mBackHair.sizeX, mBackHair.sizeY);
	mEyes.rc = RectMakeCenter(mX - mSizeX / 2 + mEyes.x + mEyes.sizeX / 2
		, mY - mSizeY / 2 + mEyes.y + mEyes.sizeY / 2, mEyes.sizeX, mEyes.sizeY);
	mPupil.rc = RectMakeCenter(mX - mSizeX / 2 + mPupil.x + mPupil.sizeX / 2
		, mY - mSizeY / 2 + mPupil.y + mPupil.sizeY / 2, mPupil.sizeX, mPupil.sizeY);

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
			if (mChest.moveTime >= 1.1f)
			{
				mChest.move = true;
				mChest.moveTime = 0.f;
				mChest.moveCount = 0;
			}
		}
	}

	if (mIsHit)		// 피격 순간
	{
		mChest.y -= 4;
		mIsHit = false;
		mIsInvincibility = true;
	}
	
	if (mIsInvincibility)	// 피격 후 무적 시간
	{
		mHitFrameTime += TIME->DeltaTime();

		if (mHitFrameTime >= 0.3f)
		{
			mHitMoveCount++;
			mHitFrameTime = 0.f;
			mChest.y += 2;

			if (mHitMoveCount >= 2)
			{
				mIsInvincibility = false;
				mHitMoveCount = 0;
			}
		}
	}

	mChest.rc = RectMakeCenter(mX - mSizeX / 2 + mChest.x + mChest.sizeX / 2
		, mY - mSizeY / 2 + mChest.y + mChest.sizeY / 2, mChest.sizeX, mChest.sizeY);

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

	mLeftArm.rc = RectMakeCenter(mX - mSizeX / 2 + mLeftArm.x + mLeftArm.sizeX / 2
		, mY - mSizeY / 2 + mLeftArm.y + mLeftArm.sizeY / 2, mLeftArm.sizeX, mLeftArm.sizeY);
	mRightArm.rc = RectMakeCenter(mX - mSizeX / 2 + mRightArm.x + mRightArm.sizeX / 2
		, mY - mSizeY / 2 + mRightArm.y + mRightArm.sizeY / 2, mRightArm.sizeX, mRightArm.sizeY);
}

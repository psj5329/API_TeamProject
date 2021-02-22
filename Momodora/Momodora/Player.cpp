#include "pch.h"
#include "Player.h"
#include "Image.h"


void Player::Init()
{
	mState = State::Right;
	mCurrentAnimation = mRightIdleAnimation;
	mSizeX = (float)(mIdleImage->GetFrameWidth());
	mSizeY = (float)(mIdleImage->GetFrameHeight());
	mRect = RectMakeCenter((int)mX, (int)mY, (int)mSizeX, (int)mSizeY);

	IMAGEMANAGER->LoadFromFile(L"Idle", (L"../Resources/Player/idle"), 294, 96, 6, 2, true);
	mIdleImage = IMAGEMANAGER->FindImage(L"Idle");

	IMAGEMANAGER->LoadFromFile(L"Run", (L"../Resources/Player/run"), 490, 96, 10, 2, true);
	mRunImage = IMAGEMANAGER->FindImage(L"Run");

	IMAGEMANAGER->LoadFromFile(L"Jump", (L"../Resources/Player/jump"), 147, 96, 3, 2, true);
	mRunImage = IMAGEMANAGER->FindImage(L"Jump");

	IMAGEMANAGER->LoadFromFile(L"Fall", (L"../Resources/Player/fall"), 245, 96, 3, 2, true);
	mRunImage = IMAGEMANAGER->FindImage(L"Fall");
	
	//스탠드 이미지
	mLeftIdleAnimation = new Animation();
	mLeftIdleAnimation->InitFrameByStartEnd(0, 1, 5, 1, false);
	mLeftIdleAnimation->SetIsLoop(true);
	mLeftIdleAnimation->SetFrameUpdateTime(0.3f);
	mLeftIdleAnimation->Play();

	mRightIdleAnimation = new Animation();
	mRightIdleAnimation->InitFrameByStartEnd(0, 0, 5, 0, false);
	mRightIdleAnimation->SetIsLoop(true);
	mRightIdleAnimation->SetFrameUpdateTime(0.3f);
	mRightIdleAnimation->Play();

	//이동 이미지
	mLeftRunAnimation = new Animation();
	mLeftRunAnimation->InitFrameByStartEnd(0, 1, 9, 1, false);
	mLeftRunAnimation->SetIsLoop(true);
	mLeftRunAnimation->SetFrameUpdateTime(0.3f);
	mLeftRunAnimation->Play();

	mRightRunAnimation = new Animation();
	mRightRunAnimation->InitFrameByStartEnd(0, 0, 9, 0, false);
	mRightRunAnimation->SetIsLoop(true);
	mRightRunAnimation->SetFrameUpdateTime(0.3f);
	mRightRunAnimation->Play();

	//점프 이미지
	mLeftJumpAnimation = new Animation();
	mLeftJumpAnimation->InitFrameByStartEnd(0, 1, 2, 1, false);
	mLeftJumpAnimation->SetIsLoop(true);
	mLeftJumpAnimation->SetFrameUpdateTime(0.3f);
	mLeftJumpAnimation->Play();

	mRightJumpAnimation = new Animation();
	mRightJumpAnimation->InitFrameByStartEnd(0, 0, 2, 0, false);
	mRightJumpAnimation->SetIsLoop(true);
	mRightJumpAnimation->SetFrameUpdateTime(0.3f);
	mRightJumpAnimation->Play();

	//점프 하강 이미지
	mLeftFallAnimation = new Animation();
	mLeftFallAnimation->InitFrameByStartEnd(0, 1, 4, 1, false);
	mLeftFallAnimation->SetIsLoop(true);
	mLeftFallAnimation->SetFrameUpdateTime(0.3f);
	mLeftFallAnimation->Play();

	mRightFallAnimation = new Animation();
	mRightFallAnimation->InitFrameByStartEnd(0, 0, 4, 0, false);
	mRightFallAnimation->SetIsLoop(true);
	mRightFallAnimation->SetFrameUpdateTime(0.3f);
	mRightFallAnimation->Play();
}

void Player::Update()
{
	//이동 프레임
	if (Input::GetInstance()->GetKeyDown(VK_LEFT))
	{
		mState = State::Left;
		mCurrentAnimation->Stop();
		mCurrentAnimation = mLeftRunAnimation;
		mCurrentAnimation->Play();
	}
	if (Input::GetInstance()->GetKeyUp(VK_LEFT))
	{
		mCurrentAnimation->Stop();
		mCurrentAnimation = mLeftIdleAnimation;
		mCurrentAnimation->Play();
	}
	if (Input::GetInstance()->GetKeyDown(VK_RIGHT))
	{
		mState = State::Right;
		mCurrentAnimation->Stop();
		mCurrentAnimation = mRightRunAnimation;
		mCurrentAnimation->Play();
	}
	if (Input::GetInstance()->GetKeyUp(VK_RIGHT))
	{
		mCurrentAnimation->Stop();
		mCurrentAnimation = mRightIdleAnimation;
		mCurrentAnimation->Play();
	}
	//점프 프레임
	if (Input::GetInstance()->GetKeyDown(VK_SPACE))
	{
		if (mState == State::Right)
		{
			mCurrentAnimation->Stop();
			mCurrentAnimation = mRightJumpAnimation;
			mCurrentAnimation->Play();
		}
		if (mState == State::Left)
		{
			mCurrentAnimation->Stop(); 
			mCurrentAnimation = mLeftJumpAnimation;
			mCurrentAnimation->Play();
		}
	}

	//이동
	if (Input::GetInstance()->GetKey(VK_LEFT))
	{
		mX -= mSpeed * Time::GetInstance()->DeltaTime();
		mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	}
	if (Input::GetInstance()->GetKey(VK_RIGHT))
	{
		mX += mSpeed * Time::GetInstance()->DeltaTime();
		mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	}
	//점프
	if (Input::GetInstance()->GetKey(VK_SPACE))
	{
		mY -= mSpeed * Time::GetInstance()->DeltaTime();
		mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
		if (mY -= 100)
		{
			mY += 100;
		}
	}


}

void Player::Render(HDC hdc)
{
	CameraManager::GetInstance()->GetMainCamera()->AlphaScaleFrameRender(hdc, mIdleImage, (int)mRect.left, (int)mRect.top, mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY(), (int)mSizeX, (int)mSizeY, 1.f);
}

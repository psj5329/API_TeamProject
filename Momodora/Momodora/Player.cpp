#include "pch.h"
#include "Player.h"
#include "Image.h"
#include "Animation.h"
#include "Camera.h"

void Player::Init()
{
	mName = "Player";
	IMAGEMANAGER->LoadFromFile(L"Idle", Resources(L"Player/idle"), 294, 96, 6, 2, true);
	mIdleImage = IMAGEMANAGER->FindImage(L"Idle");

	IMAGEMANAGER->LoadFromFile(L"Run", Resources(L"Player/run"), 490, 96, 10, 2, true);
	mRunImage = IMAGEMANAGER->FindImage(L"Run");

	IMAGEMANAGER->LoadFromFile(L"Jump", Resources(L"/Player/jump"), 147, 96, 3, 2, true);
	mJumpImage = IMAGEMANAGER->FindImage(L"Jump");

	IMAGEMANAGER->LoadFromFile(L"Fall", Resources(L"/Player/fall"), 245, 96, 5, 2, true);
	mFallImage = IMAGEMANAGER->FindImage(L"Fall");

	IMAGEMANAGER->LoadFromFile(L"Crouch", Resources(L"/Player/crouch"), 196, 96, 4, 2, true);
	mCrouchImage = IMAGEMANAGER->FindImage(L"Crouch");

	IMAGEMANAGER->LoadFromFile(L"Rise", Resources(L"/Player/rise"), 98, 96, 2, 2, true);
	mRiseImage = IMAGEMANAGER->FindImage(L"Rise");

	//스탠드 이미지
	mLeftIdleAnimation = new Animation();
	mLeftIdleAnimation->InitFrameByStartEnd(0, 1, 5, 1, true);
	mLeftIdleAnimation->SetIsLoop(true);
	mLeftIdleAnimation->SetFrameUpdateTime(0.2f);
	mLeftIdleAnimation->Play();

	mRightIdleAnimation = new Animation();
	mRightIdleAnimation->InitFrameByStartEnd(0, 0, 5, 0, false);
	mRightIdleAnimation->SetIsLoop(true);
	mRightIdleAnimation->SetFrameUpdateTime(0.2f);
	mRightIdleAnimation->Play();

	//이동 이미지
	mLeftRunStartAnimation = new Animation();
	mLeftRunStartAnimation->InitFrameByStartEnd(8, 1, 9, 1, true); //유찬
	mLeftRunStartAnimation->SetIsLoop(true);
	mLeftRunStartAnimation->SetFrameUpdateTime(0.1f);
	mLeftRunStartAnimation->Play();
	mLeftRunStartAnimation->SetCallbackFunc(bind(&Player::SetStateRun, this));

	mLeftRunAnimation = new Animation();
	mLeftRunAnimation->InitFrameByStartEnd(0, 1, 7, 1, true);
	mLeftRunAnimation->SetIsLoop(true);
	mLeftRunAnimation->SetFrameUpdateTime(0.1f);
	mLeftRunAnimation->Play();

	mRightRunStartAnimation = new Animation();
	mRightRunStartAnimation->InitFrameByStartEnd(0, 0, 1, 0, false);
	mRightRunStartAnimation->SetIsLoop(true);
	mRightRunStartAnimation->SetFrameUpdateTime(0.1f);
	mRightRunStartAnimation->Play();
	mRightRunStartAnimation->SetCallbackFunc(bind(&Player::SetStateRun, this));

	mRightRunAnimation = new Animation();
	mRightRunAnimation->InitFrameByStartEnd(2, 0, 9, 0, false);
	mRightRunAnimation->SetIsLoop(true);
	mRightRunAnimation->SetFrameUpdateTime(0.1f);
	mRightRunAnimation->Play();

	//점프 이미지
	mLeftJumpAnimation = new Animation();
	mLeftJumpAnimation->InitFrameByStartEnd(0, 1, 2, 1, true);
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
	mLeftFallAnimation->InitFrameByStartEnd(0, 1, 4, 1, true);
	mLeftFallAnimation->SetIsLoop(true);
	mLeftFallAnimation->SetFrameUpdateTime(0.3f);
	mLeftFallAnimation->Play();

	mRightFallAnimation = new Animation();
	mRightFallAnimation->InitFrameByStartEnd(0, 0, 4, 0, false);
	mRightFallAnimation->SetIsLoop(true);
	mRightFallAnimation->SetFrameUpdateTime(0.3f);
	mRightFallAnimation->Play();

	//앉기 이미지
	mLeftCrouchAnimation = new Animation();
	mLeftCrouchAnimation->InitFrameByStartEnd(0, 1, 3, 1, true);
	mLeftCrouchAnimation->SetIsLoop(false);
	mLeftCrouchAnimation->SetFrameUpdateTime(0.3f);
	mLeftCrouchAnimation->Play();

	mRightCrouchAnimation = new Animation();
	mRightCrouchAnimation->InitFrameByStartEnd(0, 0, 3, 0, false);
	mRightCrouchAnimation->SetIsLoop(false);
	mRightCrouchAnimation->SetFrameUpdateTime(0.3f);
	mRightCrouchAnimation->Play();

	//일어나기 이미지
	mLeftRiseAnimation = new Animation();
	mLeftRiseAnimation->InitFrameByStartEnd(0, 1, 1, 1, true);
	mLeftRiseAnimation->SetIsLoop(false);
	mLeftRiseAnimation->SetFrameUpdateTime(0.3f);
	mLeftRiseAnimation->Play();

	mRightRiseAnimation = new Animation();
	mRightRiseAnimation->InitFrameByStartEnd(0, 0, 1, 0, false);
	mRightRiseAnimation->SetIsLoop(false);
	mRightRiseAnimation->SetFrameUpdateTime(0.3f);
	mRightRiseAnimation->Play();

	//값 설정
	mX = WINSIZEX / 2;
	mY = WINSIZEY / 2;
	mSpeed = 200.f;
	mGravity = 0.2f;
	mState = State::Right;
	mCurrentAnimation = mRightIdleAnimation;
	mCurrentImage = mIdleImage;
	mSizeX = (float)(mIdleImage->GetFrameWidth());
	mSizeY = (float)(mIdleImage->GetFrameHeight());
	mRect = RectMakeCenter((int)mX, (int)mY, (int)mSizeX, (int)mSizeY);
}

void Player::Release()
{
	
}

void Player::Update()
{
	//이동 프레임
	if (Input::GetInstance()->GetKeyDown(VK_LEFT))
	{
		mState = State::Left;
		mCurrentAnimation->Stop();
		mCurrentAnimation = mLeftRunStartAnimation;
		mCurrentAnimation->Play();
		mCurrentImage = mRunImage;
	}
	if (Input::GetInstance()->GetKeyUp(VK_LEFT))
	{
		mCurrentAnimation->Stop();
		mCurrentAnimation = mLeftIdleAnimation;
		mCurrentAnimation->Play();
		mCurrentImage = mIdleImage;
	}
	if (Input::GetInstance()->GetKeyDown(VK_RIGHT))
	{
		mState = State::Right;
		mCurrentAnimation->Stop();
		mCurrentAnimation = mRightRunStartAnimation;
		mCurrentAnimation->Play();
		mCurrentImage = mRunImage;
	}
	if (Input::GetInstance()->GetKeyUp(VK_RIGHT))
	{
		mCurrentAnimation->Stop();
		mCurrentAnimation = mRightIdleAnimation;
		mCurrentAnimation->Play();
		mCurrentImage = mIdleImage;
	}
	//점프 프레임
	if (Input::GetInstance()->GetKeyDown(VK_SPACE))
	{
		mJumpPower = 8.f;

		if (mJumpPower > 0)
		{
			if (mState == State::Right)
			{
				mCurrentAnimation->Stop();
				mCurrentAnimation = mRightJumpAnimation;
				mCurrentAnimation->Play();
				mCurrentImage = mJumpImage;
			}
			if (mState == State::Left)
			{
				mCurrentAnimation->Stop();
				mCurrentAnimation = mLeftJumpAnimation;
				mCurrentAnimation->Play();
				mCurrentImage = mJumpImage;
			}
		}
		if (mJumpPower < 0)
		{
			if (mState == State::Right)
			{
				mCurrentAnimation->Stop();
				mCurrentAnimation = mRightFallAnimation;
				mCurrentAnimation->Play();
				mCurrentImage = mFallImage;
			}
			if (mState == State::Left)
			{
				mCurrentAnimation->Stop();
				mCurrentAnimation = mLeftFallAnimation;
				mCurrentAnimation->Play();
				mCurrentImage = mFallImage;
			}
		}
	}
	//점프
	mY -= mJumpPower;
	mJumpPower -= mGravity;
	if (mY > WINSIZEY / 2)
	{
		mJumpPower = 0;
		//mCurrentImage = mIdleImage;
	}

	//앉기 프레임
	if (Input::GetInstance()->GetKeyDown('C'))
	{
		mRect.top += 24;

		if (mState == State::Right)
		{
			mCurrentAnimation->Stop();
			mCurrentAnimation = mRightCrouchAnimation;
			mCurrentAnimation->Play();
			mCurrentImage = mCrouchImage;
		}
		if (mState == State::Left)
		{
			mCurrentAnimation->Stop();
			mCurrentAnimation = mLeftCrouchAnimation;
			mCurrentAnimation->Play();
			mCurrentImage = mCrouchImage;
		}
	}
	//일어서기 프레임
	if (Input::GetInstance()->GetKeyUp('C'))
	{
		mRect.top -= 24;

		if (mState == State::Right)
		{
			mCurrentAnimation->Stop();
			mCurrentAnimation = mRightRiseAnimation;
			mCurrentAnimation->Play();
			mCurrentImage = mRiseImage;
		}
		if (mState == State::Left)
		{
			mCurrentAnimation->Stop();
			mCurrentAnimation = mLeftRiseAnimation;
			mCurrentAnimation->Play();
			mCurrentImage = mRiseImage;
		}
	}

	//이동
	if (Input::GetInstance()->GetKey(VK_LEFT))
	{
		mX -= mSpeed * Time::GetInstance()->DeltaTime();
	}
	if (Input::GetInstance()->GetKey(VK_RIGHT))
	{
		mX += mSpeed * Time::GetInstance()->DeltaTime();
	}
	//앉기
	//if (Input::GetInstance()->GetKeyDown('C'))
	//{
	//	mRect.top += 24;
	//}
	//if (Input::GetInstance()->GetKeyUp('C'))
	//{
	//	mRect.top -= 24;
	//	mCurrentImage = mIdleImage;
	//}

	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);

	mCurrentAnimation->Update();
}

void Player::Render(HDC hdc)
{
	CameraManager::GetInstance()->GetMainCamera()->AlphaScaleFrameRender(hdc, mCurrentImage, (int)mRect.left, (int)mRect.top, mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY(), (int)mSizeX * 2, (int)mSizeY * 2, 1.f);
}

void Player::SetStateRun()
{
	if (mState == State::Left)
	{
		mCurrentAnimation->Stop();
		mCurrentAnimation = mLeftRunAnimation;
		mCurrentAnimation->Play();
		mCurrentImage = mRunImage;
	}
	else if (mState == State::Right)
	{
		mCurrentAnimation->Stop();
		mCurrentAnimation = mRightRunAnimation;
		mCurrentAnimation->Play();
		mCurrentImage = mRunImage;
	}
}
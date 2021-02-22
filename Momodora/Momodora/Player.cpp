#include "pch.h"
#include "Player.h"
#include "Image.h"
#include "Animation.h"
#include "Camera.h"

void Player::Init()
{
	IMAGEMANAGER->LoadFromFile(L"Idle", Resources(L"Player/idle"), 294, 96, 6, 2, true);
	mIdleImage = IMAGEMANAGER->FindImage(L"Idle");

	IMAGEMANAGER->LoadFromFile(L"Run", Resources(L"Player/run"), 490, 96, 10, 2, true);
	mRunImage = IMAGEMANAGER->FindImage(L"Run");

	IMAGEMANAGER->LoadFromFile(L"Jump", Resources(L"/Player/jump"), 147, 96, 3, 2, true);
	mJumpImage = IMAGEMANAGER->FindImage(L"Jump");

	IMAGEMANAGER->LoadFromFile(L"Fall", Resources(L"/Player/fall"), 245, 96, 3, 2, true);
	mFallImage = IMAGEMANAGER->FindImage(L"Fall");

	IMAGEMANAGER->LoadFromFile(L"Crouch", Resources(L"/Player/crouch"), 196, 96, 4, 2, true);
	mCrouchImage = IMAGEMANAGER->FindImage(L"Crouch");

	IMAGEMANAGER->LoadFromFile(L"Rise", Resources(L"/Player/rise"), 98, 96, 2, 2, true);
	mRiseImage = IMAGEMANAGER->FindImage(L"Rise");

	//���ĵ� �̹���
	mLeftIdleAnimation = new Animation();
	mLeftIdleAnimation->InitFrameByStartEnd(0, 1, 5, 1, true);
	mLeftIdleAnimation->SetIsLoop(true);
	mLeftIdleAnimation->SetFrameUpdateTime(0.3f);
	mLeftIdleAnimation->Play();

	mRightIdleAnimation = new Animation();
	mRightIdleAnimation->InitFrameByStartEnd(0, 0, 5, 0, false);
	mRightIdleAnimation->SetIsLoop(true);
	mRightIdleAnimation->SetFrameUpdateTime(0.3f);
	mRightIdleAnimation->Play();

	//�̵� �̹���
	mLeftRunAnimation = new Animation();
	mLeftRunAnimation->InitFrameByStartEnd(0, 1, 9, 1, true);
	mLeftRunAnimation->SetIsLoop(true);
	mLeftRunAnimation->SetFrameUpdateTime(0.3f);
	mLeftRunAnimation->Play();

	mRightRunAnimation = new Animation();
	mRightRunAnimation->InitFrameByStartEnd(0, 0, 9, 0, false);
	mRightRunAnimation->SetIsLoop(true);
	mRightRunAnimation->SetFrameUpdateTime(0.3f);
	mRightRunAnimation->Play();

	//���� �̹���
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

	//���� �ϰ� �̹���
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

	//�ɱ� �̹���
	mLeftCrouchAnimation = new Animation();
	mLeftCrouchAnimation->InitFrameByStartEnd(0, 1, 3, 1, false);
	mLeftCrouchAnimation->SetIsLoop(true);
	mLeftCrouchAnimation->SetFrameUpdateTime(0.3f);
	mLeftCrouchAnimation->Play();

	mRightCrouchAnimation = new Animation();
	mRightCrouchAnimation->InitFrameByStartEnd(0, 0, 3, 0, false);
	mRightCrouchAnimation->SetIsLoop(true);
	mRightCrouchAnimation->SetFrameUpdateTime(0.3f);
	mRightCrouchAnimation->Play();

	//�Ͼ�� �̹���
	mLeftRiseAnimation = new Animation();
	mLeftRiseAnimation->InitFrameByStartEnd(0, 1, 1, 1, true);
	mLeftRiseAnimation->SetIsLoop(true);
	mLeftRiseAnimation->SetFrameUpdateTime(0.3f);
	mLeftRiseAnimation->Play();

	mRightRiseAnimation = new Animation();
	mRightRiseAnimation->InitFrameByStartEnd(0, 0, 1, 0, false);
	mRightRiseAnimation->SetIsLoop(true);
	mRightRiseAnimation->SetFrameUpdateTime(0.3f);
	mRightRiseAnimation->Play();

	//�� ����
	mX = WINSIZEX / 2;
	mY = WINSIZEY / 2;
	mSpeed = 200.f;
	mJumpPower = 8.f;
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
	//�̵� ������
	if (Input::GetInstance()->GetKeyDown(VK_LEFT))
	{
		mState = State::Left;
		mCurrentAnimation->Stop();
		mCurrentAnimation = mLeftRunAnimation;
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
		mCurrentAnimation = mRightRunAnimation;
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
	//���� ������
	if (Input::GetInstance()->GetKeyDown(VK_SPACE))
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
	//�ϰ� ������
	//if (mJumpPower <= 0)
	//{
	//
	//}

	//�ɱ� ������
	if (Input::GetInstance()->GetKeyDown('C'))
	{
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
	//�Ͼ�� ������
	if (Input::GetInstance()->GetKeyUp('C'))
	{
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

	//�̵�
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
	//����
	if (Input::GetInstance()->GetKeyDown(VK_SPACE))
	{
		mY -= mJumpPower;
		mJumpPower -= mGravity;
	}
	//�ɱ�
	//if (Input::GetInstance()->GetKeyDown('C'))
	//{
	//	mRect.top += 24;
	//}
	//if (Input::GetInstance()->GetKeyUp('C'))
	//{
	//	mRect.top -= 24;
	//	mCurrentImage = mIdleImage;
	//}


	mCurrentAnimation->Update();
}

void Player::Render(HDC hdc)
{
	CameraManager::GetInstance()->GetMainCamera()->AlphaScaleFrameRender(hdc, mCurrentImage, (int)mRect.left, (int)mRect.top, mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY(), (int)mSizeX * 2, (int)mSizeY * 2, 1.f);
}

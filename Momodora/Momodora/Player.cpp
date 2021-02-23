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
	
	IMAGEMANAGER->LoadFromFile(L"Turn", Resources(L"/Player/turn"), 147, 96, 3, 2, true);
	mTurnImage = IMAGEMANAGER->FindImage(L"Turn");

	IMAGEMANAGER->LoadFromFile(L"Jump", Resources(L"/Player/jump"), 147, 96, 3, 2, true);
	mJumpImage = IMAGEMANAGER->FindImage(L"Jump");

	IMAGEMANAGER->LoadFromFile(L"Fall", Resources(L"/Player/fall"), 245, 96, 5, 2, true);
	mFallImage = IMAGEMANAGER->FindImage(L"Fall");

	IMAGEMANAGER->LoadFromFile(L"Crouch", Resources(L"/Player/crouch"), 196, 96, 4, 2, true);
	mCrouchImage = IMAGEMANAGER->FindImage(L"Crouch");

	IMAGEMANAGER->LoadFromFile(L"Rise", Resources(L"/Player/rise"), 98, 96, 2, 2, true);
	mRiseImage = IMAGEMANAGER->FindImage(L"Rise");

	IMAGEMANAGER->LoadFromFile(L"Roll", Resources(L"/Player/roll"), 392, 96, 8, 2, true);
	mRollImage = IMAGEMANAGER->FindImage(L"Roll");

	IMAGEMANAGER->LoadFromFile(L"LadderUp", Resources(L"/Player/ladderup"), 204, 48, 6, 1, true);
	mLadderUpImage = IMAGEMANAGER->FindImage(L"LadderUp");

	IMAGEMANAGER->LoadFromFile(L"LadderDown", Resources(L"/Player/ladderdown"), 105, 43, 3, 1, true);
	mLadderDownImage = IMAGEMANAGER->FindImage(L"LadderDown");

	IMAGEMANAGER->LoadFromFile(L"LadderEnter", Resources(L"/Player/ladderenter"), 390, 128, 6, 2, true);
	mLadderEnterImage = IMAGEMANAGER->FindImage(L"LadderEnter");

	IMAGEMANAGER->LoadFromFile(L"LadderLeave", Resources(L"/Player/ladderleave"), 294, 160, 6, 2, true);
	mLadderLeaveImage = IMAGEMANAGER->FindImage(L"LadderLeave");


	//���ĵ� �ִϸ��̼�
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
	//�̵� �ִϸ��̼�
	mLeftRunStartAnimation = new Animation();
	mLeftRunStartAnimation->InitFrameByStartEnd(8, 1, 9, 1, true);
	mLeftRunStartAnimation->SetIsLoop(false);
	mLeftRunStartAnimation->SetFrameUpdateTime(0.1f);
	mLeftRunStartAnimation->Play();
	mLeftRunStartAnimation->SetCallbackFunc(bind(&Player::SetStateRun, this));

	mLeftRunAnimation = new Animation();
	mLeftRunAnimation->InitFrameByStartEnd(0, 1, 7, 1, true);
	mLeftRunAnimation->SetIsLoop(true);
	mLeftRunAnimation->SetFrameUpdateTime(0.1f);
	mLeftRunAnimation->Play();

	mRightRunStartAnimation = new Animation();
	mRightRunStartAnimation->InitFrameByStartEnd(0, 0, 1, 0, true);
	mRightRunStartAnimation->SetIsLoop(false);
	mRightRunStartAnimation->SetFrameUpdateTime(0.1f);
	mRightRunStartAnimation->Play();
	mRightRunStartAnimation->SetCallbackFunc(bind(&Player::SetStateRun, this));

	mRightRunAnimation = new Animation();
	mRightRunAnimation->InitFrameByStartEnd(2, 0, 9, 0, false);
	mRightRunAnimation->SetIsLoop(true);
	mRightRunAnimation->SetFrameUpdateTime(0.1f);
	mRightRunAnimation->Play();
	//������ȯ �ִϸ��̼�
	mLeftTurnAnimation = new Animation();
	mLeftTurnAnimation->InitFrameByStartEnd(0, 1, 2, 1, true);
	mLeftTurnAnimation->SetIsLoop(false);
	mLeftTurnAnimation->SetFrameUpdateTime(0.3f);
	mLeftTurnAnimation->Play();

	mRightTurnAnimation = new Animation();
	mRightTurnAnimation->InitFrameByStartEnd(0, 0, 2, 0, false);
	mRightTurnAnimation->SetIsLoop(false);
	mRightTurnAnimation->SetFrameUpdateTime(0.3f);
	mRightTurnAnimation->Play();
	//���� �ִϸ��̼�
	mLeftJumpAnimation = new Animation();
	mLeftJumpAnimation->InitFrameByStartEnd(0, 1, 2, 1, true);
	mLeftJumpAnimation->SetIsLoop(true);
	mLeftJumpAnimation->SetFrameUpdateTime(0.2f);
	mLeftJumpAnimation->Play();
	mLeftJumpAnimation->SetCallbackFunc(bind(&Player::SetStateFall, this));

	mRightJumpAnimation = new Animation();
	mRightJumpAnimation->InitFrameByStartEnd(0, 0, 2, 0, false);
	mRightJumpAnimation->SetIsLoop(true);
	mRightJumpAnimation->SetFrameUpdateTime(0.2f);
	mRightJumpAnimation->Play();
	mRightJumpAnimation->SetCallbackFunc(bind(&Player::SetStateFall, this));
	//���� �ϰ� �ִϸ��̼�
	mLeftFallAnimation = new Animation();
	mLeftFallAnimation->InitFrameByStartEnd(0, 1, 4, 1, true);
	mLeftFallAnimation->SetIsLoop(false);
	mLeftFallAnimation->SetFrameUpdateTime(0.2f);
	mLeftFallAnimation->Play();

	mRightFallAnimation = new Animation();
	mRightFallAnimation->InitFrameByStartEnd(0, 0, 4, 0, false);
	mRightFallAnimation->SetIsLoop(false);
	mRightFallAnimation->SetFrameUpdateTime(0.2f);
	mRightFallAnimation->Play();
	//�ɱ� �ִϸ��̼�
	mLeftCrouchAnimation = new Animation();
	mLeftCrouchAnimation->InitFrameByStartEnd(0, 1, 3, 1, true);
	mLeftCrouchAnimation->SetIsLoop(false);
	mLeftCrouchAnimation->SetFrameUpdateTime(0.1f);
	mLeftCrouchAnimation->Play();

	mRightCrouchAnimation = new Animation();
	mRightCrouchAnimation->InitFrameByStartEnd(0, 0, 3, 0, false);
	mRightCrouchAnimation->SetIsLoop(false);
	mRightCrouchAnimation->SetFrameUpdateTime(0.1f);
	mRightCrouchAnimation->Play();
	//�Ͼ�� �ִϸ��̼�
	mLeftRiseAnimation = new Animation();
	mLeftRiseAnimation->InitFrameByStartEnd(0, 1, 1, 1, true);
	mLeftRiseAnimation->SetIsLoop(false);
	mLeftRiseAnimation->SetFrameUpdateTime(0.1f);
	mLeftRiseAnimation->Play();

	mRightRiseAnimation = new Animation();
	mRightRiseAnimation->InitFrameByStartEnd(0, 0, 1, 0, false);
	mRightRiseAnimation->SetIsLoop(false);
	mRightRiseAnimation->SetFrameUpdateTime(0.1f);
	mRightRiseAnimation->Play();
	//������ �ִϸ��̼�
	mLeftRollAnimation = new Animation();
	mLeftRollAnimation->InitFrameByStartEnd(0, 1, 7, 1, true);
	mLeftRollAnimation->SetIsLoop(false);
	mLeftRollAnimation->SetFrameUpdateTime(0.07f);
	mLeftRollAnimation->Play();
	mLeftRollAnimation->SetCallbackFunc(bind(&Player::SetStateIdle, this));

	mRightRollAnimation = new Animation();
	mRightRollAnimation->InitFrameByStartEnd(0, 0, 7, 0, false);
	mRightRollAnimation->SetIsLoop(false);
	mRightRollAnimation->SetFrameUpdateTime(0.07f);
	mRightRollAnimation->Play();
	mRightRollAnimation->SetCallbackFunc(bind(&Player::SetStateIdle, this));
	//��ٸ� �ִϸ��̼�
	mLadderUpAnimation = new Animation();
	mLadderUpAnimation->InitFrameByStartEnd(0, 0, 5, 0, true);
	mLadderUpAnimation->SetIsLoop(true);
	mLadderUpAnimation->SetFrameUpdateTime(0.1f);
	mLadderUpAnimation->Play();

	mLadderDownAnimation = new Animation();
	mLadderDownAnimation->InitFrameByStartEnd(0, 0, 2, 0, true);
	mLadderDownAnimation->SetIsLoop(true);
	mLadderDownAnimation->SetFrameUpdateTime(0.1f);
	mLadderDownAnimation->Play();
	//��ٸ� ���� �ִϸ��̼�
	mLeftLadderEnterAnimation = new Animation();
	mLeftLadderEnterAnimation->InitFrameByStartEnd(0, 1, 5, 1, true);
	mLeftLadderEnterAnimation->SetIsLoop(true);
	mLeftLadderEnterAnimation->SetFrameUpdateTime(0.1f);
	mLeftLadderEnterAnimation->Play();

	mRightLadderEnterAnimation = new Animation();
	mRightLadderEnterAnimation->InitFrameByStartEnd(0, 0, 5, 0, false);
	mRightLadderEnterAnimation->SetIsLoop(true);
	mRightLadderEnterAnimation->SetFrameUpdateTime(0.1f);
	mRightLadderEnterAnimation->Play();
	//��ٸ� ���� �ִϸ��̼�
	mLeftLadderLeaveAnimation = new Animation();
	mLeftLadderLeaveAnimation->InitFrameByStartEnd(0, 1, 5, 1, true);
	mLeftLadderLeaveAnimation->SetIsLoop(true);
	mLeftLadderLeaveAnimation->SetFrameUpdateTime(0.1f);
	mLeftLadderLeaveAnimation->Play();

	mRightLadderLeaveAnimation = new Animation();
	mRightLadderLeaveAnimation->InitFrameByStartEnd(0, 0, 5, 0, false);
	mRightLadderLeaveAnimation->SetIsLoop(true);
	mRightLadderLeaveAnimation->SetFrameUpdateTime(0.1f);

	//�� ����
	mX = WINSIZEX / 2;
	mY = WINSIZEY / 2;
	mCurrentAnimation = mRightIdleAnimation;
	mCurrentImage = mIdleImage;
	mSizeX = (float)(mIdleImage->GetFrameWidth()) *2;
	mSizeY = (float)(mIdleImage->GetFrameHeight()) *2;
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
		mState = State::LeftRun;
		mCurrentAnimation->Stop();
		mCurrentAnimation = mLeftRunStartAnimation;
		mCurrentAnimation->Play();
		mCurrentImage = mRunImage;
	}
	if (Input::GetInstance()->GetKeyUp(VK_LEFT))
	{
		mState = State::LeftIdle;
		mCurrentAnimation->Stop();
		mCurrentAnimation = mLeftIdleAnimation;
		mCurrentAnimation->Play();
		mCurrentImage = mIdleImage;
	}
	if (Input::GetInstance()->GetKeyDown(VK_RIGHT))
	{
		mState = State::RightRun;
		mCurrentAnimation->Stop();
		mCurrentAnimation = mRightRunStartAnimation;
		mCurrentAnimation->Play();
		mCurrentImage = mRunImage;
	}
	if (Input::GetInstance()->GetKeyUp(VK_RIGHT))
	{
		mState = State::RightIdle;
		mCurrentAnimation->Stop();
		mCurrentAnimation = mRightIdleAnimation;
		mCurrentAnimation->Play();
		mCurrentImage = mIdleImage;
	}
	//�̵� ���� �� ������ȯ
	if (Input::GetInstance()->GetKey(VK_LEFT))
	{
		if (stopmove == 0)
		{
			mX -= mSpeed * Time::GetInstance()->DeltaTime();

			if (Input::GetInstance()->GetKeyDown(VK_RIGHT))
			{
				mState = State::RightRun;
				mCurrentAnimation->Stop();
				mCurrentAnimation = mRightTurnAnimation;
				mCurrentAnimation->Play();
				mCurrentImage = mTurnImage;
			}
		}
	}
	if (Input::GetInstance()->GetKey(VK_RIGHT))
	{
		if (stopmove == 0)
		{
			mX += mSpeed * Time::GetInstance()->DeltaTime();

			if (Input::GetInstance()->GetKeyDown(VK_LEFT))
			{
				mState = State::LeftRun;
				mCurrentAnimation->Stop();
				mCurrentAnimation = mLeftTurnAnimation;
				mCurrentAnimation->Play();
				mCurrentImage = mTurnImage;
			}
		}
	}

	//����
	if (Input::GetInstance()->GetKeyDown(VK_SPACE))
	{
		mJumpPower = 8.f;

		if (mJumpPower > 0)
		{
			if (mState == State::LeftIdle || mState == State::LeftRun)
			{
				mState = State::LeftJump;
				mCurrentAnimation->Stop();
				mCurrentAnimation = mLeftJumpAnimation;
				mCurrentAnimation->Play();
				mCurrentImage = mJumpImage;
			}
			if (mState == State::RightIdle || mState == State::RightRun)
			{
				mState = State::RightJump;
				mCurrentAnimation->Stop();
				mCurrentAnimation = mRightJumpAnimation;
				mCurrentAnimation->Play();
				mCurrentImage = mJumpImage;
			}
		}
		if (mJumpPower < 0)
		{
			if (mState == State::LeftJump)
			{
				mCurrentAnimation->Stop();
				mCurrentAnimation = mLeftFallAnimation;
				mCurrentAnimation->Play();
				mCurrentImage = mFallImage;
			}
			if (mState == State::RightJump)
			{
				mCurrentAnimation->Stop();
				mCurrentAnimation = mRightFallAnimation;
				mCurrentAnimation->Play();
				mCurrentImage = mFallImage;
			}
		}
	}
	mY -= mJumpPower;
	mJumpPower -= mGravity;
	if (mY > WINSIZEY / 2)
	{
		mJumpPower = 0;
	}

	//�ɱ�
	if (Input::GetInstance()->GetKeyDown('C'))
	{
		stopmove = 1;

		if (mState == State::LeftIdle || mState == State::LeftRun)
		{
			mState = State::LeftCrouch;
			mCurrentAnimation->Stop();
			mCurrentAnimation = mLeftCrouchAnimation;
			mCurrentAnimation->Play();
			mCurrentImage = mCrouchImage;
		}
		if (mState == State::RightIdle || mState == State::RightRun)
		{
			mState = State::RightCrouch;
			mCurrentAnimation->Stop();
			mCurrentAnimation = mRightCrouchAnimation;
			mCurrentAnimation->Play();
			mCurrentImage = mCrouchImage;
		}
	}
	//�Ͼ��
	if (Input::GetInstance()->GetKeyUp('C'))
	{
		stopmove = 0;

		if (mState == State::LeftCrouch)
		{
			mCurrentAnimation->Stop();
			mCurrentAnimation = mLeftRiseAnimation;
			mCurrentAnimation->Play();
			mCurrentImage = mRiseImage;
		}
		if (mState == State::RightCrouch)
		{
			mCurrentAnimation->Stop();
			mCurrentAnimation = mRightRiseAnimation;
			mCurrentAnimation->Play();
			mCurrentImage = mRiseImage;
		}
	}

	//������
	if (Input::GetInstance()->GetKeyDown(VK_LSHIFT)) //�̵�Ű�� ���� �Է½� �̵��ӵ�+������ӵ�
	{
		//stopmove = 1;

		if (mState == State::LeftIdle || mState == State::LeftRun)
		{
			mState = State::LeftRoll;
			mCurrentAnimation->Stop();
			mCurrentAnimation = mLeftRollAnimation;
			mCurrentAnimation->Play();
			mCurrentImage = mRollImage;
		}
		if (mState == State::RightIdle || mState == State::RightRun)
		{
			mState = State::RightRoll;
			mCurrentAnimation->Stop();
			mCurrentAnimation = mRightRollAnimation;
			mCurrentAnimation->Play();
			mCurrentImage = mRollImage;
		}
	}
	if (mState == State::LeftRoll)
	{
		mX -= mSpeed * Time::GetInstance()->DeltaTime() * 1.3f;
		mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	}
	if (mState == State::RightRoll)
	{
		mX += mSpeed * Time::GetInstance()->DeltaTime() * 1.3f;
		mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	}

	//��ٸ�
	if (Input::GetInstance()->GetKey(VK_UP))
	{
		if (mState == State::LeftIdle || mState == State::LeftRun || mState == State::LeftJump)
		{
			mState = State::LeftEnterLadder;
			mCurrentAnimation->Stop();
			mCurrentAnimation = mLeftLadderEnterAnimation;
			mCurrentAnimation->Play();
			mCurrentImage = mLadderEnterImage;
		}
		if (mState == State::RightIdle || mState == State::RightRun || mState == State::RightJump)
		{
			mState = State::RightEnterLadder;
			mCurrentAnimation->Stop();
			mCurrentAnimation = mRightLadderEnterAnimation;
			mCurrentAnimation->Play();
			mCurrentImage = mLadderEnterImage;
		}
	}
	if (Input::GetInstance()->GetKey(VK_DOWN))
	{
		if (mState == State::LeftIdle || mState == State::LeftRun || mState == State::LeftJump)
		{

		}
		if (mState == State::RightIdle || mState == State::RightRun || mState == State::RightJump)
		{

		}
	}


	//false �϶��� ������
	if (stopmove == 0)
	{
		mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	}
	mCurrentAnimation->Update();
}

void Player::Render(HDC hdc)
{
	CAMERAMANAGER->GetMainCamera()->RenderRectInCamera(hdc, mRect);
	CameraManager::GetInstance()->GetMainCamera()->AlphaScaleFrameRender(hdc, mCurrentImage, (int)mRect.left, (int)mRect.top, mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY(), (int)mSizeX, (int)mSizeY , 1.f);
}

void Player::SetStateRun()
{
	if (mState == State::LeftRun)
	{
		mCurrentAnimation->Stop();
		mCurrentAnimation = mLeftRunAnimation;
		mCurrentAnimation->Play();
		mCurrentImage = mRunImage;
	}
	else if (mState == State::RightRun)
	{
		mCurrentAnimation->Stop();
		mCurrentAnimation = mRightRunAnimation;
		mCurrentAnimation->Play();
		mCurrentImage = mRunImage;
	}
}

void Player::SetStateIdle()
{
	if (mState == State::LeftRoll)
	{
		mState = State::LeftIdle;
		mCurrentAnimation->Stop();
		mCurrentAnimation = mLeftIdleAnimation;
		mCurrentAnimation->Play();
		mCurrentImage = mIdleImage;
	}
	else if (mState == State::RightRoll)
	{
		mState = State::RightIdle;
		mCurrentAnimation->Stop();
		mCurrentAnimation = mRightIdleAnimation;
		mCurrentAnimation->Play();
		mCurrentImage = mIdleImage;
	}
}

void Player::SetStateFall()
{
	if (mState == State::LeftJump)
	{
		mState = State::LeftFall;
		mCurrentAnimation->Stop();
		mCurrentAnimation = mLeftFallAnimation;
		mCurrentAnimation->Play();
		mCurrentImage = mFallImage;
	}
	else if (mState == State::RightJump)
	{
		mState = State::RightFall;
		mCurrentAnimation->Stop();
		mCurrentAnimation = mRightFallAnimation;
		mCurrentAnimation->Play();
		mCurrentImage = mFallImage;
	}
}

void Player::SetStateLadderUp()
{
	if (mState == State::LeftEnterLadder || mState == State::RightEnterLadder)
	{
		mState = State::LadderUp;
		mCurrentAnimation->Stop();
		mCurrentAnimation = mLadderUpAnimation;
		mCurrentAnimation->Play();
		mCurrentImage = mLadderUpImage;
	}
}

void Player::SetStateLadderDown()
{
	if (mState == State::LeftEnterLadder || mState == State::RightEnterLadder)
	{
		mState = State::LadderDown;
		mCurrentAnimation->Stop();
		mCurrentAnimation = mLadderDownAnimation;
		mCurrentAnimation->Play();
		mCurrentImage = mLadderDownImage;
	}
}
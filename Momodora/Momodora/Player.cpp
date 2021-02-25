#include "pch.h"
#include "Player.h"
#include "Image.h"
#include "Animation.h"
#include "Camera.h"
#include "Arrow.h"

Player::Player()
	: GameObject()
{
}

void Player::Init()
{
	mName = "Player";

	mIdleImage = IMAGEMANAGER->FindImage(L"Idle");
	mRunImage = IMAGEMANAGER->FindImage(L"Run");
	mBrakeImage = IMAGEMANAGER->FindImage(L"Brake");
	mTurnImage = IMAGEMANAGER->FindImage(L"Turn");
	mJumpImage = IMAGEMANAGER->FindImage(L"Jump");
	mFallImage = IMAGEMANAGER->FindImage(L"Fall");
	mLandSoftImage = IMAGEMANAGER->FindImage(L"LandSoft");
	mCrouchImage = IMAGEMANAGER->FindImage(L"Crouch");
	mRiseImage = IMAGEMANAGER->FindImage(L"Rise");
	mRollImage = IMAGEMANAGER->FindImage(L"Roll");
	mLadderUpImage = IMAGEMANAGER->FindImage(L"LadderUp");
	mLadderDownImage = IMAGEMANAGER->FindImage(L"LadderDown");
	mLadderEnterImage = IMAGEMANAGER->FindImage(L"LadderEnter");
	mLadderLeaveImage = IMAGEMANAGER->FindImage(L"LadderLeave");
	mBowImage = IMAGEMANAGER->FindImage(L"Bow");
	mAirBowImage = IMAGEMANAGER->FindImage(L"AirBow");
	mCrouchBowImage = IMAGEMANAGER->FindImage(L"CrouchBow");
	mAttack1Image = IMAGEMANAGER->FindImage(L"Attack1");
	mAttack2Image = IMAGEMANAGER->FindImage(L"Attack2");
	mAttack3Image = IMAGEMANAGER->FindImage(L"Attack3");
	mAirAttackImage = IMAGEMANAGER->FindImage(L"AirAttack");
	mHurtImage = IMAGEMANAGER->FindImage(L"Hurt");
	mDeathImage = IMAGEMANAGER->FindImage(L"Death");
	

	//스탠드 애니메이션
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
	//이동 애니메이션
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
	mRightRunStartAnimation->InitFrameByStartEnd(0, 0, 1, 0, false);
	mRightRunStartAnimation->SetIsLoop(false);
	mRightRunStartAnimation->SetFrameUpdateTime(0.1f);
	mRightRunStartAnimation->Play();
	mRightRunStartAnimation->SetCallbackFunc(bind(&Player::SetStateRun, this));

	mRightRunAnimation = new Animation();
	mRightRunAnimation->InitFrameByStartEnd(2, 0, 9, 0, false);
	mRightRunAnimation->SetIsLoop(true);
	mRightRunAnimation->SetFrameUpdateTime(0.1f);
	mRightRunAnimation->Play();
	//브레이크 애니메이션
	mLeftBrakeAnimation = new Animation();
	mLeftBrakeAnimation->InitFrameByStartEnd(0, 1, 6, 1, true);
	mLeftBrakeAnimation->SetIsLoop(true);
	mLeftBrakeAnimation->SetFrameUpdateTime(0.05f);
	mLeftBrakeAnimation->Play();
	mLeftBrakeAnimation->SetCallbackFunc(bind(&Player::SetStateIdle, this));

	mRightBrakeAnimation = new Animation();
	mRightBrakeAnimation->InitFrameByStartEnd(0, 0, 6, 0, false);
	mRightBrakeAnimation->SetIsLoop(true);
	mRightBrakeAnimation->SetFrameUpdateTime(0.05f);
	mRightBrakeAnimation->Play();
	mRightBrakeAnimation->SetCallbackFunc(bind(&Player::SetStateIdle, this));
	//방향전환 애니메이션
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
	//점프 애니메이션
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
	//점프 하강 애니메이션
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
	//약한 착지 애니메이션
	mLeftLandSoftAnimation = new Animation();
	mLeftLandSoftAnimation->InitFrameByStartEnd(0, 1, 3, 1, true);
	mLeftLandSoftAnimation->SetIsLoop(true);
	mLeftLandSoftAnimation->SetFrameUpdateTime(0.1f);
	mLeftLandSoftAnimation->Play();
	mLeftLandSoftAnimation->SetCallbackFunc(bind(&Player::SetStateIdle, this));

	mRightLandSoftAnimation = new Animation();
	mRightLandSoftAnimation->InitFrameByStartEnd(0, 0, 3, 0, false);
	mRightLandSoftAnimation->SetIsLoop(true);
	mRightLandSoftAnimation->SetFrameUpdateTime(0.1f);
	mRightLandSoftAnimation->Play();
	mRightLandSoftAnimation->SetCallbackFunc(bind(&Player::SetStateIdle, this));
	//앉기 애니메이션
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
	//일어나기 애니메이션
	mLeftRiseAnimation = new Animation();
	mLeftRiseAnimation->InitFrameByStartEnd(0, 1, 1, 1, true);
	mLeftRiseAnimation->SetIsLoop(false);
	mLeftRiseAnimation->SetFrameUpdateTime(0.1f);
	mLeftRiseAnimation->Play();
	mLeftRiseAnimation->SetCallbackFunc(bind(&Player::SetStateIdle, this));

	mRightRiseAnimation = new Animation();
	mRightRiseAnimation->InitFrameByStartEnd(0, 0, 1, 0, false);
	mRightRiseAnimation->SetIsLoop(false);
	mRightRiseAnimation->SetFrameUpdateTime(0.1f);
	mRightRiseAnimation->Play();
	mRightRiseAnimation->SetCallbackFunc(bind(&Player::SetStateIdle, this));
	//구르기 애니메이션
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
	//사다리 오르내리기 애니메이션
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
	//사다리 입장 애니메이션
	mLeftLadderEnterAnimation = new Animation();
	mLeftLadderEnterAnimation->InitFrameByStartEnd(0, 1, 5, 1, true);
	mLeftLadderEnterAnimation->SetIsLoop(true);
	mLeftLadderEnterAnimation->SetFrameUpdateTime(0.1f);
	mLeftLadderEnterAnimation->Play();
	mLeftLadderEnterAnimation->SetCallbackFunc(bind(&Player::SetStateLadderUp, this));

	mRightLadderEnterAnimation = new Animation();
	mRightLadderEnterAnimation->InitFrameByStartEnd(0, 0, 5, 0, false);
	mRightLadderEnterAnimation->SetIsLoop(true);
	mRightLadderEnterAnimation->SetFrameUpdateTime(0.1f);
	mRightLadderEnterAnimation->Play();
	mRightLadderEnterAnimation->SetCallbackFunc(bind(&Player::SetStateLadderUp, this));
	//사다리 퇴장 애니메이션
	mLeftLadderLeaveAnimation = new Animation();
	mLeftLadderLeaveAnimation->InitFrameByStartEnd(0, 1, 5, 1, true);
	mLeftLadderLeaveAnimation->SetIsLoop(true);
	mLeftLadderLeaveAnimation->SetFrameUpdateTime(0.1f);
	mLeftLadderLeaveAnimation->Play();

	mRightLadderLeaveAnimation = new Animation();
	mRightLadderLeaveAnimation->InitFrameByStartEnd(0, 0, 5, 0, false);
	mRightLadderLeaveAnimation->SetIsLoop(true);
	mRightLadderLeaveAnimation->SetFrameUpdateTime(0.1f);
	mRightLadderLeaveAnimation->Play();
	//서서 활 애니메이션
	mLeftBowAnimation = new Animation();
	mLeftBowAnimation->InitFrameByStartEnd(0, 1, 5, 1, true);
	mLeftBowAnimation->SetIsLoop(true);
	mLeftBowAnimation->SetFrameUpdateTime(0.1f);
	mLeftBowAnimation->Play();

	mRightBowAnimation = new Animation();
	mRightBowAnimation->InitFrameByStartEnd(0, 0, 5, 0, false);
	mRightBowAnimation->SetIsLoop(true);
	mRightBowAnimation->SetFrameUpdateTime(0.1f);
	mRightBowAnimation->Play();
	//공중 활 애니메이션
	mLeftAirBowAnimation = new Animation();
	mLeftAirBowAnimation->InitFrameByStartEnd(0, 1, 5, 1, true);
	mLeftAirBowAnimation->SetIsLoop(true);
	mLeftAirBowAnimation->SetFrameUpdateTime(0.1f);
	mLeftAirBowAnimation->Play();

	mRightAirBowAnimation = new Animation();
	mRightAirBowAnimation->InitFrameByStartEnd(0, 0, 5, 0, false);
	mRightAirBowAnimation->SetIsLoop(true);
	mRightAirBowAnimation->SetFrameUpdateTime(0.1f);
	mRightAirBowAnimation->Play();
	//앉아 활 애니메이션
	mLeftCrouchBowAnimation = new Animation();
	mLeftCrouchBowAnimation->InitFrameByStartEnd(0, 1, 5, 1, true);
	mLeftCrouchBowAnimation->SetIsLoop(true);
	mLeftCrouchBowAnimation->SetFrameUpdateTime(0.1f);
	mLeftCrouchBowAnimation->Play();

	mRightCrouchBowAnimation = new Animation();
	mRightCrouchBowAnimation->InitFrameByStartEnd(0, 0, 5, 0, false);
	mRightCrouchBowAnimation->SetIsLoop(true);
	mRightCrouchBowAnimation->SetFrameUpdateTime(0.1f);
	mRightCrouchBowAnimation->Play();
	//첫번째 공격 애니메이션
	mLeftAttack1Animation = new Animation();
	mLeftAttack1Animation->InitFrameByStartEnd(0, 1, 6, 1, true);
	mLeftAttack1Animation->SetIsLoop(true);
	mLeftAttack1Animation->SetFrameUpdateTime(0.1f);
	mLeftAttack1Animation->Play();

	mRightAttack1Animation = new Animation();
	mRightAttack1Animation->InitFrameByStartEnd(0, 0, 6, 0, false);
	mRightAttack1Animation->SetIsLoop(true);
	mRightAttack1Animation->SetFrameUpdateTime(0.1f);
	mRightAttack1Animation->Play();
	//두번째 공격 애니메이션
	mLeftAttack2Animation = new Animation();
	mLeftAttack2Animation->InitFrameByStartEnd(0, 1, 6, 1, true);
	mLeftAttack2Animation->SetIsLoop(true);
	mLeftAttack2Animation->SetFrameUpdateTime(0.1f);
	mLeftAttack2Animation->Play();

	mRightAttack2Animation = new Animation();
	mRightAttack2Animation->InitFrameByStartEnd(0, 0, 6, 0, false);
	mRightAttack2Animation->SetIsLoop(true);
	mRightAttack2Animation->SetFrameUpdateTime(0.1f);
	mRightAttack2Animation->Play();
	//세번째 공격 애니메이션
	mLeftAttack3Animation = new Animation();
	mLeftAttack3Animation->InitFrameByStartEnd(0, 1, 10, 1, true);
	mLeftAttack3Animation->SetIsLoop(true);
	mLeftAttack3Animation->SetFrameUpdateTime(0.1f);
	mLeftAttack3Animation->Play();

	mRightAttack3Animation = new Animation();
	mRightAttack3Animation->InitFrameByStartEnd(0, 0, 10, 0, false);
	mRightAttack3Animation->SetIsLoop(true);
	mRightAttack3Animation->SetFrameUpdateTime(0.1f);
	mRightAttack3Animation->Play();
	//공중 공격 애니메이션
	mLeftAirAttackAnimation = new Animation();
	mLeftAirAttackAnimation->InitFrameByStartEnd(0, 1, 6, 1, true);
	mLeftAirAttackAnimation->SetIsLoop(true);
	mLeftAirAttackAnimation->SetFrameUpdateTime(0.1f);
	mLeftAirAttackAnimation->Play();

	mRightAirAttackAnimation = new Animation();
	mRightAirAttackAnimation->InitFrameByStartEnd(0, 0, 6, 0, false);
	mRightAirAttackAnimation->SetIsLoop(true);
	mRightAirAttackAnimation->SetFrameUpdateTime(0.1f);
	mRightAirAttackAnimation->Play();
	//피격 애니메이션
	mLeftHurtAnimation = new Animation();
	mLeftHurtAnimation->InitFrameByStartEnd(0, 1, 1, 1, true);
	mLeftHurtAnimation->SetIsLoop(true);
	mLeftHurtAnimation->SetFrameUpdateTime(0.3f);
	mLeftHurtAnimation->Play();

	mRightHurtAnimation = new Animation();
	mRightHurtAnimation->InitFrameByStartEnd(0, 0, 1, 0, false);
	mRightHurtAnimation->SetIsLoop(true);
	mRightHurtAnimation->SetFrameUpdateTime(0.3f);
	mRightHurtAnimation->Play();
	//사망 애니메이션
	mLeftDeathAnimation = new Animation();
	mLeftDeathAnimation->InitFrameByStartEnd(0, 1, 23, 1, true);
	mLeftDeathAnimation->SetIsLoop(false);
	mLeftDeathAnimation->SetFrameUpdateTime(0.2f);
	mLeftDeathAnimation->Play();

	mRightDeathAnimation = new Animation();
	mRightDeathAnimation->InitFrameByStartEnd(0, 0, 23, 0, false);
	mRightDeathAnimation->SetIsLoop(false);
	mRightDeathAnimation->SetFrameUpdateTime(0.2f);
	mRightDeathAnimation->Play();



	//값 설정
	mX = WINSIZEX / 2;
	mY = 500;
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
	//이동 프레임
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
		mState = State::LeftBrake;
		mCurrentAnimation->Stop();
		mCurrentAnimation = mLeftBrakeAnimation;
		mCurrentAnimation->Play();
		mCurrentImage = mBrakeImage;
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
		mState = State::RightBrake;
		mCurrentAnimation->Stop();
		mCurrentAnimation = mRightBrakeAnimation;
		mCurrentAnimation->Play();
		mCurrentImage = mBrakeImage;
	}
	//이동 구현
	if (Input::GetInstance()->GetKey(VK_LEFT))
	{
		if (stopmove == 0)
		{
			if (mState != State::LeftRoll)
				mX -= mSpeed * Time::GetInstance()->DeltaTime();

			if (Input::GetInstance()->GetKeyDown(VK_RIGHT))
			{
				mState = State::RightTurn;
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
			if (mState != State::RightRoll)
				mX += mSpeed * Time::GetInstance()->DeltaTime();

			if (Input::GetInstance()->GetKeyDown(VK_LEFT))
			{
				mState = State::LeftTurn;
				mCurrentAnimation->Stop();
				mCurrentAnimation = mLeftTurnAnimation;
				mCurrentAnimation->Play();
				mCurrentImage = mTurnImage;
			}
		}
	}

	//점프
	if (Input::GetInstance()->GetKeyDown(VK_SPACE))
	{
		mJumpPower = 8.f;
		mGravity = 0.2f;

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
	if (mState == State::LeftJump || mState == State::LeftFall || mState == State::RightJump || mState == State::RightFall)
	{
		mY -= mJumpPower;
		mJumpPower -= mGravity;
	}


	//앉기
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
	//일어서기
	if (Input::GetInstance()->GetKeyUp('C'))
	{
		stopmove = 0;

		if (mState == State::LeftCrouch)
		{
			mState = State::LeftRise;
			mCurrentAnimation->Stop();
			mCurrentAnimation = mLeftRiseAnimation;
			mCurrentAnimation->Play();
			mCurrentImage = mRiseImage;
		}
		if (mState == State::RightCrouch)
		{
			mState = State::RightRise;
			mCurrentAnimation->Stop();
			mCurrentAnimation = mRightRiseAnimation;
			mCurrentAnimation->Play();
			mCurrentImage = mRiseImage;
		}
	}

	//구르기
	if (Input::GetInstance()->GetKeyDown(VK_LSHIFT))
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

	//사다리!!!!!!!!!!!!!!!!!!!!!!!!!!
	RECT LadderRect;
	vector<GameObject*> LadderList = OBJECTMANAGER->GetObjectList(ObjectLayer::Ladder);
	vector<GameObject*>::iterator ladderiter = LadderList.begin();
	for (; ladderiter != LadderList.end(); ++ladderiter)
	{
		LadderRect = (*ladderiter)->GetRect();
		if (COLLISIONMANAGER->IsCollision(&mRect, &LadderRect))
		{
			if (LadderRect.left + 2 <= mX && mX <= LadderRect.right - 2)
			{
				if (Input::GetInstance()->GetKey(VK_UP))
				{
					if (mState == State::LeftIdle || mState == State::LeftRun || mState == State::LeftJump)
					{
						mState = State::LeftLadderEnter;
						mCurrentAnimation->Stop();
						mCurrentAnimation = mLeftLadderEnterAnimation;
						mCurrentAnimation->Play();
						mCurrentImage = mLadderEnterImage;
					}
					if (mState == State::RightIdle || mState == State::RightRun || mState == State::RightJump)
					{
						mState = State::RightLadderEnter;
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
						mState = State::LeftLadderEnter;
						mCurrentAnimation->Stop();
						mCurrentAnimation = mLeftLadderEnterAnimation;
						mCurrentAnimation->Play();
						mCurrentImage = mLadderEnterImage;
					}
					if (mState == State::RightIdle || mState == State::RightRun || mState == State::RightJump)
					{
						mState = State::RightLadderEnter;
						mCurrentAnimation->Stop();
						mCurrentAnimation = mRightLadderEnterAnimation;
						mCurrentAnimation->Play();
						mCurrentImage = mLadderEnterImage;
					}
				}

			}
		}
	}

	//활 공격
	if (Input::GetInstance()->GetKeyDown('X'))
	{
		Arrow* arrow = new Arrow;
		mArrowImage = IMAGEMANAGER->FindImage(L"Arrow");

		if (mState == State::LeftIdle || mState == State::LeftRun)
		{
			mCurrentAnimation->Stop();
			mCurrentAnimation = mLeftBowAnimation;
			mCurrentAnimation->Play();
			mCurrentImage = mBowImage;
			arrow->Fire(mArrowImage, mX, mY, mArrowSpeed, PI);
			arrow->SetArrowIndexY(1);
			mArrow.push_back(arrow);
		}
		if (mState == State::RightIdle || mState == State::RightRun)
		{
			mCurrentAnimation->Stop();
			mCurrentAnimation = mRightBowAnimation;
			mCurrentAnimation->Play();
			mCurrentImage = mBowImage;
			arrow->Fire(mArrowImage, mX, mY, mArrowSpeed, 0);
			arrow->SetArrowIndexY(0);
			mArrow.push_back(arrow);
		}
		if (mState == State::LeftJump || mState == State::LeftFall)
		{
			mCurrentAnimation->Stop();
			mCurrentAnimation = mLeftAirBowAnimation;
			mCurrentAnimation->Play();
			mCurrentImage = mAirBowImage;
			arrow->Fire(mArrowImage, mX, mY, mArrowSpeed, PI);
			arrow->SetArrowIndexY(1);
			mArrow.push_back(arrow);
		}
		if (mState == State::RightJump || mState == State::RightFall)
		{
			mCurrentAnimation->Stop();
			mCurrentAnimation = mRightAirBowAnimation;
			mCurrentAnimation->Play();
			mCurrentImage = mAirBowImage;
			arrow->Fire(mArrowImage, mX, mY, mArrowSpeed, 0);
			arrow->SetArrowIndexY(0);
			mArrow.push_back(arrow);
		}
		if (mState == State::LeftCrouch)
		{
			mCurrentAnimation->Stop();
			mCurrentAnimation = mLeftCrouchBowAnimation;
			mCurrentAnimation->Play();
			mCurrentImage = mCrouchBowImage;
			arrow->Fire(mArrowImage, mX - 20, mY + 18, mArrowSpeed, PI);
			arrow->SetArrowIndexY(1);
			mArrow.push_back(arrow);
		}
		if (mState == State::RightCrouch)
		{
			mCurrentAnimation->Stop();
			mCurrentAnimation = mRightCrouchBowAnimation;
			mCurrentAnimation->Play();
			mCurrentImage = mCrouchBowImage;
			arrow->Fire(mArrowImage, mX + 20, mY + 18, mArrowSpeed, 0);
			arrow->SetArrowIndexY(0);
			mArrow.push_back(arrow);
		}
	}
	for (int i = 0; i < mArrow.size(); ++i)
	{
		mArrow[i]->Update();

	}

	//검 공격 1 //이펙트 X
	if (mState != State::LeftAttack1 && mState != State::RightAttack1 && mState != State::LeftAttack2 && mState != State::RightAttack2 && mState != State::LeftAttack3 && mState != State::RightAttack3)
	{
		if (Input::GetInstance()->GetKeyDown('Z'))
		{
			if (mState == State::LeftIdle || mState == State::LeftRun)
			{
				mState = State::LeftAttack1;
				mCurrentAnimation->Stop();
				mCurrentAnimation = mLeftAttack1Animation;
				mCurrentAnimation->Play();
				mCurrentImage = mAttack1Image;
			}
			if (mState == State::RightIdle || mState == State::RightRun)
			{
				mState = State::RightAttack1;
				mCurrentAnimation->Stop();
				mCurrentAnimation = mRightAttack1Animation;
				mCurrentAnimation->Play();
				mCurrentImage = mAttack1Image;
			}
			if (mState == State::LeftJump || mState == State::LeftFall)
			{
				mState = State::LeftAirAttack;
				mCurrentAnimation->Stop();
				mCurrentAnimation = mLeftAirAttackAnimation;
				mCurrentAnimation->Play();
				mCurrentImage = mAirAttackImage;
			}
			if (mState == State::RightJump || mState == State::RightFall)
			{
				mState = State::RightAirAttack;
				mCurrentAnimation->Stop();
				mCurrentAnimation = mRightAirAttackAnimation;
				mCurrentAnimation->Play();
				mCurrentImage = mAirAttackImage;
			}
			mAttackDamage = 10;
		}
	}
	//검 공격 2
	if (mState == State::LeftAttack1 || mState == State::RightAttack1)
	{
		if (Input::GetInstance()->GetKeyDown('Z'))
		{
			if (mState == State::LeftAttack1)
			{
				if (mCurrentAnimation->GetNowFrameX() == 0 || mCurrentAnimation->GetNowFrameX() == 1 || mCurrentAnimation->GetNowFrameX() == 2)
				{
					mState = State::LeftAttack2;
					mCurrentAnimation->Stop();
					mCurrentAnimation = mLeftAttack2Animation;
					mCurrentAnimation->Play();
					mCurrentImage = mAttack2Image;
				}
			}
			if (mState == State::RightAttack1)
			{
				if (mCurrentAnimation->GetNowFrameX() == 4 || mCurrentAnimation->GetNowFrameX() == 5 || mCurrentAnimation->GetNowFrameX() == 6)
				{
					mState = State::RightAttack2;
					mCurrentAnimation->Stop();
					mCurrentAnimation = mRightAttack2Animation;
					mCurrentAnimation->Play();
					mCurrentImage = mAttack2Image;
				}
			}
			mAttackDamage = 15;
		}
	}
	//검 공격 3
	if (mState == State::LeftAttack2 || mState == State::RightAttack2)
	{
		if (Input::GetInstance()->GetKeyDown('Z'))
		{
			if (mState == State::LeftAttack2)
			{
				if (mCurrentAnimation->GetNowFrameX() == 0 || mCurrentAnimation->GetNowFrameX() == 1 || mCurrentAnimation->GetNowFrameX() == 2)
				{
					mState = State::LeftAttack3;
					mCurrentAnimation->Stop();
					mCurrentAnimation = mLeftAttack3Animation;
					mCurrentAnimation->Play();
					mCurrentImage = mAttack3Image;
				}
			}
			if (mState == State::RightAttack2)
			{
				if (mCurrentAnimation->GetNowFrameX() == 4 || mCurrentAnimation->GetNowFrameX() == 5 || mCurrentAnimation->GetNowFrameX() == 6)
				{
					mState = State::RightAttack3;
					mCurrentAnimation->Stop();
					mCurrentAnimation = mRightAttack3Animation;
					mCurrentAnimation->Play();
					mCurrentImage = mAttack3Image;
				}
			}
			mAttackDamage = 20;
		}
	}
	//피격 및 사망
	if (mHp <= 0)
	{
		stopmove = 1;
		if (mState == State::LeftIdle || mState == State::LeftRun)
		{
			mState = State::Death;
			mCurrentAnimation->Stop();
			mCurrentAnimation = mLeftDeathAnimation;
			mCurrentAnimation->Play();
			mCurrentImage = mDeathImage;
		}
		if (mState == State::RightIdle || mState == State::RightRun)
		{
			mState = State::Death;
			mCurrentAnimation->Stop();
			mCurrentAnimation = mRightDeathAnimation;
			mCurrentAnimation->Play();
			mCurrentImage = mDeathImage;
		}
	}


	//땅에 닿았을때 중력 X
	RECT PlatformRect;
	vector<GameObject*> PlatformList = OBJECTMANAGER->GetObjectList(ObjectLayer::Platform);
	vector<GameObject*>::iterator platformiter = PlatformList.begin();
	for (; platformiter != PlatformList.end(); ++platformiter)
	{
		PlatformRect = (*platformiter)->GetRect();
		if (mRect.bottom >= PlatformRect.top)
		{
			if (mState == State::LeftFall)
			{
				mState = State::LeftLandSoft;
				mCurrentAnimation->Stop();
				mCurrentAnimation = mLeftLandSoftAnimation;
				mCurrentAnimation->Play();
				mCurrentImage = mLandSoftImage;
			}
			if (mState == State::RightFall)
			{
				mState = State::RightLandSoft;
				mCurrentAnimation->Stop();
				mCurrentAnimation = mRightLandSoftAnimation;
				mCurrentAnimation->Play();
				mCurrentImage = mLandSoftImage;
			}
		}
	}
	

	if (stopmove == 0)
	{
		mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	}
	mCurrentAnimation->Update();
	 
	//RECT mPrevRect;
	mRect = *(COLLISIONMANAGER->CollideWithPlatform(&mRect, &mPrevRect, mSizeX, mSizeY));

	mPrevRect = mRect;
}

void Player::Render(HDC hdc)
{
	CAMERAMANAGER->GetMainCamera()->RenderRectInCamera(hdc, mRect);
	CameraManager::GetInstance()->GetMainCamera()->AlphaScaleFrameRender(hdc, mCurrentImage, (int)mRect.left, (int)mRect.top, mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY(), (int)mSizeX, (int)mSizeY, 1.f);

	for (int i = 0; i < mArrow.size(); ++i)
	{
		mArrow[i]->Render(hdc);
	}
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
	if (mState == State::LeftRoll || mState == State::LeftRise || mState == State::LeftBrake || mState == State::LeftLandSoft)
	{
		mState = State::LeftIdle;
		mCurrentAnimation->Stop();
		mCurrentAnimation = mLeftIdleAnimation;
		mCurrentAnimation->Play();
		mCurrentImage = mIdleImage;
	}
	else if (mState == State::RightRoll || mState == State::RightRise || mState == State::RightBrake || mState == State::RightLandSoft)
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
	if (mState == State::LeftLadderEnter || mState == State::RightLadderEnter)
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
	if (mState == State::LeftLadderEnter || mState == State::RightLadderEnter)
	{
		mState = State::LadderDown;
		mCurrentAnimation->Stop();
		mCurrentAnimation = mLadderDownAnimation;
		mCurrentAnimation->Play();
		mCurrentImage = mLadderDownImage;
	}
}
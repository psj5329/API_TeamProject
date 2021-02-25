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
	FindPlayerImage();

	ReadyPlayerAnimation();

	InitPlayerVar(); // 플레이어가 가진 각종 변수들 초기화 하는 함수
}

void Player::Release()
{
	SafeDeletePlayerAnimation();
}

void Player::Update()
{
	// 이동 프레임
	if (Input::GetInstance()->GetKeyDown(VK_LEFT))
	{
		//mState = State::LeftRun;
		mDirection = Direction::Left;
		mState = PlayerState::Run;
		mCurrentAnimation->Stop();
		mCurrentAnimation = mLeftRunStartAnimation;
		mCurrentAnimation->Play();
		mCurrentImage = mRunImage;
	}
	if (Input::GetInstance()->GetKeyUp(VK_LEFT))
	{
		//mState = State::LeftBrake;
		mDirection = Direction::Left;
		mState = PlayerState::Brake;
		mCurrentAnimation->Stop();
		mCurrentAnimation = mLeftBrakeAnimation;
		mCurrentAnimation->Play();
		mCurrentImage = mBrakeImage;
	}
	if (Input::GetInstance()->GetKeyDown(VK_RIGHT))
	{
		//mState = State::RightRun;
		mDirection = Direction::Right;
		mState = PlayerState::Run;
		mCurrentAnimation->Stop();
		mCurrentAnimation = mRightRunStartAnimation;
		mCurrentAnimation->Play();
		mCurrentImage = mRunImage;
	}
	if (Input::GetInstance()->GetKeyUp(VK_RIGHT))
	{
		//mState = State::RightBrake;
		mDirection = Direction::Right;
		mState = PlayerState::Brake;
		mCurrentAnimation->Stop();
		mCurrentAnimation = mRightBrakeAnimation;
		mCurrentAnimation->Play();
		mCurrentImage = mBrakeImage;
	}

	// 이동 구현
	if (Input::GetInstance()->GetKey(VK_LEFT))
	{	
		if (stopmove == 0)
		{
			mX -= mSpeed * Time::GetInstance()->DeltaTime();
		}

		if (Input::GetInstance()->GetKeyDown(VK_RIGHT))
		{
			//mState = State::RightTurn;
			mDirection = Direction::Right;
			mState = PlayerState::Turn;
			mCurrentAnimation->Stop();
			mCurrentAnimation = mRightTurnAnimation;
			mCurrentAnimation->Play();
			mCurrentImage = mTurnImage;
		
		}
	}
	if (Input::GetInstance()->GetKey(VK_RIGHT))
	{	
		if (stopmove == 0)
		{
			mX += mSpeed * Time::GetInstance()->DeltaTime();
		}

		if (Input::GetInstance()->GetKeyDown(VK_LEFT))
		{
			//mState = State::LeftTurn;
			mDirection = Direction::Left;
			mState = PlayerState::Turn;
			mCurrentAnimation->Stop();
			mCurrentAnimation = mLeftTurnAnimation;
			mCurrentAnimation->Play();
			mCurrentImage = mTurnImage;
		}
	}

	// 앉기
	if (Input::GetInstance()->GetKey('C'))
	{
		//if (mState == State::LeftIdle || mState == State::LeftRun)
		if (mDirection == Direction::Left)
		{
			if (mState == PlayerState::Idle || mState == PlayerState::Run)
			{
				//mState = State::LeftCrouch;
				mState = PlayerState::Crouch;
				mCurrentAnimation->Stop();
				mCurrentAnimation = mLeftCrouchAnimation;
				mCurrentAnimation->Play();
				mCurrentImage = mCrouchImage;
			}
		}
		//if (mState == State::RightIdle || mState == State::RightRun)
		if (mDirection == Direction::Right)
		{
			if (mState == PlayerState::Idle || mState == PlayerState::Run)
			{
				//mState = State::RightCrouch;
				mState = PlayerState::Crouch;
				mCurrentAnimation->Stop();
				mCurrentAnimation = mRightCrouchAnimation;
				mCurrentAnimation->Play();
				mCurrentImage = mCrouchImage;
			}
		}
	}

	// 일어서기
	if (Input::GetInstance()->GetKeyUp('C'))
	{
		if (mState == PlayerState::Crouch)
		{
			//if (mState == State::LeftCrouch)
			if (mDirection == Direction::Left)
			{
				//mState = State::LeftRise;
				mState = PlayerState::Rise;
				mCurrentAnimation->Stop();
				mCurrentAnimation = mLeftRiseAnimation;
				mCurrentAnimation->Play();
				mCurrentImage = mRiseImage;
			}
			//if (mState == State::RightCrouch)
			if (mDirection == Direction::Right)
			{
				//mState = State::RightRise;
				mState = PlayerState::Rise;
				mCurrentAnimation->Stop();
				mCurrentAnimation = mRightRiseAnimation;
				mCurrentAnimation->Play();
				mCurrentImage = mRiseImage;
			}
		}
	}

	// 구르기
	if (Input::GetInstance()->GetKeyDown(VK_LSHIFT))
	{
		//if (mState == State::LeftIdle || mState == State::LeftRun)
		if(mDirection == Direction::Left)
		{
			if (mState == PlayerState::Idle || mState == PlayerState::Run)
			{
				//mState = State::LeftRoll;
				mState = PlayerState::Roll;
				mCurrentAnimation->Stop();
				mCurrentAnimation = mLeftRollAnimation;
				mCurrentAnimation->Play();
				mCurrentImage = mRollImage;
			}
		}
		//if (mState == State::RightIdle || mState == State::RightRun)
		if (mDirection == Direction::Right)
		{
			if (mState == PlayerState::Idle || mState == PlayerState::Run)
			{
				//mState = State::RightRoll;
				mState = PlayerState::Roll;
				mCurrentAnimation->Stop();
				mCurrentAnimation = mRightRollAnimation;
				mCurrentAnimation->Play();
				mCurrentImage = mRollImage;
			}
		}
	}

	if (mState == PlayerState::Roll)
	{
		//if (mState == State::LeftRoll)
		if (mDirection == Direction::Left)
		{
			mX -= mSpeed * Time::GetInstance()->DeltaTime() * 1.3f;
			mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
		}
		//if (mState == State::RightRoll)
		if (mDirection == Direction::Right)
		{
			mX += mSpeed * Time::GetInstance()->DeltaTime() * 1.3f;
			mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
		}
	}

	// 사다리!!!!!!!!!!!!!!!!!!!!
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
					//if (mState == State::LeftIdle || mState == State::LeftRun || mState == State::LeftJump)
					if (mDirection == Direction::Left)
					{
						if (mState == PlayerState::Idle || mState == PlayerState::Run || mState == PlayerState::Jump)
						{
							//mState = State::LeftLadderEnter;
							mState = PlayerState::LadderEnter;
							mCurrentAnimation->Stop();
							mCurrentAnimation = mLeftLadderEnterAnimation;
							mCurrentAnimation->Play();
							mCurrentImage = mLadderEnterImage;
						}
					}
					//if (mState == State::RightIdle || mState == State::RightRun || mState == State::RightJump)
					if (mDirection == Direction::Right)
					{
						if (mState == PlayerState::Idle || mState == PlayerState::Run || mState == PlayerState::Jump)
						{
							//mState = State::RightLadderEnter;
							mState = PlayerState::LadderEnter;
							mCurrentAnimation->Stop();
							mCurrentAnimation = mRightLadderEnterAnimation;
							mCurrentAnimation->Play();
							mCurrentImage = mLadderEnterImage;
						}
					}
				}
				if (Input::GetInstance()->GetKey(VK_DOWN))
				{
					//if (mState == State::LeftIdle || mState == State::LeftRun || mState == State::LeftJump)
					if (mDirection == Direction::Left)
					{
						if (mState == PlayerState::Idle || mState == PlayerState::Run || mState == PlayerState::Jump)
						{
							//mState = State::LeftLadderEnter;
							mState = PlayerState::LadderEnter;
							mCurrentAnimation->Stop();
							mCurrentAnimation = mLeftLadderEnterAnimation;
							mCurrentAnimation->Play();
							mCurrentImage = mLadderEnterImage;
						}
					}
					//if (mState == State::RightIdle || mState == State::RightRun || mState == State::RightJump)
					if (mDirection == Direction::Right)
					{
						if (mState == PlayerState::Idle || mState == PlayerState::Run || mState == PlayerState::Jump)
						{
							//mState = State::RightLadderEnter;
							mState = PlayerState::LadderEnter;
							mCurrentAnimation->Stop();
							mCurrentAnimation = mRightLadderEnterAnimation;
							mCurrentAnimation->Play();
							mCurrentImage = mLadderEnterImage;
						}
					}
				}
			}
		}
	}

	// 활 공격
	if (Input::GetInstance()->GetKeyDown('X'))
	{
		Arrow* arrow = new Arrow;
		mArrowImage = IMAGEMANAGER->FindImage(L"Arrow");

		if (mDirection == Direction::Left)
		{
			//if (mState == State::LeftIdle || mState == State::LeftRun)
			if (mState == PlayerState::Idle || mState == PlayerState::Run)
			{
				//mState = State::LeftBow;
				mState = PlayerState::Bow;
				mCurrentAnimation->Stop();
				mCurrentAnimation = mLeftBowAnimation;
				mCurrentAnimation->Play();
				mCurrentImage = mBowImage;
				arrow->Fire(mArrowImage, mX, mY, mArrowSpeed, PI);
				arrow->SetArrowIndexY(1);
				mArrow.push_back(arrow);
			}
			//if (mState == State::LeftJump || mState == State::LeftFall)
			if (mState == PlayerState::Jump || mState == PlayerState::Fall)
			{
				//mState = State::LeftAirBow;
				mState = PlayerState::AirBow;
				mCurrentAnimation->Stop();
				mCurrentAnimation = mLeftAirBowAnimation;
				mCurrentAnimation->Play();
				mCurrentImage = mAirBowImage;
				arrow->Fire(mArrowImage, mX, mY, mArrowSpeed, PI);
				arrow->SetArrowIndexY(1);
				mArrow.push_back(arrow);
			}
			//if (mState == State::LeftCrouch)
			if (mState == PlayerState::Crouch)
			{
				//mState = State::LeftCrouchBow;
				mState = PlayerState::CrouchBow;
				mCurrentAnimation->Stop();
				mCurrentAnimation = mLeftCrouchBowAnimation;
				mCurrentAnimation->Play();
				mCurrentImage = mCrouchBowImage;
				arrow->Fire(mArrowImage, mX - 20, mY + 18, mArrowSpeed, PI);
				arrow->SetArrowIndexY(1);
				mArrow.push_back(arrow);
			}
		}
		if (mDirection == Direction::Right)
		{
			//if (mState == State::RightIdle || mState == State::RightRun)
			if (mState == PlayerState::Idle || mState == PlayerState::Run)
			{
				//mState = State::RightBow;
				mState = PlayerState::Bow;
				mCurrentAnimation->Stop();
				mCurrentAnimation = mRightBowAnimation;
				mCurrentAnimation->Play();
				mCurrentImage = mBowImage;
				arrow->Fire(mArrowImage, mX, mY, mArrowSpeed, 0);
				arrow->SetArrowIndexY(0);
				mArrow.push_back(arrow);
			}
			//if (mState == State::RightJump || mState == State::RightFall)
			if (mState == PlayerState::Jump || mState == PlayerState::Fall)
			{
				//mState = State::RightAirBow;
				mState = PlayerState::AirBow;
				mCurrentAnimation->Stop();
				mCurrentAnimation = mRightAirBowAnimation;
				mCurrentAnimation->Play();
				mCurrentImage = mAirBowImage;
				arrow->Fire(mArrowImage, mX, mY, mArrowSpeed, 0);
				arrow->SetArrowIndexY(0);
				mArrow.push_back(arrow);
			}
			//if (mState == State::RightCrouch)
			if (mState == PlayerState::Crouch)
			{
				//mState = State::RightCrouchBow;
				mState = PlayerState::CrouchBow;
				mCurrentAnimation->Stop();
				mCurrentAnimation = mRightCrouchBowAnimation;
				mCurrentAnimation->Play();
				mCurrentImage = mCrouchBowImage;
				arrow->Fire(mArrowImage, mX + 20, mY + 18, mArrowSpeed, 0);
				arrow->SetArrowIndexY(0);
				mArrow.push_back(arrow);
			}
		}
	}
	for (int i = 0; i < mArrow.size(); ++i)
	{
		mArrow[i]->Update();
	}

	// 검 공격 1 // 이펙트 X
	//if (mState != State::LeftAttack1 && mState != State::RightAttack1 && mState != State::LeftAttack2 && mState != State::RightAttack2 && mState != State::LeftAttack3 && mState != State::RightAttack3)
	if(mState != PlayerState::Attack1 || mState != PlayerState::Attack2 || mState != PlayerState::Attack3)
	{
		if (Input::GetInstance()->GetKeyDown('Z'))
		{
			if (mDirection == Direction::Left)
			{
				//if (mState == State::LeftIdle || mState == State::LeftRun)
				if (mState == PlayerState::Idle || mState == PlayerState::Run)
				{
					//mState = State::LeftAttack1;
					mState = PlayerState::Attack1;
					mCurrentAnimation->Stop();
					mCurrentAnimation = mLeftAttack1Animation;
					mCurrentAnimation->Play();
					mCurrentImage = mAttack1Image;
				}
				//if (mState == State::LeftJump || mState == State::LeftFall)
				if (mState == PlayerState::Jump || mState == PlayerState::Fall)
				{
					//mState = State::LeftAirAttack;
					mState = PlayerState::AirAttack;
					mCurrentAnimation->Stop();
					mCurrentAnimation = mLeftAirAttackAnimation;
					mCurrentAnimation->Play();
					mCurrentImage = mAirAttackImage;
				}
			}
			if (mDirection == Direction::Right)
			{
				//if (mState == State::RightIdle || mState == State::RightRun)
				if (mState == PlayerState::Idle || mState == PlayerState::Run)
				{
					//mState = State::RightAttack1;
					mState = PlayerState::Attack1;
					mCurrentAnimation->Stop();
					mCurrentAnimation = mRightAttack1Animation;
					mCurrentAnimation->Play();
					mCurrentImage = mAttack1Image;
				}
				//if (mState == State::RightJump || mState == State::RightFall)
				if (mState == PlayerState::Jump || mState == PlayerState::Fall)
				{
					//mState = State::RightAirAttack;
					mState = PlayerState::AirAttack;
					mCurrentAnimation->Stop();
					mCurrentAnimation = mRightAirAttackAnimation;
					mCurrentAnimation->Play();
					mCurrentImage = mAirAttackImage;
				}
			}
			mAttackDamage = 10;
		}
	}

	// 검 공격 2
	//if (mState == State::LeftAttack1 || mState == State::RightAttack1)
	if (mState == PlayerState::Attack1)
	{
		if (Input::GetInstance()->GetKeyDown('Z'))
		{
			//if (mState == State::LeftAttack1)
			if (mDirection == Direction::Left)
			{
				if (mCurrentAnimation->GetNowFrameX() == 0 || mCurrentAnimation->GetNowFrameX() == 1 || mCurrentAnimation->GetNowFrameX() == 2)
				{
					//mState = State::LeftAttack2;
					mState = PlayerState::Attack2;
					mCurrentAnimation->Stop();
					mCurrentAnimation = mLeftAttack2Animation;
					mCurrentAnimation->Play();
					mCurrentImage = mAttack2Image;
				}
			}
			//if (mState == State::RightAttack1)
			if (mDirection == Direction::Right)
			{
				if (mCurrentAnimation->GetNowFrameX() == 4 || mCurrentAnimation->GetNowFrameX() == 5 || mCurrentAnimation->GetNowFrameX() == 6)
				{
					//mState = State::RightAttack2;
					mState = PlayerState::Attack2;
					mCurrentAnimation->Stop();
					mCurrentAnimation = mRightAttack2Animation;
					mCurrentAnimation->Play();
					mCurrentImage = mAttack2Image;
				}
			}
			mHitAttack = true;
			mAttackDamage = 15;
		}
	}

	// 검 공격 3
	//if (mState == State::LeftAttack2 || mState == State::RightAttack2)
	if (mState == PlayerState::Attack2)
	{
		if (Input::GetInstance()->GetKeyDown('Z'))
		{
			//if (mState == State::LeftAttack2)
			if (mDirection == Direction::Left)
			{
				if (mCurrentAnimation->GetNowFrameX() == 0 || mCurrentAnimation->GetNowFrameX() == 1 || mCurrentAnimation->GetNowFrameX() == 2)
				{
					//mState = State::LeftAttack3;
					mState = PlayerState::Attack3;
					mCurrentAnimation->Stop();
					mCurrentAnimation = mLeftAttack3Animation;
					mCurrentAnimation->Play();
					mCurrentImage = mAttack3Image;
				}
			}
			//if (mState == State::RightAttack2)
			if (mDirection == Direction::Right)
			{
				if (mCurrentAnimation->GetNowFrameX() == 4 || mCurrentAnimation->GetNowFrameX() == 5 || mCurrentAnimation->GetNowFrameX() == 6)
				{
					//mState = State::RightAttack3;
					mState = PlayerState::Attack3;
					mCurrentAnimation->Stop();
					mCurrentAnimation = mRightAttack3Animation;
					mCurrentAnimation->Play();
					mCurrentImage = mAttack3Image;
				}
			}
			mHitAttack = true;
			mAttackDamage = 20;
		}
	}

	// Hp 회복 아이템
	if (mHp > 0)
	{
		if (Input::GetInstance()->GetKeyDown('Q'))
		{
			//if (mState == State::LeftIdle || mState == State::RightIdle)
			if (mState == PlayerState::Idle)
				mHp + 30; // <- 이거 되는 문장인가요?
		}
	}

	// 피격 및 사망
	if (mHp <= 0)
	{
		if (mDirection == Direction::Left)
		{
			//if (mState == State::LeftIdle || mState == State::LeftRun)
			if (mState == PlayerState::Idle || mState == PlayerState::Run)
			{
				//mState = State::Death;
				mState = PlayerState::Death;
				mCurrentAnimation->Stop();
				mCurrentAnimation = mLeftDeathAnimation;
				mCurrentAnimation->Play();
				mCurrentImage = mDeathImage;
			}
		}
		if (mDirection == Direction::Right)
		{
			//if (mState == State::RightIdle || mState == State::RightRun)
			if (mState == PlayerState::Idle || mState == PlayerState::Run)
			{
				//mState = State::Death;
				mState = PlayerState::Death;
				mCurrentAnimation->Stop();
				mCurrentAnimation = mRightDeathAnimation;
				mCurrentAnimation->Play();
				mCurrentImage = mDeathImage;
			}
		}
	}
  
//	if (Input::GetInstance()->GetKeyDown(VK_SPACE))
	// 플랫폼 충돌
	if (COLLISIONMANAGER->IsCollideWithPlatform(&mRect))
	{
		mJumpPower = 0;
		mGravity = 0;
		//if (mState == State::LeftFall)
		if (mDirection == Direction::Left)
		{
			if (mState == PlayerState::Fall)
			{
				//mState = State::LeftLandSoft;
				mState = PlayerState::LandSoft;
				mCurrentAnimation->Stop();
				mCurrentAnimation = mLeftLandSoftAnimation;
				mCurrentAnimation->Play();
				mCurrentImage = mLandSoftImage;
			}
		}
		//if (mState == State::RightFall)
		if (mDirection == Direction::Right)
		{
			if (mState == PlayerState::Fall)
			{
				//mState = State::RightLandSoft;
				mState = PlayerState::LandSoft;
				mCurrentAnimation->Stop();
				mCurrentAnimation = mRightLandSoftAnimation;
				mCurrentAnimation->Play();
				mCurrentImage = mLandSoftImage;
			}
		}
	}
	else
	{
		mGravity = 0.2f;
		if (mState == PlayerState::Idle || mState == PlayerState::Run || mState == PlayerState::Brake)
		{
			//if (mState == State::LeftIdle || mState == State::LeftRun || mState == State::LeftBrake)
			if (mDirection == Direction::Left)
			{
				//mState = State::LeftFall;
				mState = PlayerState::Fall;
				mCurrentAnimation->Stop();
				mCurrentAnimation = mLeftFallAnimation;
				mCurrentAnimation->Play();
				mCurrentImage = mFallImage;
			}
			//if (mState == State::RightIdle || mState == State::RightRun || mState == State::RightBrake)
			if (mDirection == Direction::Right)
			{
				//mState = State::RightFall;
				mState = PlayerState::Fall;
				mCurrentAnimation->Stop();
				mCurrentAnimation = mRightFallAnimation;
				mCurrentAnimation->Play();
				mCurrentImage = mFallImage;
			}
		}
	}

	// 점프
	if (Input::GetInstance()->GetKeyDown(VK_SPACE))
	{
		mJumpPower = 8.f;
		mGravity = 0.2f;

		if (mDirection == Direction::Left)
		{
			//if (mState == State::LeftIdle || mState == State::LeftRun)
			if (mState == PlayerState::Idle || mState == PlayerState::Run)
			{
				//mState = State::LeftJump;
				mState = PlayerState::Jump;
				mCurrentAnimation->Stop();
				mCurrentAnimation = mLeftJumpAnimation;
				mCurrentAnimation->Play();
				mCurrentImage = mJumpImage;
			}
		}
		if (mDirection == Direction::Right)
		{
			//if (mState == State::RightIdle || mState == State::RightRun)
			if (mState == PlayerState::Idle || mState == PlayerState::Run)
			{
				//mState = State::RightJump;
				mState = PlayerState::Jump;
				mCurrentAnimation->Stop();
				mCurrentAnimation = mRightJumpAnimation;
				mCurrentAnimation->Play();
				mCurrentImage = mJumpImage;
			}
		}
	}
	//if (mState == State::LeftJump || mState == State::RightJump)
	if (mState == PlayerState::Jump)
	{
		//if (mJumpPower < 0 && mState == State::LeftJump)
		if (mJumpPower < 0 && mDirection == Direction::Left)
		{
			//mState = State::LeftFall;
			mState = PlayerState::Fall;
			mCurrentAnimation->Stop();
			mCurrentAnimation = mLeftFallAnimation;
			mCurrentAnimation->Play();
			mCurrentImage = mFallImage;
		}
		//if (mJumpPower < 0 && mState == State::RightJump)
		if (mJumpPower < 0 && mDirection == Direction::Right)
		{
			//mState = State::RightFall;
			mState = PlayerState::Fall;
			mCurrentAnimation->Stop();
			mCurrentAnimation = mRightFallAnimation;
			mCurrentAnimation->Play();
			mCurrentImage = mFallImage;
		}
	}
	//if (mState == State::LeftFall || mState == State::RightFall || mState == State::LeftJump || mState == State::RightJump)
	if(mState == PlayerState::Fall || mState == PlayerState::Jump)
	{
		mY -= mJumpPower;
		mJumpPower -= mGravity;
	}

	// 움직임 제한
	//if (mState == State::LeftCrouch || mState == State::RightCrouch || mState == State::LeftLandSoft || mState == State::RightLandSoft || 
	//	mState == State::LeftAttack1 || mState == State::LeftAttack2 || mState == State::LeftAttack3) // <- 혹시 right attack 1~3 뺀 이유가 있는지?
	if(mState == PlayerState::Crouch || mState == PlayerState::LandSoft || mState == PlayerState::Attack1 || mState == PlayerState::Attack2 || mState == PlayerState::Attack3)
	{
		stopmove = 1;
	}
	//if (mState == State::LeftIdle || mState == State::RightIdle)
	if (mState == PlayerState::Idle)
	{
		stopmove = 0;
	}
	if (stopmove == 0)
	{
		mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	}
	mCurrentAnimation->Update();
	 
	//RECT mPrevRect;
	mRect = *(COLLISIONMANAGER->CollideWithPlatform(&mRect, &mPrevRect, mSizeX, mSizeY));
	mX = (mRect.left + mRect.right) / 2;
	mY = (mRect.bottom + mRect.top) / 2;
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

	wstring str3 = L"mX:" + to_wstring(mX);
	TextOut(hdc, _mousePosition.x + 10, _mousePosition.y + 10, str3.c_str(), str3.length());
	wstring str4 = L"mY:" + to_wstring(mY);
	TextOut(hdc, _mousePosition.x + 10, _mousePosition.y + 30, str4.c_str(), str4.length());
	wstring str5 = L"Gravity:" + to_wstring(mGravity);
	TextOut(hdc, _mousePosition.x + 10, _mousePosition.y + 50, str5.c_str(), str5.length());
	wstring str6 = L"jumppower" + to_wstring(mJumpPower);
	TextOut(hdc, _mousePosition.x + 10, _mousePosition.y + 70, str6.c_str(), str6.length());

}

void Player::FindPlayerImage()
{
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
}

void Player::ReadyPlayerAnimation()
{
	// 스탠드 애니메이션
	mLeftIdleAnimation = new Animation();
	mLeftIdleAnimation->InitFrameByStartEnd(0, 1, 5, 1, true);
	mLeftIdleAnimation->SetIsLoop(true);
	mLeftIdleAnimation->SetFrameUpdateTime(0.2f);
//	mLeftIdleAnimation->Play();

	mRightIdleAnimation = new Animation();
	mRightIdleAnimation->InitFrameByStartEnd(0, 0, 5, 0, false);
	mRightIdleAnimation->SetIsLoop(true);
	mRightIdleAnimation->SetFrameUpdateTime(0.2f);
//	mRightIdleAnimation->Play();

	// 이동 애니메이션
	mLeftRunStartAnimation = new Animation();
	mLeftRunStartAnimation->InitFrameByStartEnd(8, 1, 9, 1, true);
	mLeftRunStartAnimation->SetIsLoop(false);
	mLeftRunStartAnimation->SetFrameUpdateTime(0.1f);
//	mLeftRunStartAnimation->Play();
	mLeftRunStartAnimation->SetCallbackFunc(bind(&Player::SetStateRun, this));

	mLeftRunAnimation = new Animation();
	mLeftRunAnimation->InitFrameByStartEnd(0, 1, 7, 1, true);
	mLeftRunAnimation->SetIsLoop(true);
	mLeftRunAnimation->SetFrameUpdateTime(0.1f);
//	mLeftRunAnimation->Play();

	mRightRunStartAnimation = new Animation();
	mRightRunStartAnimation->InitFrameByStartEnd(0, 0, 1, 0, false);
	mRightRunStartAnimation->SetIsLoop(false);
	mRightRunStartAnimation->SetFrameUpdateTime(0.1f);
//	mRightRunStartAnimation->Play();
	mRightRunStartAnimation->SetCallbackFunc(bind(&Player::SetStateRun, this));

	mRightRunAnimation = new Animation();
	mRightRunAnimation->InitFrameByStartEnd(2, 0, 9, 0, false);
	mRightRunAnimation->SetIsLoop(true);
	mRightRunAnimation->SetFrameUpdateTime(0.1f);
//	mRightRunAnimation->Play();

	// 브레이크 애니메이션
	mLeftBrakeAnimation = new Animation();
	mLeftBrakeAnimation->InitFrameByStartEnd(0, 1, 6, 1, true);
	mLeftBrakeAnimation->SetIsLoop(true);
	mLeftBrakeAnimation->SetFrameUpdateTime(0.05f);
//	mLeftBrakeAnimation->Play();
	mLeftBrakeAnimation->SetCallbackFunc(bind(&Player::SetStateIdle, this));

	mRightBrakeAnimation = new Animation();
	mRightBrakeAnimation->InitFrameByStartEnd(0, 0, 6, 0, false);
	mRightBrakeAnimation->SetIsLoop(true);
	mRightBrakeAnimation->SetFrameUpdateTime(0.05f);
//	mRightBrakeAnimation->Play();
	mRightBrakeAnimation->SetCallbackFunc(bind(&Player::SetStateIdle, this));

	// 방향 전환 애니메이션
	mLeftTurnAnimation = new Animation();
	mLeftTurnAnimation->InitFrameByStartEnd(0, 1, 2, 1, true);
	mLeftTurnAnimation->SetIsLoop(false);
	mLeftTurnAnimation->SetFrameUpdateTime(0.1f);
//	mLeftTurnAnimation->Play();

	mRightTurnAnimation = new Animation();
	mRightTurnAnimation->InitFrameByStartEnd(0, 0, 2, 0, false);
	mRightTurnAnimation->SetIsLoop(false);
	mRightTurnAnimation->SetFrameUpdateTime(0.1f);
//	mRightTurnAnimation->Play();

	// 점프 애니메이션
	mLeftJumpAnimation = new Animation();
	mLeftJumpAnimation->InitFrameByStartEnd(0, 1, 2, 1, true);
	mLeftJumpAnimation->SetIsLoop(true);
	mLeftJumpAnimation->SetFrameUpdateTime(0.2f);
//	mLeftJumpAnimation->Play();

	mRightJumpAnimation = new Animation();
	mRightJumpAnimation->InitFrameByStartEnd(0, 0, 2, 0, false);
	mRightJumpAnimation->SetIsLoop(true);
	mRightJumpAnimation->SetFrameUpdateTime(0.2f);
//	mRightJumpAnimation->Play();

	// 점프 하강 애니메이션
	mLeftFallAnimation = new Animation();
	mLeftFallAnimation->InitFrameByStartEnd(0, 1, 4, 1, true);
	mLeftFallAnimation->SetIsLoop(false);
	mLeftFallAnimation->SetFrameUpdateTime(0.2f);
//	mLeftFallAnimation->Play();

	mRightFallAnimation = new Animation();
	mRightFallAnimation->InitFrameByStartEnd(0, 0, 4, 0, false);
	mRightFallAnimation->SetIsLoop(false);
	mRightFallAnimation->SetFrameUpdateTime(0.2f);
//	mRightFallAnimation->Play();

	// 약한 착지 애니메이션
	mLeftLandSoftAnimation = new Animation();
	mLeftLandSoftAnimation->InitFrameByStartEnd(0, 1, 3, 1, true);
	mLeftLandSoftAnimation->SetIsLoop(true);
	mLeftLandSoftAnimation->SetFrameUpdateTime(0.1f);
//	mLeftLandSoftAnimation->Play();
	mLeftLandSoftAnimation->SetCallbackFunc(bind(&Player::SetStateIdle, this));

	mRightLandSoftAnimation = new Animation();
	mRightLandSoftAnimation->InitFrameByStartEnd(0, 0, 3, 0, false);
	mRightLandSoftAnimation->SetIsLoop(true);
	mRightLandSoftAnimation->SetFrameUpdateTime(0.1f);
//	mRightLandSoftAnimation->Play();
	mRightLandSoftAnimation->SetCallbackFunc(bind(&Player::SetStateIdle, this));

	// 앉기 애니메이션
	mLeftCrouchAnimation = new Animation();
	mLeftCrouchAnimation->InitFrameByStartEnd(0, 1, 3, 1, true);
	mLeftCrouchAnimation->SetIsLoop(false);
	mLeftCrouchAnimation->SetFrameUpdateTime(0.1f);
//	mLeftCrouchAnimation->Play();

	mRightCrouchAnimation = new Animation();
	mRightCrouchAnimation->InitFrameByStartEnd(0, 0, 3, 0, false);
	mRightCrouchAnimation->SetIsLoop(false);
	mRightCrouchAnimation->SetFrameUpdateTime(0.1f);
//	mRightCrouchAnimation->Play();

	// 일어나기 애니메이션
	mLeftRiseAnimation = new Animation();
	mLeftRiseAnimation->InitFrameByStartEnd(0, 1, 1, 1, true);
	mLeftRiseAnimation->SetIsLoop(false);
	mLeftRiseAnimation->SetFrameUpdateTime(0.1f);
//	mLeftRiseAnimation->Play();
	mLeftRiseAnimation->SetCallbackFunc(bind(&Player::SetStateIdle, this));

	mRightRiseAnimation = new Animation();
	mRightRiseAnimation->InitFrameByStartEnd(0, 0, 1, 0, false);
	mRightRiseAnimation->SetIsLoop(false);
	mRightRiseAnimation->SetFrameUpdateTime(0.1f);
//	mRightRiseAnimation->Play();
	mRightRiseAnimation->SetCallbackFunc(bind(&Player::SetStateIdle, this));

	// 구르기 애니메이션
	mLeftRollAnimation = new Animation();
	mLeftRollAnimation->InitFrameByStartEnd(0, 1, 7, 1, true);
	mLeftRollAnimation->SetIsLoop(false);
	mLeftRollAnimation->SetFrameUpdateTime(0.07f);
//	mLeftRollAnimation->Play();
	mLeftRollAnimation->SetCallbackFunc(bind(&Player::SetStateIdle, this));

	mRightRollAnimation = new Animation();
	mRightRollAnimation->InitFrameByStartEnd(0, 0, 7, 0, false);
	mRightRollAnimation->SetIsLoop(false);
	mRightRollAnimation->SetFrameUpdateTime(0.07f);
//	mRightRollAnimation->Play();
	mRightRollAnimation->SetCallbackFunc(bind(&Player::SetStateIdle, this));

	// 사다리 입장 애니메이션
	mLeftLadderEnterAnimation = new Animation();
	mLeftLadderEnterAnimation->InitFrameByStartEnd(0, 1, 5, 1, true);
	mLeftLadderEnterAnimation->SetIsLoop(true);
	mLeftLadderEnterAnimation->SetFrameUpdateTime(0.1f);
//	mLeftLadderEnterAnimation->Play();
	mLeftLadderEnterAnimation->SetCallbackFunc(bind(&Player::SetStateLadderUp, this));

	mRightLadderEnterAnimation = new Animation();
	mRightLadderEnterAnimation->InitFrameByStartEnd(0, 0, 5, 0, false);
	mRightLadderEnterAnimation->SetIsLoop(true);
	mRightLadderEnterAnimation->SetFrameUpdateTime(0.1f);
//	mRightLadderEnterAnimation->Play();
	mRightLadderEnterAnimation->SetCallbackFunc(bind(&Player::SetStateLadderUp, this));

	// 사다리 오르내리기 애니메이션
	mLadderUpAnimation = new Animation();
	mLadderUpAnimation->InitFrameByStartEnd(0, 0, 5, 0, true);
	mLadderUpAnimation->SetIsLoop(true);
	mLadderUpAnimation->SetFrameUpdateTime(0.1f);
//	mLadderUpAnimation->Play();

	mLadderDownAnimation = new Animation();
	mLadderDownAnimation->InitFrameByStartEnd(0, 0, 2, 0, true);
	mLadderDownAnimation->SetIsLoop(true);
	mLadderDownAnimation->SetFrameUpdateTime(0.1f);
//	mLadderDownAnimation->Play();

	// 사다리 퇴장 애니메이션
	mLeftLadderLeaveAnimation = new Animation();
	mLeftLadderLeaveAnimation->InitFrameByStartEnd(0, 1, 5, 1, true);
	mLeftLadderLeaveAnimation->SetIsLoop(true);
	mLeftLadderLeaveAnimation->SetFrameUpdateTime(0.1f);
//	mLeftLadderLeaveAnimation->Play();

	mRightLadderLeaveAnimation = new Animation();
	mRightLadderLeaveAnimation->InitFrameByStartEnd(0, 0, 5, 0, false);
	mRightLadderLeaveAnimation->SetIsLoop(true);
	mRightLadderLeaveAnimation->SetFrameUpdateTime(0.1f);
//	mRightLadderLeaveAnimation->Play();

	// 서서 활 애니메이션
	mLeftBowAnimation = new Animation();
	mLeftBowAnimation->InitFrameByStartEnd(0, 1, 5, 1, true);
	mLeftBowAnimation->SetIsLoop(true);
	mLeftBowAnimation->SetFrameUpdateTime(0.1f);
//	mLeftBowAnimation->Play();
	mLeftBowAnimation->SetCallbackFunc(bind(&Player::SetEndAttack, this));

	mRightBowAnimation = new Animation();
	mRightBowAnimation->InitFrameByStartEnd(0, 0, 5, 0, false);
	mRightBowAnimation->SetIsLoop(true);
	mRightBowAnimation->SetFrameUpdateTime(0.1f);
//	mRightBowAnimation->Play();
	mRightBowAnimation->SetCallbackFunc(bind(&Player::SetEndAttack, this));

	// 공중 활 애니메이션
	mLeftAirBowAnimation = new Animation();
	mLeftAirBowAnimation->InitFrameByStartEnd(0, 1, 5, 1, true);
	mLeftAirBowAnimation->SetIsLoop(true);
	mLeftAirBowAnimation->SetFrameUpdateTime(0.1f);
//	mLeftAirBowAnimation->Play();
	mLeftAirBowAnimation->SetCallbackFunc(bind(&Player::SetEndAirAttack, this));

	mRightAirBowAnimation = new Animation();
	mRightAirBowAnimation->InitFrameByStartEnd(0, 0, 5, 0, false);
	mRightAirBowAnimation->SetIsLoop(true);
	mRightAirBowAnimation->SetFrameUpdateTime(0.1f);
//	mRightAirBowAnimation->Play();
	mRightAirBowAnimation->SetCallbackFunc(bind(&Player::SetEndAirAttack, this));

	// 앉아 활 애니메이션
	mLeftCrouchBowAnimation = new Animation();
	mLeftCrouchBowAnimation->InitFrameByStartEnd(0, 1, 5, 1, true);
	mLeftCrouchBowAnimation->SetIsLoop(true);
	mLeftCrouchBowAnimation->SetFrameUpdateTime(0.1f);
//	mLeftCrouchBowAnimation->Play();
	mLeftCrouchBowAnimation->SetCallbackFunc(bind(&Player::SetEndCrouchAttack, this));

	mRightCrouchBowAnimation = new Animation();
	mRightCrouchBowAnimation->InitFrameByStartEnd(0, 0, 5, 0, false);
	mRightCrouchBowAnimation->SetIsLoop(true);
	mRightCrouchBowAnimation->SetFrameUpdateTime(0.1f);
//	mRightCrouchBowAnimation->Play();
	mRightCrouchBowAnimation->SetCallbackFunc(bind(&Player::SetEndCrouchAttack, this));

	// 첫 번째 공격 애니메이션
	mLeftAttack1Animation = new Animation();
	mLeftAttack1Animation->InitFrameByStartEnd(0, 1, 6, 1, true);
	mLeftAttack1Animation->SetIsLoop(true);
	mLeftAttack1Animation->SetFrameUpdateTime(0.1f);
//	mLeftAttack1Animation->Play();
	mLeftAttack1Animation->SetCallbackFunc(bind(&Player::SetEndAttack, this));

	mRightAttack1Animation = new Animation();
	mRightAttack1Animation->InitFrameByStartEnd(0, 0, 6, 0, false);
	mRightAttack1Animation->SetIsLoop(true);
	mRightAttack1Animation->SetFrameUpdateTime(0.1f);
//	mRightAttack1Animation->Play();
	mRightAttack1Animation->SetCallbackFunc(bind(&Player::SetEndAttack, this));

	// 두 번째 공격 애니메이션
	mLeftAttack2Animation = new Animation();
	mLeftAttack2Animation->InitFrameByStartEnd(0, 1, 6, 1, true);
	mLeftAttack2Animation->SetIsLoop(true);
	mLeftAttack2Animation->SetFrameUpdateTime(0.1f);
//	mLeftAttack2Animation->Play();
	mLeftAttack2Animation->SetCallbackFunc(bind(&Player::SetEndAttack, this));

	mRightAttack2Animation = new Animation();
	mRightAttack2Animation->InitFrameByStartEnd(0, 0, 6, 0, false);
	mRightAttack2Animation->SetIsLoop(true);
	mRightAttack2Animation->SetFrameUpdateTime(0.1f);
//	mRightAttack2Animation->Play();
	mRightAttack2Animation->SetCallbackFunc(bind(&Player::SetEndAttack, this));

	// 세 번째 공격 애니메이션
	mLeftAttack3Animation = new Animation();
	mLeftAttack3Animation->InitFrameByStartEnd(0, 1, 10, 1, true);
	mLeftAttack3Animation->SetIsLoop(true);
	mLeftAttack3Animation->SetFrameUpdateTime(0.1f);
//	mLeftAttack3Animation->Play();
	mLeftAttack3Animation->SetCallbackFunc(bind(&Player::SetEndAttack, this));

	mRightAttack3Animation = new Animation();
	mRightAttack3Animation->InitFrameByStartEnd(0, 0, 10, 0, false);
	mRightAttack3Animation->SetIsLoop(true);
	mRightAttack3Animation->SetFrameUpdateTime(0.1f);
//	mRightAttack3Animation->Play();
	mRightAttack3Animation->SetCallbackFunc(bind(&Player::SetEndAttack, this));

	// 공중 공격 애니메이션
	mLeftAirAttackAnimation = new Animation();
	mLeftAirAttackAnimation->InitFrameByStartEnd(0, 1, 6, 1, true);
	mLeftAirAttackAnimation->SetIsLoop(true);
	mLeftAirAttackAnimation->SetFrameUpdateTime(0.1f);
//	mLeftAirAttackAnimation->Play();
	mLeftAirAttackAnimation->SetCallbackFunc(bind(&Player::SetEndAirAttack, this));

	mRightAirAttackAnimation = new Animation();
	mRightAirAttackAnimation->InitFrameByStartEnd(0, 0, 6, 0, false);
	mRightAirAttackAnimation->SetIsLoop(true);
	mRightAirAttackAnimation->SetFrameUpdateTime(0.1f);
//	mRightAirAttackAnimation->Play();
	mRightAirAttackAnimation->SetCallbackFunc(bind(&Player::SetEndAirAttack, this));

	// 피격 애니메이션
	mLeftHurtAnimation = new Animation();
	mLeftHurtAnimation->InitFrameByStartEnd(0, 1, 1, 1, true);
	mLeftHurtAnimation->SetIsLoop(true);
	mLeftHurtAnimation->SetFrameUpdateTime(0.3f);
//	mLeftHurtAnimation->Play();

	mRightHurtAnimation = new Animation();
	mRightHurtAnimation->InitFrameByStartEnd(0, 0, 1, 0, false);
	mRightHurtAnimation->SetIsLoop(true);
	mRightHurtAnimation->SetFrameUpdateTime(0.3f);
//	mRightHurtAnimation->Play();

	// 사망 애니메이션
	mLeftDeathAnimation = new Animation();
	mLeftDeathAnimation->InitFrameByStartEnd(0, 1, 23, 1, true);
	mLeftDeathAnimation->SetIsLoop(false);
	mLeftDeathAnimation->SetFrameUpdateTime(0.2f);
//	mLeftDeathAnimation->Play();

	mRightDeathAnimation = new Animation();
	mRightDeathAnimation->InitFrameByStartEnd(0, 0, 23, 0, false);
	mRightDeathAnimation->SetIsLoop(false);
	mRightDeathAnimation->SetFrameUpdateTime(0.2f);
//	mRightDeathAnimation->Play();
}

void Player::InitPlayerVar()
{
	// 부모 클래스인 GameObject에 선언된 변수들
	mName = "Player";
	mX = WINSIZEX / 2.f;
	mY = 200.f;
	mSizeX = (float)(mIdleImage->GetFrameWidth()) * 2.f;
	mSizeY = (float)(mIdleImage->GetFrameHeight()) * 2.f;
	mDirection = Direction::Right;
	mRect = RectMakeCenter((int)mX, (int)mY, (int)mSizeX, (int)mSizeY);
	mHitBox = RectMakeCenter((int)mX, (int)mY, (int)(mSizeX / 2.f), (int)mSizeY); // 임시(가로만 반)
	mAttackBox = RectMakeCenter((int)mX, (int)mY, (int)mSizeX, (int)mSizeY); // 임시(플레이어 사이즈)

	// Player에 선언된 변수들
	mArrowSpeed = 600.f;

	mState = PlayerState::Idle;
	mSpeed = 400.f;
	mJumpPower = 0.f;
	mGravity = 0.2f;

	mHp = 100;
	mAttackDamage = 0;

	invincibility = 0;
	stopmove = 0;
	stoproll = 0;

	mHaveMagnet = false;

	mCurrentImage = mIdleImage;
	mCurrentAnimation = mRightIdleAnimation;
}

void Player::SafeDeletePlayerAnimation()
{
	SafeDelete(mLeftIdleAnimation);
	SafeDelete(mRightIdleAnimation);
	SafeDelete(mLeftRunStartAnimation);
	SafeDelete(mLeftRunAnimation);
	SafeDelete(mRightRunStartAnimation);
	SafeDelete(mRightRunAnimation);
	SafeDelete(mLeftBrakeAnimation);
	SafeDelete(mRightBrakeAnimation);
	SafeDelete(mLeftTurnAnimation);
	SafeDelete(mRightTurnAnimation);
	SafeDelete(mLeftJumpAnimation);
	SafeDelete(mRightJumpAnimation);
	SafeDelete(mLeftFallAnimation);
	SafeDelete(mRightFallAnimation);
	SafeDelete(mLeftLandSoftAnimation);
	SafeDelete(mRightLandSoftAnimation);
	SafeDelete(mLeftCrouchAnimation);
	SafeDelete(mRightCrouchAnimation);
	SafeDelete(mLeftRiseAnimation);
	SafeDelete(mRightRiseAnimation);
	SafeDelete(mLeftRollAnimation);
	SafeDelete(mRightRollAnimation);
	SafeDelete(mLeftLadderEnterAnimation);
	SafeDelete(mRightLadderEnterAnimation);
	SafeDelete(mLadderUpAnimation);
	SafeDelete(mLadderDownAnimation);
	SafeDelete(mLeftLadderLeaveAnimation);
	SafeDelete(mRightLadderLeaveAnimation);
	SafeDelete(mLeftBowAnimation);
	SafeDelete(mRightBowAnimation);
	SafeDelete(mLeftAirBowAnimation);
	SafeDelete(mRightAirBowAnimation);
	SafeDelete(mLeftCrouchBowAnimation);
	SafeDelete(mRightCrouchBowAnimation);
	SafeDelete(mLeftAttack1Animation);
	SafeDelete(mRightAttack1Animation);
	SafeDelete(mLeftAttack2Animation);
	SafeDelete(mRightAttack2Animation);
	SafeDelete(mLeftAttack3Animation);
	SafeDelete(mRightAttack3Animation);
	SafeDelete(mLeftAirAttackAnimation);
	SafeDelete(mRightAirAttackAnimation);
	SafeDelete(mLeftHurtAnimation);
	SafeDelete(mRightHurtAnimation);
	SafeDelete(mLeftDeathAnimation);
	SafeDelete(mRightDeathAnimation);
}

void Player::SetStateRun()
{
	// if (mState == State::LeftRun) // 이게 아랫문장으로 바뀐 것(스테이트랑 방향 나누기)
	if (mState == PlayerState::Run && mDirection == Direction::Left)
	{
		mCurrentAnimation->Stop();
		mCurrentAnimation = mLeftRunAnimation;
		mCurrentAnimation->Play();
		mCurrentImage = mRunImage;
	}
	//else if (mState == State::RightRun)
	else if (mState == PlayerState::Run && mDirection == Direction::Right)
	{
		mCurrentAnimation->Stop();
		mCurrentAnimation = mRightRunAnimation;
		mCurrentAnimation->Play();
		mCurrentImage = mRunImage;
	}
}

void Player::SetStateIdle()
{
	//if (mState == State::LeftRoll || mState == State::LeftRise || mState == State::LeftBrake || mState == State::LeftLandSoft)
	if (mDirection == Direction::Left)
	{
		if (mState == PlayerState::Roll || mState == PlayerState::Rise || mState == PlayerState::Brake || mState == PlayerState::LandSoft)
		{
			//mState = State::LeftIdle;
			mState = PlayerState::Idle;
			mCurrentAnimation->Stop();
			mCurrentAnimation = mLeftIdleAnimation;
			mCurrentAnimation->Play();
			mCurrentImage = mIdleImage;
		}
	}
	//else if (mState == State::RightRoll || mState == State::RightRise || mState == State::RightBrake || mState == State::RightLandSoft)
	else if (mDirection == Direction::Right)
	{
		if (mState == PlayerState::Roll || mState == PlayerState::Rise || mState == PlayerState::Brake || mState == PlayerState::LandSoft)
		{
			//mState = State::RightIdle;
			mState = PlayerState::Idle;
			mCurrentAnimation->Stop();
			mCurrentAnimation = mRightIdleAnimation;
			mCurrentAnimation->Play();
			mCurrentImage = mIdleImage;
		}
	}
}

void Player::SetEndAttack() 
{
	//if (mState == State::LeftAttack1 || mState == State::LeftAttack2 || mState == State::LeftAttack3 || mState == State::LeftBow)
	if (mDirection == Direction::Left)
	{
		if (mState == PlayerState::Attack1 || mState == PlayerState::Attack2 || mState == PlayerState::Attack3 || mState == PlayerState::Bow)
		{
			//mState = State::LeftIdle;
			mState = PlayerState::Idle;
			mCurrentAnimation->Stop();
			mCurrentAnimation = mLeftIdleAnimation;
			mCurrentAnimation->Play();
			mCurrentImage = mIdleImage;
		}
	}
	//if (mState == State::RightAttack1 || mState == State::RightAttack2 || mState == State::RightAttack3 || mState == State::RightBow)
	if (mDirection == Direction::Right)
	{
		if (mState == PlayerState::Attack1 || mState == PlayerState::Attack2 || mState == PlayerState::Attack3 || mState == PlayerState::Bow)
		{
			//mState = State::RightIdle;
			mState = PlayerState::Idle;
			mCurrentAnimation->Stop();
			mCurrentAnimation = mRightIdleAnimation;
			mCurrentAnimation->Play();
			mCurrentImage = mIdleImage;
		}
	}

	mHitAttack = true;
}

void Player::SetEndAirAttack()
{
	//if (mState == State::LeftAirBow || mState == State::LeftAirAttack)
	if (mDirection == Direction::Left)
	{
		if (mState == PlayerState::AirBow || mState == PlayerState::AirAttack)
		{
			//mState = State::LeftFall;
			mState = PlayerState::Fall;
			mCurrentAnimation->Stop();
			mCurrentAnimation = mLeftFallAnimation;
			mCurrentAnimation->Play();
			mCurrentImage = mFallImage;
		}
	}
	//if (mState == State::RightAirBow || mState == State::RightAirAttack)
	if (mDirection == Direction::Right)
	{
		if (mState == PlayerState::AirBow || mState == PlayerState::AirAttack)
		{
			//mState = State::RightFall;
			mState = PlayerState::Fall;
			mCurrentAnimation->Stop();
			mCurrentAnimation = mRightFallAnimation;
			mCurrentAnimation->Play();
			mCurrentImage = mFallImage;
		}
	}

	mHitAttack = true;
}

void Player::SetEndCrouchAttack()
{
	//if (mState == State::LeftCrouchBow) // <- 여기 왼쪽 오른쪽 왜 달라? 의도 맞아? (1)
	if (mDirection == Direction::Left)
	{
		if (mState == PlayerState::CrouchBow)
		{
			//mState = State::LeftCrouch;
			mState = PlayerState::Crouch;
			mCurrentAnimation->Stop();
			mCurrentAnimation = mLeftCrouchAnimation;
			mCurrentAnimation->Play();
			mCurrentImage = mCrouchImage;
		}
	}
	//if (mState == State::RightAirBow) // <- 여기 왼쪽 오른쪽 왜 달라? 의도 맞아? (2)
	if (mDirection == Direction::Right)
	{
		if (mState == PlayerState::AirBow)
		{
			//mState = State::RightCrouch;
			mState = PlayerState::Crouch;
			mCurrentAnimation->Stop();
			mCurrentAnimation = mRightCrouchAnimation;
			mCurrentAnimation->Play();
			mCurrentImage = mCrouchImage;
		}
	}

	mHitAttack = true;
}

void Player::SetStateLadderUp()
{
	//if (mState == State::LeftLadderEnter || mState == State::RightLadderEnter)
	if (mState == PlayerState::LadderEnter)
	{
		//mState = State::LadderUp;
		mState = PlayerState::LadderUp;
		mCurrentAnimation->Stop();
		mCurrentAnimation = mLadderUpAnimation;
		mCurrentAnimation->Play();
		mCurrentImage = mLadderUpImage;
	}
}

void Player::SetStateLadderDown()
{
	//if (mState == State::LeftLadderEnter || mState == State::RightLadderEnter)
	if (mState == PlayerState::LadderEnter)
	{
		//mState = State::LadderDown;
		mState = PlayerState::LadderDown;
		mCurrentAnimation->Stop();
		mCurrentAnimation = mLadderDownAnimation;
		mCurrentAnimation->Play();
		mCurrentImage = mLadderDownImage;
	}
}
/*
void Player::SetImageAnimation()
{
	mCurrentAnimation->Stop();

	// 왼쪽
	if (mDirection == Direction::Left)
	{
		if (mFennelState == FennelState::Jump)
		{
			mCurrentAnimation = mLeftJump;
			mImage = IMAGEMANAGER->FindImage(L"Fenneljump");
		}
		if (mFennelState == FennelState::Plunge)
		{
			mCurrentAnimation = mLeftPlunge;
			mImage = IMAGEMANAGER->FindImage(L"Fennelplunge");
		}
		if (mFennelState == FennelState::Idle)
		{
			mCurrentAnimation = mLeftIdle;
			mImage = IMAGEMANAGER->FindImage(L"Fennelidle");
		}
		if (mFennelState == FennelState::Attack)
		{
			mCurrentAnimation = mLeftAtk;
			mImage = IMAGEMANAGER->FindImage(L"Fennelatk1");
		}
		if (mFennelState == FennelState::Attack2)
		{
			mCurrentAnimation = mLeftAtk2;
			mImage = IMAGEMANAGER->FindImage(L"Fennelatk2");
		}
		if (mFennelState == FennelState::Hurt)
		{
			mCurrentAnimation = mLeftHurt;
			mImage = IMAGEMANAGER->FindImage(L"Fennelhurt");
		}
		if (mFennelState == FennelState::JumpReady)
		{
			mCurrentAnimation = mLeftJumpReady;
			mImage = IMAGEMANAGER->FindImage(L"Fenneljumpready");
		}
		if (mFennelState == FennelState::Buff)
		{
			mCurrentAnimation = mLeftBuff;
			mImage = IMAGEMANAGER->FindImage(L"Fennelbuff");
		}
		if (mFennelState == FennelState::Dash)
		{
			mCurrentAnimation = mLeftDash;
			mImage = IMAGEMANAGER->FindImage(L"Fenneldash");
		}
		if (mFennelState == FennelState::Death)
		{
			mCurrentAnimation = mLeftDeath;
			mImage = IMAGEMANAGER->FindImage(L"Fenneldeath");
		}
		if (mFennelState == FennelState::Thunder)
		{
			mCurrentAnimation = mLeftThunder;
			mImage = IMAGEMANAGER->FindImage(L"Fennelthunder");
		}
		if (mFennelState == FennelState::Thunder)
		{
			mCurrentAnimation = mLeftThunder;
			mImage = IMAGEMANAGER->FindImage(L"Fennelthunder");
		}
		if (mFennelState == FennelState::BackFlip)
		{
			mCurrentAnimation = mLeftBackflip;
			mImage = IMAGEMANAGER->FindImage(L"Fennelbackflip");
		}
	}
	// 오른쪽
	if (mDirection == Direction::Right)
	{
		if (mFennelState == FennelState::Jump)
		{
			mCurrentAnimation = mRightJump;
			mImage = IMAGEMANAGER->FindImage(L"Fenneljump");
		}
		if (mFennelState == FennelState::Plunge)
		{
			mCurrentAnimation = mRightPlunge;
			mImage = IMAGEMANAGER->FindImage(L"Fennelplunge");
		}
		if (mFennelState == FennelState::Idle)
		{
			mCurrentAnimation = mRightIdle;
			mImage = IMAGEMANAGER->FindImage(L"Fennelidle");
		}
		if (mFennelState == FennelState::Attack)
		{
			mCurrentAnimation = mRightAtk;
			mImage = IMAGEMANAGER->FindImage(L"Fennelatk1");
		}
		if (mFennelState == FennelState::Attack2)
		{
			mCurrentAnimation = mRightAtk2;
			mImage = IMAGEMANAGER->FindImage(L"Fennelatk2");
		}
		if (mFennelState == FennelState::Hurt)
		{
			mCurrentAnimation = mRightHurt;
			mImage = IMAGEMANAGER->FindImage(L"Fennelhurt");
		}
		if (mFennelState == FennelState::JumpReady)
		{
			mCurrentAnimation = mRightJumpReady;
			mImage = IMAGEMANAGER->FindImage(L"Fenneljumpready");
		}
		if (mFennelState == FennelState::Buff)
		{
			mCurrentAnimation = mRightBuff;
			mImage = IMAGEMANAGER->FindImage(L"Fennelbuff");
		}
		if (mFennelState == FennelState::Dash)
		{
			mCurrentAnimation = mRightDash;
			mImage = IMAGEMANAGER->FindImage(L"Fenneldash");
		}
		if (mFennelState == FennelState::Death)
		{
			mCurrentAnimation = mRightDeath;
			mImage = IMAGEMANAGER->FindImage(L"Fenneldeath");
		}
		if (mFennelState == FennelState::Thunder)
		{
			mCurrentAnimation = mRightThunder;
			mImage = IMAGEMANAGER->FindImage(L"Fennelthunder");
		}
		if (mFennelState == FennelState::Thunder)
		{
			mCurrentAnimation = mRightThunder;
			mImage = IMAGEMANAGER->FindImage(L"Fennelthunder");
		}
		if (mFennelState == FennelState::BackFlip)
		{
			mCurrentAnimation = mRightBackflip;
			mImage = IMAGEMANAGER->FindImage(L"Fennelbackflip");
		}
	}

	mCurrentAnimation->Play();
}
*/
#include "pch.h"
#include "Player.h"
#include "Image.h"
#include "Animation.h"
#include "Camera.h"
#include "Arrow.h"
#include "Leaf.h"

Player::Player()
	: GameObject()
{
}

void Player::Init()
{
	FindPlayerImage();

	ReadyPlayerAnimation();

	InitPlayerVar(); // ?Œë ˆ?´ì–´ê°€ ê°€ì§?ê°ì¢… ë³€?˜ë“¤ ì´ˆê¸°???˜ëŠ” ?¨ìˆ˜
}

void Player::Release()
{
	SafeDeletePlayerAnimation();
}

void Player::Update()
{
	// 이동 브레이크 프레임
	if (mState == PlayerState::Idle || mState == PlayerState::Turn || mState == PlayerState::Brake)
	{
		if (Input::GetInstance()->GetKeyDown(VK_LEFT))
		{
			mDirection = Direction::Left;
			mState = PlayerState::Run;
			mCurrentAnimation->Stop();
			mCurrentAnimation = mLeftRunStartAnimation;
			mCurrentAnimation->Play();
			mCurrentImage = mRunImage;
		}
		if (Input::GetInstance()->GetKeyDown(VK_RIGHT))
		{
			mDirection = Direction::Right;
			mState = PlayerState::Run;
			mCurrentAnimation->Stop();
			mCurrentAnimation = mRightRunStartAnimation;
			mCurrentAnimation->Play();
			mCurrentImage = mRunImage;
		}
	}
	if (mState == PlayerState::Run)
	{
		if (Input::GetInstance()->GetKeyUp(VK_LEFT))
		{
			mDirection = Direction::Left;
			mState = PlayerState::Brake;
			mCurrentAnimation->Stop();
			mCurrentAnimation = mLeftBrakeAnimation;
			mCurrentAnimation->Play();
			mCurrentImage = mBrakeImage;
		}
		if (Input::GetInstance()->GetKeyUp(VK_RIGHT))
		{
			mDirection = Direction::Right;
			mState = PlayerState::Brake;
			mCurrentAnimation->Stop();
			mCurrentAnimation = mRightBrakeAnimation;
			mCurrentAnimation->Play();
			mCurrentImage = mBrakeImage;
		}
	}

	// 이동 및 방향전환
	if (Input::GetInstance()->GetKey(VK_LEFT))
	{
		if (stopmove == 0)
		{
			mX -= mSpeed * Time::GetInstance()->DeltaTime();
		}
		if (mState == PlayerState::Run)
		{
<<<<<<< HEAD
			//mState = State::RightTurn;
			mDirection = Direction::Right;
			mState = PlayerState::Turn;
			mCurrentAnimation->Stop();
			mCurrentAnimation = mRightTurnAnimation;
			mCurrentAnimation->Play();
			mCurrentImage = mTurnImage;

=======
			if (Input::GetInstance()->GetKeyDown(VK_RIGHT))
			{
				mDirection = Direction::Right;
				mState = PlayerState::Turn;
				mCurrentAnimation->Stop();
				mCurrentAnimation = mRightTurnAnimation;
				mCurrentAnimation->Play();
				mCurrentImage = mTurnImage;
			}
>>>>>>> 2227e69f15c6377d0d57bf15a56de711be084afe
		}
	}
	if (Input::GetInstance()->GetKey(VK_RIGHT))
	{
		if (stopmove == 0)
		{
			mX += mSpeed * Time::GetInstance()->DeltaTime();
		}
		if (mState == PlayerState::Run)
		{
			if (Input::GetInstance()->GetKeyDown(VK_LEFT))
			{
				mDirection = Direction::Left;
				mState = PlayerState::Turn;
				mCurrentAnimation->Stop();
				mCurrentAnimation = mLeftTurnAnimation;
				mCurrentAnimation->Play();
				mCurrentImage = mTurnImage;
			}
		}
	}
	if (mState == PlayerState::Turn)
	{
		if (Input::GetInstance()->GetKeyUp(VK_LEFT))
		{
			mDirection = Direction::Right;
			mState = PlayerState::Run;
			mCurrentAnimation->Stop();
			mCurrentAnimation = mRightRunAnimation;
			mCurrentAnimation->Play();
			mCurrentImage = mRunImage;
		}
		if (Input::GetInstance()->GetKeyUp(VK_RIGHT))
		{
			mDirection = Direction::Left;
			mState = PlayerState::Run;
			mCurrentAnimation->Stop();
			mCurrentAnimation = mLeftRunAnimation;
			mCurrentAnimation->Play();
			mCurrentImage = mRunImage;
		}
		if (INPUT->GetKeyUp(VK_LEFT) && INPUT->GetKeyUp(VK_RIGHT))
		{
			if (mDirection == Direction::Left)
			{
				mState = PlayerState::Brake;
				mCurrentAnimation->Stop();
				mCurrentAnimation = mLeftBrakeAnimation;
				mCurrentAnimation->Play();
				mCurrentImage = mBrakeImage;
			}
			if (mDirection == Direction::Right)
			{
				mState = PlayerState::Brake;
				mCurrentAnimation->Stop();
				mCurrentAnimation = mRightBrakeAnimation;
				mCurrentAnimation->Play();
				mCurrentImage = mBrakeImage;
			}
		}
	}

	// ?‰ê¸°
	if (Input::GetInstance()->GetKey(VK_DOWN))
	{
		mHitBox = RectMakeCenter((int)mX, (int)mY + 20, (int)(mSizeX / 3.f), (int)(mSizeY / 2));

		if (mDirection == Direction::Left)
		{
			if (mState == PlayerState::Idle || mState == PlayerState::Run)
			{
				mState = PlayerState::Crouch;
				mCurrentAnimation->Stop();
				mCurrentAnimation = mLeftCrouchAnimation;
				mCurrentAnimation->Play();
				mCurrentImage = mCrouchImage;
			}
			if (INPUT->GetKeyDown(VK_RIGHT))
			{
				mDirection = Direction::Right;
				mState = PlayerState::Crouch;
				mCurrentAnimation->Stop();
				mCurrentAnimation = mRightCrouchAnimation;
				mCurrentAnimation->Play();
				mCurrentImage = mCrouchImage;
			}
		}
		if (mDirection == Direction::Right)
		{
			if (mState == PlayerState::Idle || mState == PlayerState::Run)
			{
				mState = PlayerState::Crouch;
				mCurrentAnimation->Stop();
				mCurrentAnimation = mRightCrouchAnimation;
				mCurrentAnimation->Play();
				mCurrentImage = mCrouchImage;
			}
			if (INPUT->GetKeyDown(VK_LEFT))
			{
				mDirection = Direction::Left;
				mState = PlayerState::Crouch;
				mCurrentAnimation->Stop();
				mCurrentAnimation = mLeftCrouchAnimation;
				mCurrentAnimation->Play();
				mCurrentImage = mCrouchImage;
			}
		}
		//?„ëž˜ ?í”„
		if (Input::GetInstance()->GetKeyDown(VK_SPACE))
		{
			// if 플레이어가 특정 바닥위에 있으면
			if (COLLISIONMANAGER->IsInRangeDownjumpPlatform(&mRect))
			{
				mIsInDownPlatform = true;

				if (mDirection == Direction::Left)
				{
					mState = PlayerState::Fall;
					mCurrentAnimation->Stop();
					mCurrentAnimation = mLeftFallAnimation;
					mCurrentAnimation->Play();
					mCurrentImage = mFallImage;
				}
				if (mDirection == Direction::Right)
				{
					mState = PlayerState::Fall;
					mCurrentAnimation->Stop();
					mCurrentAnimation = mRightFallAnimation;
					mCurrentAnimation->Play();
					mCurrentImage = mFallImage;
				}
			}
		}
	}

	// 일어서기
	if (mState == PlayerState::Crouch)
	{
		if (Input::GetInstance()->GetKeyUp(VK_DOWN))
		{
			if (mDirection == Direction::Left)
			{
				mState = PlayerState::Rise;
				mCurrentAnimation->Stop();
				mCurrentAnimation = mLeftRiseAnimation;
				mCurrentAnimation->Play();
				mCurrentImage = mRiseImage;
			}
			if (mDirection == Direction::Right)
			{
				mState = PlayerState::Rise;
				mCurrentAnimation->Stop();
				mCurrentAnimation = mRightRiseAnimation;
				mCurrentAnimation->Play();
				mCurrentImage = mRiseImage;
			}
		}
	}

	// êµ¬ë¥´ê¸?
	if (Input::GetInstance()->GetKeyDown(VK_LSHIFT))
	{
<<<<<<< HEAD
		//if (mState == State::LeftIdle || mState == State::LeftRun)
=======
>>>>>>> 2227e69f15c6377d0d57bf15a56de711be084afe
		if (mDirection == Direction::Left)
		{
			if (mState == PlayerState::Idle || mState == PlayerState::Run)
			{
				mState = PlayerState::Roll;
				mCurrentAnimation->Stop();
				mCurrentAnimation = mLeftRollAnimation;
				mCurrentAnimation->Play();
				mCurrentImage = mRollImage;
			}
		}
		if (mDirection == Direction::Right)
		{
			if (mState == PlayerState::Idle || mState == PlayerState::Run)
			{
				mState = PlayerState::Roll;
				mCurrentAnimation->Stop();
				mCurrentAnimation = mRightRollAnimation;
				mCurrentAnimation->Play();
				mCurrentImage = mRollImage;
			}
		}
	}
	//굴렀을때 랙트
	if (mState == PlayerState::Roll)
	{
		mHitBox = RectMakeCenter((int)mX + 10000, (int)mY, (int)(mSizeX / 3.f), (int)mSizeY);

		if (mDirection == Direction::Left)
		{
			mX -= mSpeed * Time::GetInstance()->DeltaTime() * 1.3f;
			mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
		}
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

	// ??ê³µê²©
	if (Input::GetInstance()->GetKeyDown('X'))
	{
		Arrow* arrow = new Arrow();
		mArrowImage = IMAGEMANAGER->FindImage(L"Arrow");

		if (mDirection == Direction::Left)
		{
			if (mState == PlayerState::Idle || mState == PlayerState::Run)
			{
				mState = PlayerState::Bow;
				mCurrentAnimation->Stop();
				mCurrentAnimation = mLeftBowAnimation;
				mCurrentAnimation->Play();
				mCurrentImage = mBowImage;
				arrow->Fire(mArrowImage, mX, mY, mArrowSpeed, PI);
				arrow->SetArrowIndexY(1);
				arrow->SetObject();
				OBJECTMANAGER->AddObject(ObjectLayer::PlayerArrow, (GameObject*)arrow);
			}
			if (mState == PlayerState::Jump || mState == PlayerState::Fall)
			{
				mState = PlayerState::AirBow;
				mCurrentAnimation->Stop();
				mCurrentAnimation = mLeftAirBowAnimation;
				mCurrentAnimation->Play();
				mCurrentImage = mAirBowImage;
				arrow->Fire(mArrowImage, mX, mY, mArrowSpeed, PI);
				arrow->SetArrowIndexY(1);
				OBJECTMANAGER->AddObject(ObjectLayer::PlayerArrow, (GameObject*)arrow);
			}
			if (mState == PlayerState::Crouch)
			{
				mHitBox = RectMakeCenter((int)mX, (int)mY + 20, (int)(mSizeX / 3.f), (int)(mSizeY / 2));

				mState = PlayerState::CrouchBow;
				mCurrentAnimation->Stop();
				mCurrentAnimation = mLeftCrouchBowAnimation;
				mCurrentAnimation->Play();
				mCurrentImage = mCrouchBowImage;
				arrow->Fire(mArrowImage, mX - 20, mY + 18, mArrowSpeed, PI);
				arrow->SetArrowIndexY(1);
				OBJECTMANAGER->AddObject(ObjectLayer::PlayerArrow, (GameObject*)arrow);
			}
		}
		if (mDirection == Direction::Right)
		{
			if (mState == PlayerState::Idle || mState == PlayerState::Run)
			{
				mState = PlayerState::Bow;
				mCurrentAnimation->Stop();
				mCurrentAnimation = mRightBowAnimation;
				mCurrentAnimation->Play();
				mCurrentImage = mBowImage;
				arrow->Fire(mArrowImage, mX, mY, mArrowSpeed, 0);
				arrow->SetArrowIndexY(0);
				OBJECTMANAGER->AddObject(ObjectLayer::PlayerArrow, (GameObject*)arrow);
			}
			if (mState == PlayerState::Jump || mState == PlayerState::Fall)
			{
				mState = PlayerState::AirBow;
				mCurrentAnimation->Stop();
				mCurrentAnimation = mRightAirBowAnimation;
				mCurrentAnimation->Play();
				mCurrentImage = mAirBowImage;
				arrow->Fire(mArrowImage, mX, mY, mArrowSpeed, 0);
				arrow->SetArrowIndexY(0);
				OBJECTMANAGER->AddObject(ObjectLayer::PlayerArrow, (GameObject*)arrow);
			}
			if (mState == PlayerState::Crouch)
			{
				mHitBox = RectMakeCenter((int)mX, (int)mY + 20, (int)(mSizeX / 3.f), (int)(mSizeY / 2));

				mState = PlayerState::CrouchBow;
				mCurrentAnimation->Stop();
				mCurrentAnimation = mRightCrouchBowAnimation;
				mCurrentAnimation->Play();
				mCurrentImage = mCrouchBowImage;
				arrow->Fire(mArrowImage, mX + 20, mY + 18, mArrowSpeed, 0);
				arrow->SetArrowIndexY(0);
				OBJECTMANAGER->AddObject(ObjectLayer::PlayerArrow, (GameObject*)arrow);
			}
		}
	}

<<<<<<< HEAD
	// �� ���� 1 // ����Ʈ X
	//if (mState != State::LeftAttack1 && mState != State::RightAttack1 && mState != State::LeftAttack2 && mState != State::RightAttack2 && mState != State::LeftAttack3 && mState != State::RightAttack3)
	if (mState != PlayerState::Attack1 || mState != PlayerState::Attack2 || mState != PlayerState::Attack3)
=======
	// ê²€ ê³µê²© 1
	if(mState != PlayerState::Attack1 && mState != PlayerState::Attack2 && mState != PlayerState::Attack3)
>>>>>>> 2227e69f15c6377d0d57bf15a56de711be084afe
	{
		if (Input::GetInstance()->GetKeyDown('Z'))
		{
			if (mDirection == Direction::Left)
			{
				if (mState == PlayerState::Idle || mState == PlayerState::Run)
				{
					mState = PlayerState::Attack1;
					mCurrentAnimation->Stop();
					mCurrentAnimation = mLeftAttack1Animation;
					mCurrentAnimation->Play();
					mCurrentImage = mAttack1Image;
					mLeaf->SetCurrentImageAnimation(1, true);
				}
				if (mState == PlayerState::Jump || mState == PlayerState::Fall)
				{
					mState = PlayerState::AirAttack;
					mCurrentAnimation->Stop();
					mCurrentAnimation = mLeftAirAttackAnimation;
					mCurrentAnimation->Play();
					mCurrentImage = mAirAttackImage;
				}
			}
			if (mDirection == Direction::Right)
			{
				if (mState == PlayerState::Idle || mState == PlayerState::Run)
				{
					mState = PlayerState::Attack1;
					mCurrentAnimation->Stop();
					mCurrentAnimation = mRightAttack1Animation;
					mCurrentAnimation->Play();
					mCurrentImage = mAttack1Image;
					mLeaf->SetIsActive(true);
					mLeaf->SetCurrentImageAnimation(1, false);
				}
				if (mState == PlayerState::Jump || mState == PlayerState::Fall)
				{
					mState = PlayerState::AirAttack;
					mCurrentAnimation->Stop();
					mCurrentAnimation = mRightAirAttackAnimation;
					mCurrentAnimation->Play();
					mCurrentImage = mAirAttackImage;
				}
			}
			mHitAttack = true;
			mAttackDamage = 10;
		}
	}

	// ê²€ ê³µê²© 2
	if (mState == PlayerState::Attack1)
	{
		if (Input::GetInstance()->GetKeyDown('Z'))
		{
			if (mDirection == Direction::Left)
			{
				if (mCurrentAnimation->GetNowFrameX() == 0 || mCurrentAnimation->GetNowFrameX() == 1 || mCurrentAnimation->GetNowFrameX() == 2)
				{
					mState = PlayerState::Attack2;
					mCurrentAnimation->Stop();
					mCurrentAnimation = mLeftAttack2Animation;
					mCurrentAnimation->Play();
					mCurrentImage = mAttack2Image;
					mLeaf->SetCurrentImageAnimation(2, true);
				}
			}
			if (mDirection == Direction::Right)
			{
				if (mCurrentAnimation->GetNowFrameX() == 4 || mCurrentAnimation->GetNowFrameX() == 5 || mCurrentAnimation->GetNowFrameX() == 6)
				{
					mState = PlayerState::Attack2;
					mCurrentAnimation->Stop();
					mCurrentAnimation = mRightAttack2Animation;
					mCurrentAnimation->Play();
					mCurrentImage = mAttack2Image;
					mLeaf->SetCurrentImageAnimation(2, false);
				}
			}
			mHitAttack = true;
			mAttackDamage = 15;
		}
	}

	// ê²€ ê³µê²© 3
	if (mState == PlayerState::Attack2)
	{
		if (Input::GetInstance()->GetKeyDown('Z'))
		{
			if (mDirection == Direction::Left)
			{
				if (mCurrentAnimation->GetNowFrameX() == 0 || mCurrentAnimation->GetNowFrameX() == 1)
				{
					if (INPUT->GetKey(VK_RIGHT))
					{
						mDirection = Direction::Right;
						mState = PlayerState::Attack3;
						mCurrentAnimation->Stop();
						mCurrentAnimation = mRightAttack3Animation;
						mCurrentAnimation->Play();
						mCurrentImage = mAttack3Image;
						mLeaf->SetCurrentImageAnimation(3, false);
					}
					else
					{
						mState = PlayerState::Attack3;
						mCurrentAnimation->Stop();
						mCurrentAnimation = mLeftAttack3Animation;
						mCurrentAnimation->Play();
						mCurrentImage = mAttack3Image;
						mLeaf->SetCurrentImageAnimation(3, true);
					}
				}
			}

			if (mDirection == Direction::Right)
			{
				if (mCurrentAnimation->GetNowFrameX() == 4 || mCurrentAnimation->GetNowFrameX() == 5)
				{
					if (INPUT->GetKey(VK_LEFT))
					{
						mDirection = Direction::Left;
						mState = PlayerState::Attack3;
						mCurrentAnimation->Stop();
						mCurrentAnimation = mLeftAttack3Animation;
						mCurrentAnimation->Play();
						mCurrentImage = mAttack3Image;
						mLeaf->SetCurrentImageAnimation(3, true);
					}
					else
					{
						mState = PlayerState::Attack3;
						mCurrentAnimation->Stop();
						mCurrentAnimation = mRightAttack3Animation;
						mCurrentAnimation->Play();
						mCurrentImage = mAttack3Image;
						mLeaf->SetCurrentImageAnimation(3, false);
					}
				}
			}
			mHitAttack = true;
			mAttackDamage = 20;
		}
	}
	if (mState == PlayerState::Attack1)
	{
		if (mDirection == Direction::Left)
		{
			if (mCurrentAnimation->GetNowFrameX() >= 4 && mCurrentAnimation->GetNowFrameX() <= 6)
			{
				mX -= 100.f * Time::GetInstance()->DeltaTime();
				mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
			}
		}
		if (mDirection == Direction::Right)
		{
			if (mCurrentAnimation->GetNowFrameX() >= 0 && mCurrentAnimation->GetNowFrameX() <= 2)
			{
				mX += 100.f * Time::GetInstance()->DeltaTime();
				mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
			}
		}
	}
	if (mState == PlayerState::Attack2)
	{
		if (mDirection == Direction::Left)
		{
			if (mCurrentAnimation->GetNowFrameX() >= 4 && mCurrentAnimation->GetNowFrameX() <= 6)
			{
				mX -= 120.f * Time::GetInstance()->DeltaTime();
				mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
			}
		}
		if (mDirection == Direction::Right)
		{
			if (mCurrentAnimation->GetNowFrameX() >= 0 && mCurrentAnimation->GetNowFrameX() <= 2)
			{
				mX += 120.f * Time::GetInstance()->DeltaTime();
				mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
			}
		}
	}
	if (mState == PlayerState::Attack3)
	{
		if (mDirection == Direction::Left)
		{
			if (mCurrentAnimation->GetNowFrameX() >= 6 && mCurrentAnimation->GetNowFrameX() <= 10)
			{
				mX -= 150.f * Time::GetInstance()->DeltaTime();
				mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
			}
		}
		if (mDirection == Direction::Right)
		{
			if (mCurrentAnimation->GetNowFrameX() >= 0 && mCurrentAnimation->GetNowFrameX() <= 4)
			{
				mX += 150.f * Time::GetInstance()->DeltaTime();
				mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
			}
		}
	}

	//피격
	if (mState == PlayerState::Hurt)
	{
		if (mTimer == 0) 
		{
			if (mDirection == Direction::Left)
			{
				mState = PlayerState::Hurt;
				mCurrentAnimation->Stop();
				mCurrentAnimation = mLeftHurtAnimation;
				mCurrentAnimation->Play();
				mCurrentImage = mHurtImage;
			}
			if (mDirection == Direction::Right)
			{
				mState = PlayerState::Hurt;
				mCurrentAnimation->Stop();
				mCurrentAnimation = mRightHurtAnimation;
				mCurrentAnimation->Play();
				mCurrentImage = mHurtImage;
			}
		}
		mTimer += Time::GetInstance()->DeltaTime();
		if (mDirection == Direction::Left)
		{
			mX += mSpeed * Time::GetInstance()->DeltaTime() / 3.f;
			mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);

		}
		if (mDirection == Direction::Right)
		{
			mX -= mSpeed * Time::GetInstance()->DeltaTime() / 3.f;
			mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);

		}
		if (mTimer >= 1.f)
		{
			mHitBox = RectMakeCenter((int)mX, (int)mY, (int)(mSizeX / 3.f), (int)mSizeY);
			mTimer = 0;

if (mDirection == Direction::Left)
{
	if (mState == PlayerState::Hurt)
	{
		mState = PlayerState::Idle;
		mCurrentAnimation->Stop();
		mCurrentAnimation = mLeftIdleAnimation;
		mCurrentAnimation->Play();
		mCurrentImage = mIdleImage;
	}
}
if (mDirection == Direction::Right)
{
	if (mState == PlayerState::Hurt)
	{
		mState = PlayerState::Idle;
		mCurrentAnimation->Stop();
		mCurrentAnimation = mRightIdleAnimation;
		mCurrentAnimation->Play();
		mCurrentImage = mIdleImage;
	}
}
		}
	}

	// Hp ?Œë³µ ?„ì´???¬ìš©
	if (mHp > 0 && mHp < 100 && mPotion > 0)
	{
		if (Input::GetInstance()->GetKeyDown('Q'))
		{
<<<<<<< HEAD
			//if (mState == State::LeftIdle || mState == State::RightIdle)
			if (mState == PlayerState::Idle)
			{
				mHp + 30; // <- �̰� �Ǵ� �����ΰ���?
=======
			mHp += 30;
			mPotion -= 1;

			if (mDirection == Direction::Left)
			{
				if (mState == PlayerState::Idle || mState == PlayerState::Run)
				{
					mState = PlayerState::UseItem;
					mCurrentAnimation->Stop();
					mCurrentAnimation = mLeftUseItemAnimation;
					mCurrentAnimation->Play();
					mCurrentImage = mUseItemImage;
				}
			}
			if (mDirection == Direction::Right)
			{
				if (mState == PlayerState::Idle || mState == PlayerState::Run)
				{
					mState = PlayerState::UseItem;
					mCurrentAnimation->Stop();
					mCurrentAnimation = mRightUseItemAnimation;
					mCurrentAnimation->Play();
					mCurrentImage = mUseItemImage;
				}
>>>>>>> 2227e69f15c6377d0d57bf15a56de711be084afe
			}
		}
	}
	if (mHp > 100)
	{
		mHp -= (mHp - 100);
	}

<<<<<<< HEAD
	// ���
=======
	// ?¬ë§
>>>>>>> 2227e69f15c6377d0d57bf15a56de711be084afe
	if (mHp <= 0)
	{
		if (mDirection == Direction::Left)
		{
			if (mState == PlayerState::Idle || mState == PlayerState::Run)
			{
				mState = PlayerState::Death;
				mCurrentAnimation->Stop();
				mCurrentAnimation = mLeftDeathAnimation;
				mCurrentAnimation->Play();
				mCurrentImage = mDeathImage;
			}
		}
		if (mDirection == Direction::Right)
		{
			if (mState == PlayerState::Idle || mState == PlayerState::Run)
			{
				mState = PlayerState::Death;
				mCurrentAnimation->Stop();
				mCurrentAnimation = mRightDeathAnimation;
				mCurrentAnimation->Play();
				mCurrentImage = mDeathImage;
			}
		}
	}

<<<<<<< HEAD
	//	if (Input::GetInstance()->GetKeyDown(VK_SPACE))
		// �÷��� �浹
=======
	// ?Œëž«??ì¶©ëŒ
>>>>>>> 2227e69f15c6377d0d57bf15a56de711be084afe
	if (COLLISIONMANAGER->IsCollideWithPlatform(&mRect))
	{
		mJumpPower = 0;
		mGravity = 0;
		if (mDirection == Direction::Left)
		{
			if (mState == PlayerState::Fall)
			{
				mState = PlayerState::LandSoft;
				mCurrentAnimation->Stop();
				mCurrentAnimation = mLeftLandSoftAnimation;
				mCurrentAnimation->Play();
				mCurrentImage = mLandSoftImage;
			}
		}
		if (mDirection == Direction::Right)
		{
			if (mState == PlayerState::Fall)
			{
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
			if (mDirection == Direction::Left)
			{
				mState = PlayerState::Fall;
				mCurrentAnimation->Stop();
				mCurrentAnimation = mLeftFallAnimation;
				mCurrentAnimation->Play();
				mCurrentImage = mFallImage;
			}
			if (mDirection == Direction::Right)
			{
				mState = PlayerState::Fall;
				mCurrentAnimation->Stop();
				mCurrentAnimation = mRightFallAnimation;
				mCurrentAnimation->Play();
				mCurrentImage = mFallImage;
			}
		}
	}

	// ?í”„
	if (Input::GetInstance()->GetKeyDown(VK_SPACE))
	{
		mJumpPower = 8.f;
		mGravity = 0.2f;

		if (mDirection == Direction::Left)
		{
			if (mState == PlayerState::Idle || mState == PlayerState::Run)
			{
				mState = PlayerState::Jump;
				mCurrentAnimation->Stop();
				mCurrentAnimation = mLeftJumpAnimation;
				mCurrentAnimation->Play();
				mCurrentImage = mJumpImage;
			}
		}
		if (mDirection == Direction::Right)
		{
			if (mState == PlayerState::Idle || mState == PlayerState::Run)
			{
				mState = PlayerState::Jump;
				mCurrentAnimation->Stop();
				mCurrentAnimation = mRightJumpAnimation;
				mCurrentAnimation->Play();
				mCurrentImage = mJumpImage;
			}
		}
	}
	if (mState == PlayerState::Jump)
	{
		if (INPUT->GetKeyDown(VK_LEFT))
		{
			mDirection = Direction::Left;
			mCurrentAnimation->Stop();
			mCurrentAnimation = mLeftJumpAnimation;
			mCurrentAnimation->Play();
			mCurrentImage = mJumpImage;
		}
		if (INPUT->GetKeyDown(VK_RIGHT))
		{
			mDirection = Direction::Right;
			mCurrentAnimation->Stop();
			mCurrentAnimation = mRightJumpAnimation;
			mCurrentAnimation->Play();
			mCurrentImage = mJumpImage;
		}
		if (mJumpPower < 0 && mDirection == Direction::Left)
		{
			mState = PlayerState::Fall;
			mCurrentAnimation->Stop();
			mCurrentAnimation = mLeftFallAnimation;
			mCurrentAnimation->Play();
			mCurrentImage = mFallImage;
		}
		if (mJumpPower < 0 && mDirection == Direction::Right)
		{
			mState = PlayerState::Fall;
			mCurrentAnimation->Stop();
			mCurrentAnimation = mRightFallAnimation;
			mCurrentAnimation->Play();
			mCurrentImage = mFallImage;
		}
	}
<<<<<<< HEAD
	//if (mState == State::LeftFall || mState == State::RightFall || mState == State::LeftJump || mState == State::RightJump)
	if (mState == PlayerState::Fall || mState == PlayerState::Jump)
=======
	if (mState == PlayerState::Fall)
	{
		if (INPUT->GetKeyDown(VK_LEFT))
		{
			mDirection = Direction::Left;
			mCurrentAnimation->Stop();
			mCurrentAnimation = mLeftFallAnimation;
			mCurrentAnimation->Play();
			mCurrentImage = mFallImage;
		}
		if (INPUT->GetKeyDown(VK_RIGHT))
		{
			mDirection = Direction::Right;
			mCurrentAnimation->Stop();
			mCurrentAnimation = mRightFallAnimation;
			mCurrentAnimation->Play();
			mCurrentImage = mFallImage;
		}
	}
	if (mState == PlayerState::Fall || mState == PlayerState::Jump || mState == PlayerState::AirBow || mState == PlayerState::AirAttack)
>>>>>>> 2227e69f15c6377d0d57bf15a56de711be084afe
	{
		mY -= mJumpPower;
		mJumpPower -= mGravity;
	}

<<<<<<< HEAD
	//�����ð�
	if (mState == PlayerState::Roll || mState == PlayerState::Hurt)
	{
		invincibility = 1;
	}
	if (mState != PlayerState::Roll || mState != PlayerState::Hurt)
	{
		invincibility = 0;
	}
	if (invincibility == 0)
	{
	
	}

	// ������ ����
	//if (mState == State::LeftCrouch || mState == State::RightCrouch || mState == State::LeftLandSoft || mState == State::RightLandSoft || 
	//	mState == State::LeftAttack1 || mState == State::LeftAttack2 || mState == State::LeftAttack3) // <- Ȥ�� right attack 1~3 �� ������ �ִ���?
	if(mState == PlayerState::Crouch || mState == PlayerState::LandSoft || mState == PlayerState::Attack1 || mState == PlayerState::Attack2 || mState == PlayerState::Attack3 || mState == PlayerState::Hurt)
=======
	//IDLE || BRAKE 상태에서 이동 키 눌려있을때
	if (mState == PlayerState::Idle || mState == PlayerState::Brake)
	{
		if (INPUT->GetKey(VK_LEFT))
		{
			mDirection = Direction::Left;
			mState = PlayerState::Run;
			mCurrentAnimation->Stop();
			mCurrentAnimation = mLeftRunAnimation;
			mCurrentAnimation->Play();
			mCurrentImage = mRunImage;
		}
		if (INPUT->GetKey(VK_RIGHT))
		{
			mDirection = Direction::Right;
			mState = PlayerState::Run;
			mCurrentAnimation->Stop();
			mCurrentAnimation = mRightRunAnimation;
			mCurrentAnimation->Play();
			mCurrentImage = mRunImage;
		}
	}

	// 움직임 제한
	if (mState == PlayerState::Crouch || mState == PlayerState::Roll || mState == PlayerState::LandSoft || mState == PlayerState::Attack1 || mState == PlayerState::Bow
		|| mState == PlayerState::Attack2 || mState == PlayerState::Attack3 || mState == PlayerState::UseItem || mState == PlayerState::Death || mState == PlayerState::Hurt)
>>>>>>> 2227e69f15c6377d0d57bf15a56de711be084afe
	{
		stopmove = 1;
	}
	if (mState == PlayerState::Idle || mState == PlayerState::Run)
	{
		stopmove = 0;
	}
	if (stopmove == 0)
	{
		mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	}
	mCurrentAnimation->Update();

	//RECT mPrevRect;
	//벽을 통과중이 아니라면
	if (!mIsInDownPlatform) 
	{
		mRect = *(COLLISIONMANAGER->CollideWithPlatform(&mRect, &mPrevRect, mSizeX, mSizeY));
	}
	//벽을 통과중이면
	else
	{
		mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	}
	mX = (mRect.left + mRect.right) / 2;
	mY = (mRect.bottom + mRect.top) / 2;
	mPrevRect = mRect;

	/////////////////////////////////////////임시 체력깎기///////////////////////////
	if (INPUT->GetKeyDown('O'))
	{
		PlayerHurt(Direction::Left);
		mHp -= 20;
	}
  
	//히트박스
	if (mState != PlayerState::Hurt && mState != PlayerState::Roll && mState != PlayerState::Crouch && mState != PlayerState::CrouchBow)
	{
		mHitBox = RectMakeCenter((int)mX, (int)mY, (int)(mSizeX / 3.f), (int)mSizeY);
	}
}

void Player::Render(HDC hdc)
{
	//CAMERAMANAGER->GetMainCamera()->RenderRectInCamera(hdc, mRect);
	CAMERAMANAGER->GetMainCamera()->RenderRectInCamera(hdc, mHitBox);

	CameraManager::GetInstance()->GetMainCamera()->AlphaScaleFrameRender(hdc, mCurrentImage, (int)mRect.left, (int)mRect.top, mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY(), (int)mSizeX, (int)mSizeY, 1.f);

	wstring str3 = L"mX:" + to_wstring(mX);
	TextOut(hdc, _mousePosition.x + 10, _mousePosition.y + 10, str3.c_str(), str3.length());
	wstring str4 = L"mY:" + to_wstring(mY);
	TextOut(hdc, _mousePosition.x + 10, _mousePosition.y + 30, str4.c_str(), str4.length());
	wstring str5 = L"Gravity:" + to_wstring(mGravity);
	TextOut(hdc, _mousePosition.x + 10, _mousePosition.y + 50, str5.c_str(), str5.length());
	wstring str6 = L"jumppower" + to_wstring(mJumpPower);
	TextOut(hdc, _mousePosition.x + 10, _mousePosition.y + 70, str6.c_str(), str6.length());
	wstring str7;
	if (stopmove)
		str7 = L"StopMove == true";
	else
		str7 = L"StopMove == false";
	TextOut(hdc, _mousePosition.x + 10, _mousePosition.y + 90, str7.c_str(), str7.length());

	wstring str8 = L"mState" + to_wstring((int)mState);
	TextOut(hdc, _mousePosition.x + 10, _mousePosition.y + 110, str8.c_str(), str8.length());

	wstring str9 = L"mHP" + to_wstring(mHp);
	TextOut(hdc, _mousePosition.x + 10, _mousePosition.y + 130, str9.c_str(), str9.length());
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
	mUseItemImage = IMAGEMANAGER->FindImage(L"UseItem");
}

void Player::ReadyPlayerAnimation()
{
	// ?¤íƒ ??? ë‹ˆë©”ì´??
	mLeftIdleAnimation = new Animation();
	mLeftIdleAnimation->InitFrameByStartEnd(0, 1, 5, 1, true);
	mLeftIdleAnimation->SetIsLoop(true);
	mLeftIdleAnimation->SetFrameUpdateTime(0.2f);

	mRightIdleAnimation = new Animation();
	mRightIdleAnimation->InitFrameByStartEnd(0, 0, 5, 0, false);
	mRightIdleAnimation->SetIsLoop(true);
	mRightIdleAnimation->SetFrameUpdateTime(0.2f);

		// ?´ë™ ? ë‹ˆë©”ì´??
	mLeftRunStartAnimation = new Animation();
	mLeftRunStartAnimation->InitFrameByStartEnd(8, 1, 9, 1, true);
	mLeftRunStartAnimation->SetIsLoop(false);
	mLeftRunStartAnimation->SetFrameUpdateTime(0.1f);
	mLeftRunStartAnimation->SetCallbackFunc(bind(&Player::SetStateRun, this));

	mLeftRunAnimation = new Animation();
	mLeftRunAnimation->InitFrameByStartEnd(0, 1, 7, 1, true);
	mLeftRunAnimation->SetIsLoop(true);
	mLeftRunAnimation->SetFrameUpdateTime(0.1f);

	mRightRunStartAnimation = new Animation();
	mRightRunStartAnimation->InitFrameByStartEnd(0, 0, 1, 0, false);
	mRightRunStartAnimation->SetIsLoop(false);
	mRightRunStartAnimation->SetFrameUpdateTime(0.1f);
	mRightRunStartAnimation->SetCallbackFunc(bind(&Player::SetStateRun, this));

	mRightRunAnimation = new Animation();
	mRightRunAnimation->InitFrameByStartEnd(2, 0, 9, 0, false);
	mRightRunAnimation->SetIsLoop(true);
	mRightRunAnimation->SetFrameUpdateTime(0.1f);

		// ë¸Œë ˆ?´í¬ ? ë‹ˆë©”ì´??
	mLeftBrakeAnimation = new Animation();
	mLeftBrakeAnimation->InitFrameByStartEnd(0, 1, 6, 1, true);
	mLeftBrakeAnimation->SetIsLoop(true);
	mLeftBrakeAnimation->SetFrameUpdateTime(0.05f);
	mLeftBrakeAnimation->SetCallbackFunc(bind(&Player::SetStateIdle, this));

	mRightBrakeAnimation = new Animation();
	mRightBrakeAnimation->InitFrameByStartEnd(0, 0, 6, 0, false);
	mRightBrakeAnimation->SetIsLoop(true);
	mRightBrakeAnimation->SetFrameUpdateTime(0.05f);
	mRightBrakeAnimation->SetCallbackFunc(bind(&Player::SetStateIdle, this));

	// ë°©í–¥ ?„í™˜ ? ë‹ˆë©”ì´??
	mLeftTurnAnimation = new Animation();
	mLeftTurnAnimation->InitFrameByStartEnd(0, 1, 2, 1, true);
	mLeftTurnAnimation->SetIsLoop(false);
	mLeftTurnAnimation->SetFrameUpdateTime(0.1f);
	mLeftTurnAnimation->SetCallbackFunc(bind(&Player::SetStateRun, this));

	mRightTurnAnimation = new Animation();
	mRightTurnAnimation->InitFrameByStartEnd(0, 0, 2, 0, false);
	mRightTurnAnimation->SetIsLoop(false);
	mRightTurnAnimation->SetFrameUpdateTime(0.1f);
	mRightTurnAnimation->SetCallbackFunc(bind(&Player::SetStateRun, this));

	// ?í”„ ? ë‹ˆë©”ì´??
	mLeftJumpAnimation = new Animation();
	mLeftJumpAnimation->InitFrameByStartEnd(0, 1, 2, 1, true);
	mLeftJumpAnimation->SetIsLoop(true);
	mLeftJumpAnimation->SetFrameUpdateTime(0.2f);

	mRightJumpAnimation = new Animation();
	mRightJumpAnimation->InitFrameByStartEnd(0, 0, 2, 0, false);
	mRightJumpAnimation->SetIsLoop(true);
	mRightJumpAnimation->SetFrameUpdateTime(0.2f);

		// ?í”„ ?˜ê°• ? ë‹ˆë©”ì´??
	mLeftFallAnimation = new Animation();
	mLeftFallAnimation->InitFrameByStartEnd(0, 1, 4, 1, true);
	mLeftFallAnimation->SetIsLoop(false);
	mLeftFallAnimation->SetFrameUpdateTime(0.2f);

	mRightFallAnimation = new Animation();
	mRightFallAnimation->InitFrameByStartEnd(0, 0, 4, 0, false);
	mRightFallAnimation->SetIsLoop(false);
	mRightFallAnimation->SetFrameUpdateTime(0.2f);

		// ?½í•œ ì°©ì? ? ë‹ˆë©”ì´??
	mLeftLandSoftAnimation = new Animation();
	mLeftLandSoftAnimation->InitFrameByStartEnd(0, 1, 3, 1, true);
	mLeftLandSoftAnimation->SetIsLoop(true);
	mLeftLandSoftAnimation->SetFrameUpdateTime(0.1f);
	mLeftLandSoftAnimation->SetCallbackFunc(bind(&Player::SetStateIdle, this));

	mRightLandSoftAnimation = new Animation();
	mRightLandSoftAnimation->InitFrameByStartEnd(0, 0, 3, 0, false);
	mRightLandSoftAnimation->SetIsLoop(true);
	mRightLandSoftAnimation->SetFrameUpdateTime(0.1f);
	mRightLandSoftAnimation->SetCallbackFunc(bind(&Player::SetStateIdle, this));

	// ?‰ê¸° ? ë‹ˆë©”ì´??
	mLeftCrouchAnimation = new Animation();
	mLeftCrouchAnimation->InitFrameByStartEnd(0, 1, 3, 1, true);
	mLeftCrouchAnimation->SetIsLoop(false);
	mLeftCrouchAnimation->SetFrameUpdateTime(0.1f);

	mRightCrouchAnimation = new Animation();
	mRightCrouchAnimation->InitFrameByStartEnd(0, 0, 3, 0, false);
	mRightCrouchAnimation->SetIsLoop(false);
	mRightCrouchAnimation->SetFrameUpdateTime(0.1f);

		// ?¼ì–´?˜ê¸° ? ë‹ˆë©”ì´??
	mLeftRiseAnimation = new Animation();
	mLeftRiseAnimation->InitFrameByStartEnd(0, 1, 1, 1, true);
	mLeftRiseAnimation->SetIsLoop(false);
	mLeftRiseAnimation->SetFrameUpdateTime(0.1f);
	mLeftRiseAnimation->SetCallbackFunc(bind(&Player::SetStateIdle, this));

	mRightRiseAnimation = new Animation();
	mRightRiseAnimation->InitFrameByStartEnd(0, 0, 1, 0, false);
	mRightRiseAnimation->SetIsLoop(false);
	mRightRiseAnimation->SetFrameUpdateTime(0.1f);
	mRightRiseAnimation->SetCallbackFunc(bind(&Player::SetStateIdle, this));

	// êµ¬ë¥´ê¸?? ë‹ˆë©”ì´??
	mLeftRollAnimation = new Animation();
	mLeftRollAnimation->InitFrameByStartEnd(0, 1, 7, 1, true);
	mLeftRollAnimation->SetIsLoop(false);
	mLeftRollAnimation->SetFrameUpdateTime(0.07f);
	mLeftRollAnimation->SetCallbackFunc(bind(&Player::SetStateIdle, this));

	mRightRollAnimation = new Animation();
	mRightRollAnimation->InitFrameByStartEnd(0, 0, 7, 0, false);
	mRightRollAnimation->SetIsLoop(false);
	mRightRollAnimation->SetFrameUpdateTime(0.07f);
	mRightRollAnimation->SetCallbackFunc(bind(&Player::SetStateIdle, this));

	// ?¬ë‹¤ë¦??…ìž¥ ? ë‹ˆë©”ì´??
	mLeftLadderEnterAnimation = new Animation();
	mLeftLadderEnterAnimation->InitFrameByStartEnd(0, 1, 5, 1, true);
	mLeftLadderEnterAnimation->SetIsLoop(true);
	mLeftLadderEnterAnimation->SetFrameUpdateTime(0.1f);
	mLeftLadderEnterAnimation->SetCallbackFunc(bind(&Player::SetStateLadderDown, this));

	mRightLadderEnterAnimation = new Animation();
	mRightLadderEnterAnimation->InitFrameByStartEnd(0, 0, 5, 0, false);
	mRightLadderEnterAnimation->SetIsLoop(true);
	mRightLadderEnterAnimation->SetFrameUpdateTime(0.1f);
	mRightLadderEnterAnimation->SetCallbackFunc(bind(&Player::SetStateLadderDown, this));

	// ?¬ë‹¤ë¦??¤ë¥´?´ë¦¬ê¸?? ë‹ˆë©”ì´??
	mLadderUpAnimation = new Animation();
	mLadderUpAnimation->InitFrameByStartEnd(0, 0, 5, 0, true);
	mLadderUpAnimation->SetIsLoop(true);
	mLadderUpAnimation->SetFrameUpdateTime(0.1f);

	mLadderDownAnimation = new Animation();
	mLadderDownAnimation->InitFrameByStartEnd(0, 0, 2, 0, true);
	mLadderDownAnimation->SetIsLoop(true);
	mLadderDownAnimation->SetFrameUpdateTime(0.1f);

		// ?¬ë‹¤ë¦??´ìž¥ ? ë‹ˆë©”ì´??
	mLeftLadderLeaveAnimation = new Animation();
	mLeftLadderLeaveAnimation->InitFrameByStartEnd(0, 1, 5, 1, true);
	mLeftLadderLeaveAnimation->SetIsLoop(true);
	mLeftLadderLeaveAnimation->SetFrameUpdateTime(0.1f);

	mRightLadderLeaveAnimation = new Animation();
	mRightLadderLeaveAnimation->InitFrameByStartEnd(0, 0, 5, 0, false);
	mRightLadderLeaveAnimation->SetIsLoop(true);
	mRightLadderLeaveAnimation->SetFrameUpdateTime(0.1f);

//NH	// ì„œì„œ í™œ ì• ë‹ˆë©”ì´ì…˜
//master		// ?œì„œ ??? ë‹ˆë©”ì´??
	mLeftBowAnimation = new Animation();
	mLeftBowAnimation->InitFrameByStartEnd(0, 1, 5, 1, true);
	mLeftBowAnimation->SetIsLoop(true);
	mLeftBowAnimation->SetFrameUpdateTime(0.1f);
	mLeftBowAnimation->SetCallbackFunc(bind(&Player::SetEndAttack, this));

	mRightBowAnimation = new Animation();
	mRightBowAnimation->InitFrameByStartEnd(0, 0, 5, 0, false);
	mRightBowAnimation->SetIsLoop(true);
	mRightBowAnimation->SetFrameUpdateTime(0.1f);
	mRightBowAnimation->SetCallbackFunc(bind(&Player::SetEndAttack, this));

	// ê³µì¤‘ ??? ë‹ˆë©”ì´??
	mLeftAirBowAnimation = new Animation();
	mLeftAirBowAnimation->InitFrameByStartEnd(0, 1, 5, 1, true);
	mLeftAirBowAnimation->SetIsLoop(true);
	mLeftAirBowAnimation->SetFrameUpdateTime(0.1f);
	mLeftAirBowAnimation->SetCallbackFunc(bind(&Player::SetEndAirAttack, this));

	mRightAirBowAnimation = new Animation();
	mRightAirBowAnimation->InitFrameByStartEnd(0, 0, 5, 0, false);
	mRightAirBowAnimation->SetIsLoop(true);
	mRightAirBowAnimation->SetFrameUpdateTime(0.1f);
	mRightAirBowAnimation->SetCallbackFunc(bind(&Player::SetEndAirAttack, this));

	// ?‰ì•„ ??? ë‹ˆë©”ì´??
	mLeftCrouchBowAnimation = new Animation();
	mLeftCrouchBowAnimation->InitFrameByStartEnd(0, 1, 5, 1, true);
	mLeftCrouchBowAnimation->SetIsLoop(true);
	mLeftCrouchBowAnimation->SetFrameUpdateTime(0.1f);
	mLeftCrouchBowAnimation->SetCallbackFunc(bind(&Player::SetEndCrouchAttack, this));

	mRightCrouchBowAnimation = new Animation();
	mRightCrouchBowAnimation->InitFrameByStartEnd(0, 0, 5, 0, false);
	mRightCrouchBowAnimation->SetIsLoop(true);
	mRightCrouchBowAnimation->SetFrameUpdateTime(0.1f);
	mRightCrouchBowAnimation->SetCallbackFunc(bind(&Player::SetEndCrouchAttack, this));

	// ì²?ë²ˆì§¸ ê³µê²© ? ë‹ˆë©”ì´??
	mLeftAttack1Animation = new Animation();
	mLeftAttack1Animation->InitFrameByStartEnd(0, 1, 6, 1, true);
	mLeftAttack1Animation->SetIsLoop(true);
	mLeftAttack1Animation->SetFrameUpdateTime(0.1f);
	mLeftAttack1Animation->SetCallbackFunc(bind(&Player::SetEndAttack, this));

	mRightAttack1Animation = new Animation();
	mRightAttack1Animation->InitFrameByStartEnd(0, 0, 6, 0, false);
	mRightAttack1Animation->SetIsLoop(true);
	mRightAttack1Animation->SetFrameUpdateTime(0.1f);
	mRightAttack1Animation->SetCallbackFunc(bind(&Player::SetEndAttack, this));

	// ??ë²ˆì§¸ ê³µê²© ? ë‹ˆë©”ì´??
	mLeftAttack2Animation = new Animation();
	mLeftAttack2Animation->InitFrameByStartEnd(0, 1, 6, 1, true);
	mLeftAttack2Animation->SetIsLoop(true);
	mLeftAttack2Animation->SetFrameUpdateTime(0.1f);
	mLeftAttack2Animation->SetCallbackFunc(bind(&Player::SetEndAttack, this));

	mRightAttack2Animation = new Animation();
	mRightAttack2Animation->InitFrameByStartEnd(0, 0, 6, 0, false);
	mRightAttack2Animation->SetIsLoop(true);
	mRightAttack2Animation->SetFrameUpdateTime(0.1f);
	mRightAttack2Animation->SetCallbackFunc(bind(&Player::SetEndAttack, this));

	// ??ë²ˆì§¸ ê³µê²© ? ë‹ˆë©”ì´??
	mLeftAttack3Animation = new Animation();
	mLeftAttack3Animation->InitFrameByStartEnd(0, 1, 10, 1, true);
	mLeftAttack3Animation->SetIsLoop(true);
	mLeftAttack3Animation->SetFrameUpdateTime(0.1f);
	mLeftAttack3Animation->SetCallbackFunc(bind(&Player::SetEndAttack, this));

	mRightAttack3Animation = new Animation();
	mRightAttack3Animation->InitFrameByStartEnd(0, 0, 10, 0, false);
	mRightAttack3Animation->SetIsLoop(true);
	mRightAttack3Animation->SetFrameUpdateTime(0.1f);
	mRightAttack3Animation->SetCallbackFunc(bind(&Player::SetEndAttack, this));

	// ê³µì¤‘ ê³µê²© ? ë‹ˆë©”ì´??
	mLeftAirAttackAnimation = new Animation();
	mLeftAirAttackAnimation->InitFrameByStartEnd(0, 1, 6, 1, true);
	mLeftAirAttackAnimation->SetIsLoop(true);
	mLeftAirAttackAnimation->SetFrameUpdateTime(0.1f);
	mLeftAirAttackAnimation->SetCallbackFunc(bind(&Player::SetEndAirAttack, this));

	mRightAirAttackAnimation = new Animation();
	mRightAirAttackAnimation->InitFrameByStartEnd(0, 0, 6, 0, false);
	mRightAirAttackAnimation->SetIsLoop(true);
	mRightAirAttackAnimation->SetFrameUpdateTime(0.1f);
	mRightAirAttackAnimation->SetCallbackFunc(bind(&Player::SetEndAirAttack, this));

	// ?¼ê²© ? ë‹ˆë©”ì´??
	mLeftHurtAnimation = new Animation();
	mLeftHurtAnimation->InitFrameByStartEnd(0, 1, 1, 1, true);
	mLeftHurtAnimation->SetIsLoop(true);
	mLeftHurtAnimation->SetFrameUpdateTime(0.3f);

	mRightHurtAnimation = new Animation();
	mRightHurtAnimation->InitFrameByStartEnd(0, 0, 1, 0, false);
	mRightHurtAnimation->SetIsLoop(true);
	mRightHurtAnimation->SetFrameUpdateTime(0.3f);

		// ?¬ë§ ? ë‹ˆë©”ì´??
	mLeftDeathAnimation = new Animation();
	mLeftDeathAnimation->InitFrameByStartEnd(0, 1, 23, 1, true);
	mLeftDeathAnimation->SetIsLoop(false);
	mLeftDeathAnimation->SetFrameUpdateTime(0.2f);

	mRightDeathAnimation = new Animation();
	mRightDeathAnimation->InitFrameByStartEnd(0, 0, 23, 0, false);
	mRightDeathAnimation->SetIsLoop(false);
	mRightDeathAnimation->SetFrameUpdateTime(0.2f);

		//?„ì´???¬ìš© ? ë‹ˆë©”ì´??
	mLeftUseItemAnimation = new Animation();
	mLeftUseItemAnimation->InitFrameByStartEnd(0, 1, 10, 1, true);
	mLeftUseItemAnimation->SetIsLoop(false);
	mLeftUseItemAnimation->SetFrameUpdateTime(0.1f);
	mLeftUseItemAnimation->SetCallbackFunc(bind(&Player::SetStateIdle, this));

	mRightUseItemAnimation = new Animation();
	mRightUseItemAnimation->InitFrameByStartEnd(0, 0, 10, 0, false);
	mRightUseItemAnimation->SetIsLoop(false);
	mRightUseItemAnimation->SetFrameUpdateTime(0.1f);
	mRightUseItemAnimation->SetCallbackFunc(bind(&Player::SetStateIdle, this));
}

void Player::InitPlayerVar()
{
	// ë¶€ëª??´ëž˜?¤ì¸ GameObject??? ì–¸??ë³€?˜ë“¤
	mName = "Player";
	mX = WINSIZEX / 2.f;
	mY = 200.f;
	mSizeX = (float)(mIdleImage->GetFrameWidth()) * 2.f;
	mSizeY = (float)(mIdleImage->GetFrameHeight()) * 2.f;
	mDirection = Direction::Right;
	mRect = RectMakeCenter((int)mX, (int)mY, (int)mSizeX, (int)mSizeY);
	mHitBox = RectMakeCenter((int)mX, (int)mY, (int)(mSizeX / 3.f), (int)mSizeY); // ?„ì‹œ(ê°€ë¡œë§Œ 1/3)
	mAttackBox = RectMakeCenter((int)mX, (int)mY, (int)mSizeX, (int)mSizeY); // ?„ì‹œ(?Œë ˆ?´ì–´ ?¬ì´ì¦?

	// Player??? ì–¸??ë³€?˜ë“¤
	mArrowSpeed = 600.f;

	mState = PlayerState::Idle;
	mSpeed = 400.f;
	mJumpPower = 0.f;
	mGravity = 0.2f;

	mHp = 99;
	mAttackDamage = 0;
	mPotion = 3;

	mTimer = 0;

	invincibility = 0;
	stopmove = 0;

	mHaveMagnet = false;
	mLeaf = new Leaf();
	mLeaf->Init();
	OBJECTMANAGER->AddObject(ObjectLayer::PlayerLeaf, mLeaf);

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
	if (mDirection == Direction::Left)
	{
		if (mState == PlayerState::Run || mState == PlayerState::Turn)
		{
			mCurrentAnimation->Stop();
			mCurrentAnimation = mLeftRunAnimation;
			mCurrentAnimation->Play();
			mCurrentImage = mRunImage;
		}
	}
	else if (mDirection == Direction::Right)
	{
		if (mState == PlayerState::Run || mState == PlayerState::Turn)
		{
			mCurrentAnimation->Stop();
			mCurrentAnimation = mRightRunAnimation;
			mCurrentAnimation->Play();
			mCurrentImage = mRunImage;
		}
	}
}

void Player::SetStateIdle()
{
	if (mDirection == Direction::Left)
	{
		if (mState == PlayerState::Roll || mState == PlayerState::Rise || mState == PlayerState::Brake || mState == PlayerState::LandSoft || mState == PlayerState::UseItem)
		{
			mState = PlayerState::Idle;
			mCurrentAnimation->Stop();
			mCurrentAnimation = mLeftIdleAnimation;
			mCurrentAnimation->Play();
			mCurrentImage = mIdleImage;
		}
	}
	else if (mDirection == Direction::Right)
	{
		if (mState == PlayerState::Roll || mState == PlayerState::Rise || mState == PlayerState::Brake || mState == PlayerState::LandSoft || mState == PlayerState::UseItem)
		{
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
	if (mDirection == Direction::Left)
	{
		if (mState == PlayerState::Attack1 || mState == PlayerState::Attack2 || mState == PlayerState::Attack3 || mState == PlayerState::Bow)
		{
			mState = PlayerState::Idle;
			mCurrentAnimation->Stop();
			mCurrentAnimation = mLeftIdleAnimation;
			mCurrentAnimation->Play();
			mCurrentImage = mIdleImage;
		}
	}
	if (mDirection == Direction::Right)
	{
		if (mState == PlayerState::Attack1 || mState == PlayerState::Attack2 || mState == PlayerState::Attack3 || mState == PlayerState::Bow)
		{
			mState = PlayerState::Idle;
			mCurrentAnimation->Stop();
			mCurrentAnimation = mRightIdleAnimation;
			mCurrentAnimation->Play();
			mCurrentImage = mIdleImage;
		}
	}

	mEndCombo = true;
	mHitAttack = true;

	mLeaf->SetIsActive(false); // ? ë‹ˆë©”ì´?????Œê³  ì¶œë ¥?????˜ê²Œ
}

void Player::SetEndAirAttack()
{
	if (mDirection == Direction::Left)
	{
		if (mState == PlayerState::AirBow || mState == PlayerState::AirAttack)
		{
			mState = PlayerState::Fall;
			mCurrentAnimation->Stop();
			mCurrentAnimation = mLeftFallAnimation;
			mCurrentAnimation->Play();
			mCurrentImage = mFallImage;
		}
	}
	if (mDirection == Direction::Right)
	{
		if (mState == PlayerState::AirBow || mState == PlayerState::AirAttack)
		{
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
	if (mDirection == Direction::Left)
	{
		if (mState == PlayerState::CrouchBow)
		{
			mState = PlayerState::Crouch;
			mCurrentAnimation->Stop();
			mCurrentAnimation = mLeftCrouchAnimation;
			mCurrentAnimation->Play();
			mCurrentImage = mCrouchImage;
		}
	}
	if (mDirection == Direction::Right)
	{
		if (mState == PlayerState::CrouchBow)
		{
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
	if (mState == PlayerState::LadderEnter)
	{
		mState = PlayerState::LadderUp;
		mCurrentAnimation->Stop();
		mCurrentAnimation = mLadderUpAnimation;
		mCurrentAnimation->Play();
		mCurrentImage = mLadderUpImage;
	}
}

void Player::SetStateLadderDown()
{
	if (mState == PlayerState::LadderEnter)
	{
		mState = PlayerState::LadderDown;
		mCurrentAnimation->Stop();
		mCurrentAnimation = mLadderDownAnimation;
		mCurrentAnimation->Play();
		mCurrentImage = mLadderDownImage;
	}
}
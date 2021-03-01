#include "pch.h"
#include "Fennel.h"
#include "Image.h"
#include "Animation.h"
#include "Camera.h"
#include "Player.h"
#include "Staff.h"
#include "GameObject.h"
#include "Effect.h"
#include "GameEvent.h"

void Fennel::Init()
{
	mImage = IMAGEMANAGER->FindImage(L"Fennelintro1");
	mImpactImg = IMAGEMANAGER->FindImage(L"Fennelimpact");
	mThunderImg = IMAGEMANAGER->FindImage(L"Thunder");
	mFloorEffectImg = IMAGEMANAGER->FindImage(L"FloorEffect");




	mStart.x = 2000;
	mStart.y = 2000;
	mX = mStart.x;
	mY = mStart.y;
	mSizeX = mImage->GetFrameWidth() * 2;
	mSizeY = mImage->GetFrameHeight() * 2;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	mHitBox = RectMakeCenter(mX, mY, 50, 50);
	mAttackSpeed = 0;
	mName = "Fennel";
	mAlpha = 1;
	isHit = false;

	//스탯 ////// 나중에 바꾸기////////////
	mHp = 500;
	mAtk = 15;
	///////////////////////////////////

	/////충돌판정할 랙트들//////////////////
	mImpact = RectMakeCenter(1000, 2000, 1, 1);
	mThunder = RectMakeCenter(1000, 2000, 1, 1);
	mAttackBox = RectMakeCenter(1000, 2000, 1, 1);
	mFloorEffect = { 2400,2500 };

	mRightIdle = new Animation();
	mRightIdle->InitFrameByStartEnd(0, 1, 4, 1, false);
	mRightIdle->SetIsLoop(true);
	mRightIdle->SetFrameUpdateTime(0.2f);

	mLeftIdle = new Animation();
	mLeftIdle->InitFrameByStartEnd(0, 0, 4, 0, false);
	mLeftIdle->SetIsLoop(true);
	mLeftIdle->SetFrameUpdateTime(0.2f);

	mRightAtk = new Animation();
	mRightAtk->InitFrameByStartEnd(0, 1, 22, 1, false);
	mRightAtk->SetIsLoop(false);
	mRightAtk->SetFrameUpdateTime(0.06f);
	mRightAtk->SetCallbackFunc(bind(&Fennel::EndAttack2, this));

	mLeftAtk = new Animation();
	mLeftAtk->InitFrameByStartEnd(0, 0, 22, 0, false);
	mLeftAtk->SetIsLoop(false);
	mLeftAtk->SetFrameUpdateTime(0.06f);
	mLeftAtk->SetCallbackFunc(bind(&Fennel::EndAttack2, this));

	mRightAtk2 = new Animation();
	mRightAtk2->InitFrameByStartEnd(0, 1, 11, 1, false);
	mRightAtk2->SetIsLoop(false);
	mRightAtk2->SetFrameUpdateTime(0.06f);
	mRightAtk2->SetCallbackFunc(bind(&Fennel::EndAttack2, this));

	mLeftAtk2 = new Animation();
	mLeftAtk2->InitFrameByStartEnd(0, 0, 11, 0, false);
	mLeftAtk2->SetIsLoop(false);
	mLeftAtk2->SetFrameUpdateTime(0.06f);
	mLeftAtk2->SetCallbackFunc(bind(&Fennel::EndAttack2, this));

	mRightBackflip = new Animation();
	mRightBackflip->InitFrameByStartEnd(0, 1, 12, 1, false);
	mRightBackflip->SetIsLoop(false);
	mRightBackflip->SetFrameUpdateTime(0.1f);
	mRightBackflip->SetCallbackFunc(bind(&Fennel::EndMove, this));

	mLeftBackflip = new Animation();
	mLeftBackflip->InitFrameByStartEnd(0, 0, 12, 0, false);
	mLeftBackflip->SetIsLoop(false);
	mLeftBackflip->SetFrameUpdateTime(0.1f);
	mLeftBackflip->SetCallbackFunc(bind(&Fennel::EndMove, this));

	mRightBuff = new Animation();
	mRightBuff->InitFrameByStartEnd(0, 1, 14, 1, false);
	mRightBuff->SetIsLoop(false);
	mRightBuff->SetFrameUpdateTime(0.2f);
	mRightBuff->SetCallbackFunc(bind(&Fennel::EndBuff, this));

	mLeftBuff = new Animation();
	mLeftBuff->InitFrameByStartEnd(0, 0, 14, 0, false);
	mLeftBuff->SetIsLoop(false);
	mLeftBuff->SetFrameUpdateTime(0.2f);
	mLeftBuff->SetCallbackFunc(bind(&Fennel::EndBuff, this));

	mRightDash = new Animation();
	mRightDash->InitFrameByStartEnd(0, 1, 0, 1, false);
	mRightDash->SetIsLoop(false);
	mRightDash->SetFrameUpdateTime(0.2f);
//	mRightDash->SetCallbackFunc(bind(&Fennel::EndMove, this));

	mLeftDash = new Animation();
	mLeftDash->InitFrameByStartEnd(0, 0, 0, 0, false);
	mLeftDash->SetIsLoop(false);
	mLeftDash->SetFrameUpdateTime(0.2f);
	//mLeftDash->SetCallbackFunc(bind(&Fennel::EndMove, this));

	mRightDeath = new Animation();
	mRightDeath->InitFrameByStartEnd(0, 1, 0, 1, false);
	mRightDeath->SetIsLoop(false);
	mRightDeath->SetFrameUpdateTime(0.2f);
	mRightDeath->SetCallbackFunc(bind(&Fennel::EndDeath, this));

	mLeftDeath = new Animation();
	mLeftDeath->InitFrameByStartEnd(0, 0, 13, 0, false);
	mLeftDeath->SetIsLoop(false);
	mLeftDeath->SetFrameUpdateTime(0.2f);
	mLeftDeath->SetCallbackFunc(bind(&Fennel::EndDeath, this));

	mRightHurt = new Animation();
	mRightHurt->InitFrameByStartEnd(0, 1, 0, 1, false);
	mRightHurt->SetIsLoop(false);
	mRightHurt->SetFrameUpdateTime(2.f);
	mRightHurt->SetCallbackFunc(bind(&Fennel::EndMove, this));

	mLeftHurt = new Animation();
	mLeftHurt->InitFrameByStartEnd(0, 0, 0, 0, false);
	mLeftHurt->SetIsLoop(false);
	mLeftHurt->SetFrameUpdateTime(2.f);
	mLeftHurt->SetCallbackFunc(bind(&Fennel::EndMove, this));

	mRightIdle = new Animation();
	mRightIdle->InitFrameByStartEnd(0, 1, 4, 1, false);
	mRightIdle->SetIsLoop(true);
	mRightIdle->SetFrameUpdateTime(0.2f);

	mLeftIdle = new Animation();
	mLeftIdle->InitFrameByStartEnd(0, 0, 4, 0, false);
	mLeftIdle->SetIsLoop(true);
	mLeftIdle->SetFrameUpdateTime(0.2f);

	mRightJump = new Animation();
	mRightJump->InitFrameByStartEnd(0, 1, 6, 1, false);
	mRightJump->SetIsLoop(false);
	mRightJump->SetFrameUpdateTime(0.2f);
	mRightJump->SetCallbackFunc(bind(&Fennel::JumptoPlunge, this));

	mLeftJump = new Animation();
	mLeftJump->InitFrameByStartEnd(0, 0, 6, 0, false);
	mLeftJump->SetIsLoop(false);
	mLeftJump->SetFrameUpdateTime(0.2f);
	mLeftJump->SetCallbackFunc(bind(&Fennel::JumptoPlunge, this));

	mRightJumpReady = new Animation();
	mRightJumpReady->InitFrameByStartEnd(0, 1, 4, 1, false);
	mRightJumpReady->SetIsLoop(false);
	mRightJumpReady->SetFrameUpdateTime(0.2f);
	mRightJumpReady->SetCallbackFunc(bind(&Fennel::JumpReadytoJump, this));

	mLeftJumpReady = new Animation();
	mLeftJumpReady->InitFrameByStartEnd(0, 0, 4, 0, false);
	mLeftJumpReady->SetIsLoop(false);
	mLeftJumpReady->SetFrameUpdateTime(0.2f);
	mLeftJumpReady->SetCallbackFunc(bind(&Fennel::JumpReadytoJump, this));

	mRightPlunge = new Animation();
	mRightPlunge->InitFrameByStartEnd(0, 1, 12, 1, false);
	mRightPlunge->SetIsLoop(false);
	mRightPlunge->SetFrameUpdateTime(0.1f);
	mRightPlunge->SetCallbackFunc(bind(&Fennel::EndPlunge, this));

	mLeftPlunge = new Animation();
	mLeftPlunge->InitFrameByStartEnd(0, 0, 12, 0, false);
	mLeftPlunge->SetIsLoop(false);
	mLeftPlunge->SetFrameUpdateTime(0.1f);
	mLeftPlunge->SetCallbackFunc(bind(&Fennel::EndPlunge, this));

	mRightThunder = new Animation();
	mRightThunder->InitFrameByStartEnd(0, 1, 21, 1, false);
	mRightThunder->SetIsLoop(false);
	mRightThunder->SetFrameUpdateTime(0.1f);
	mRightThunder->SetCallbackFunc(bind(&Fennel::EndMove, this));

	mLeftThunder = new Animation();
	mLeftThunder->InitFrameByStartEnd(0, 0, 21, 0, false);
	mLeftThunder->SetIsLoop(false);
	mLeftThunder->SetFrameUpdateTime(0.1f);
	mLeftThunder->SetCallbackFunc(bind(&Fennel::EndMove, this));

	mImpactAni = new Animation();
	mImpactAni->InitFrameByStartEnd(0, 0, 7, 0, false);
	mImpactAni->SetIsLoop(false);
	mImpactAni->SetFrameUpdateTime(0.1f);
	mCurrentImpact = mImpactAni;
	//mCurrentImpact->Play();

	mThunderAni = new Animation();
	mThunderAni->InitFrameByStartEnd(0, 0, 2, 0, false);
	mThunderAni->SetIsLoop(true);
	mThunderAni->SetFrameUpdateTime(0.05f);
	mCurrentThunder = mThunderAni;
	mCurrentThunder->Play();
	mCurrentThunder->Pause();

	mFloorAni = new Animation();
	mFloorAni->InitFrameByStartEnd(0, 0, 6, 0, false);
	mFloorAni->SetIsLoop(true);
	mFloorAni->SetFrameUpdateTime(0.1f);
	mCurrentFloor = mFloorAni;
	mCurrentFloor->Play();
	mCurrentFloor->Pause();

	mIntro1 = new Animation();
	mIntro1->InitFrameByStartEnd(0, 0, 17, 0, false);
	mIntro1->SetIsLoop(false);
	mIntro1->SetFrameUpdateTime(0.2f);
	mIntro1->SetCallbackFunc(bind(&Fennel::EndIntro1, this));

	mIntro2 = new Animation();
	mIntro2->InitFrameByStartEnd(0, 0, 7, 0, false);
	mIntro2->SetIsLoop(false);
	mIntro2->SetFrameUpdateTime(0.1f);
	mIntro2->SetCallbackFunc(bind(&Fennel::EndIntro2, this));

	mIntro3 = new Animation();
	mIntro3->InitFrameByStartEnd(0, 0, 13, 0, false);
	mIntro3->SetIsLoop(false);
	mIntro3->SetFrameUpdateTime(0.1f);
	mIntro3->SetCallbackFunc(bind(&Fennel::EndIntro3, this));

	mFennelState = FennelState::Intro;
	mDirection = Direction::Left;
	mCurrentAnimation = mIntro1;
	mCurrentAnimation->Play();

	//잔상
	for (int i = 3;i > 0;i--)
	{
		AfterImage afterImage1;
		afterImage1.cImage = mImage;
		afterImage1.cAnimation = mCurrentAnimation;
		afterImage1.cAlpha = 0.8;
		mAfterImages.push_back(afterImage1);
	}
}

void Fennel::Release()
{
	SafeDelete(mRightIdle);
	SafeDelete(mLeftIdle);
	SafeDelete(mRightAtk);
	SafeDelete(mLeftAtk);
	SafeDelete(mRightHurt);
	SafeDelete(mLeftHurt);
	SafeDelete(mRightBuff);
	SafeDelete(mLeftBuff);
	SafeDelete(mRightDeath);
	SafeDelete(mLeftDeath);
	SafeDelete(mRightAtk2);
	SafeDelete(mLeftAtk2);
	SafeDelete(mRightBackflip);
	SafeDelete(mLeftBackflip);
	SafeDelete(mRightPlunge);
	SafeDelete(mLeftPlunge);
	SafeDelete(mRightDeath);
	SafeDelete(mLeftDeath);
	SafeDelete(mRightThunder);
	SafeDelete(mLeftThunder);
	SafeDelete(mRightJumpReady);
	SafeDelete(mLeftJumpReady);
	SafeDelete(mThunderAni);
	SafeDelete(mImpactAni);
	SafeDelete(mFloorAni);
	SafeDelete(mIntro1);
	SafeDelete(mIntro2);
	SafeDelete(mIntro3);
}

void Fennel::Update()
{
	
	if (INPUT->GetKeyDown('P'))
	{
		mHp -= 100;
	}


	if (mFennelState == FennelState::Idle)
	{
		mAttackSpeed += TIME->DeltaTime();
		if (mAttackSpeed > 1)
		{
			//확률= RANDOM->RandomInt(3)
			//int rand = 0;
			int rand = RANDOM->RandomInt(3);
			if (rand == 0)
			{
				//거리가멀면 대쉬후 공격
				if (Math::GetDistance(mPlayer->GetX(), 0, mX, 0) > 200)
				{
					Dash();
				}
				//거리가 가까우면 그냥 공격
				else
				{
					Attack();
			
				}
			}
			else if(rand == 1)
			{
				Plunge();
			}
			else
			{
				Thunder();
			}

			//버프넣기
			if (mAtk < 20)
			{
				if (mHp < 200)
				{
					mAtk = 30;
					Buff();
				}
			}
			//else
			//{
			//	int rand = RANDOM->RandomInt(3);
			//	if (rand == 0)
			//	{
			//		//거리가멀면 대쉬후 공격
			//		if (Math::GetDistance(mPlayer->GetX(), 0, mX, 0) > 200)
			//		{
			//			Dash();
			//		}
			//		//거리가 가까우면 그냥 공격
			//		else
			//		{
			//			Attack();
			//			SOUNDMANAGER->Play(L"FennelAtk", 0.2f);
			//
			//
			//		}
			//	}
			//	else if (rand == 1)
			//	{
			//		Plunge();
			//	}
			//	else
			//	{
			//		Thunder();
			//	}
			//}

		}
	}
	
	//공격떄 이동
	if (mFennelState == FennelState::Attack)
	{
		AttackRect();
	}
	//공격2 이동
	if (mFennelState == FennelState::Attack2)
	{
		Attack2Rect();
	}
	//뒷구르기 이동
	if (mFennelState == FennelState::BackFlip)
	{
		BackflipRect();
	}
	//점프 이동
	if (mFennelState == FennelState::Jump)
	{
		JumpRect();
	}
	//찍기
	if (mFennelState == FennelState::Plunge)
	{
		PlungeRect();
	}
	//번개
	if (mFennelState == FennelState::Thunder)
	{
		ThunderRect();
	}
	//대시
	if (mFennelState == FennelState::Dash)
	{
		DashRect();
	}

	//맞으면
	//if (isHit)
	//{
	//	SetDirection();
	//	//mFennelState == FennelState::Hurt;
	//	SetImageAnimation();
	//	isHit = false;
	//}

	//죽어 알파값도 1보다작게
	if (mHp < 0 && mFennelState != FennelState::Death)
	{
		SetDirection();
		mFennelState = FennelState::Death;
		SetImageAnimation();
	}
	//알파값이 바뀌어있으면 계속 내려가게
	if (mAlpha > 0 && mAlpha < 1)
		mAlpha -= TIME->DeltaTime();
	//알파값이 0이면 삭제
	if (mAlpha <= 0)
	{ 
		DropGold(20);
		this->SetIsDestroy(true);
	}
	mCurrentImpact->Update();
	mCurrentAnimation->Update();
	mCurrentThunder->Update();
	mCurrentFloor->Update();
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);

	//잔상 알파값조정
	for (int i = 0;i < 3;i++)
	{
		if (mAfterImages[i].cAlpha > 0 && mAfterImages[i].cAlpha < 0.8)
			mAfterImages[i].cAlpha -= TIME->DeltaTime();
		if (mAfterImages[i].cAlpha <= 0)
		{
			mAfterImages[i].cAlpha = 0.8f;
			mAfterImages[i].cRect = RectMakeCenter(2000, 2000, 1, 1);
		}
	}

	//히트박스
	if(mDirection == Direction::Left)
		mHitBox = RectMakeCenter(mX + 10, mY, 50, 100);
	else
		mHitBox = RectMakeCenter(mX - 10, mY, 50, 100);

}

void Fennel::Render(HDC hdc)
{
	//CAMERAMANAGER->GetMainCamera()->RenderRectInCamera(hdc, mHitBox);
	//CAMERAMANAGER->GetMainCamera()->RenderRectInCamera(hdc, mAttackBox);
	//페넬
	CAMERAMANAGER->GetMainCamera()->AlphaScaleFrameRender(hdc, mImage, mRect.left, mRect.top, mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY(), mSizeX, mSizeY,mAlpha);
	//임팩트
	CAMERAMANAGER->GetMainCamera()->AlphaScaleFrameRender(hdc, mImpactImg, mImpact.left, mImpact.top, mCurrentImpact->GetNowFrameX(), mCurrentImpact->GetNowFrameY(), mImpactImg->GetFrameWidth() * 2, mImpactImg->GetFrameHeight() * 2, 0.5f);
	//번개
	CAMERAMANAGER->GetMainCamera()->ScaleFrameRender(hdc, mThunderImg, mThunder.left, mThunder.top, mCurrentThunder->GetNowFrameX(), mCurrentThunder->GetNowFrameY(), mThunderImg->GetFrameWidth() * 2 - 50, 500);
	//버프
	CAMERAMANAGER->GetMainCamera()->AlphaScaleFrameRender(hdc, mFloorEffectImg, mFloorEffect.x, mFloorEffect.y, mCurrentFloor->GetNowFrameX(), mCurrentFloor->GetNowFrameY(), mFloorEffectImg->GetFrameWidth() / 2, mFloorEffectImg->GetFrameHeight() / 2, 0.5);
	//잔상
	for (int i = 0;i < 3;i++)
	{
		CAMERAMANAGER->GetMainCamera()->AlphaScaleFrameRender(hdc, mAfterImages[i].cImage, mAfterImages[i].cRect.left, mAfterImages[i].cRect.top, mAfterImages[i].cFrameX, mAfterImages[i].cFrameY, mSizeX, mSizeY, mAfterImages[i].cAlpha);
	}

}

void Fennel::Attack()
{
	SetDirection();
	mFennelState = FennelState::Attack;
	SetImageAnimation();
}
void Fennel::Attack2()
{
	SetDirection();
	mFennelState = FennelState::Attack2;
	SetImageAnimation();
}
void Fennel::Backflip()
{

}
void Fennel::Plunge()
{
	SetDirection();
	//점프레디는 쓰지않는중
	mFennelState = FennelState::JumpReady;
	mFennelState = FennelState::Jump;
	SetImageAnimation();
}
void Fennel::Thunder()
{
	SetDirection();
	mFennelState = FennelState::Thunder;
	SetImageAnimation();
}
void Fennel::Hurt()
{

}
void Fennel::Buff()
{
	SetDirection();
	mFennelState = FennelState::Buff;
	SetImageAnimation();
	mCurrentFloor->Play();
	//mFloorEffect.x = mX;
	//mFloorEffect.y = mY + 20;
}
void Fennel::Death()
{

}

void Fennel::Dash()
{
	SetDirection();
	mFennelState = FennelState::Dash;
	SetImageAnimation();
}

//공격1 칼렉트
void Fennel::AttackSword()
{
	if (mCurrentAnimation->GetNowFrameX() == 6 || mCurrentAnimation->GetNowFrameX() == 7)
	{
		if (mDirection == Direction::Left)
			mAttackBox = RectMakeCenter(mX - 30, mY, 170, 100);
		else
			mAttackBox = RectMakeCenter(mX + 30, mY, 170, 100);

		//소리
		if(mCurrentAnimation->GetNowFrameX() == 6)
			SOUNDMANAGER->Play(L"FennelAtk", 0.02f);

	}
	if (mCurrentAnimation->GetNowFrameX() == 8)
	{
		mAttackBox = RectMakeCenter(2000, 2000, 1, 1);
	}
	if (mCurrentAnimation->GetNowFrameX() == 15 || mCurrentAnimation->GetNowFrameX() == 16)
	{
		if (mDirection == Direction::Left)
			mAttackBox = RectMakeCenter(mX, mY, 170, 100);
		else
			mAttackBox = RectMakeCenter(mX + 10, mY, 170, 100);

		//소리
		if (mCurrentAnimation->GetNowFrameX() == 15)
			SOUNDMANAGER->Play(L"FennelAtk", 0.02f);
	}
	if (mCurrentAnimation->GetNowFrameX() ==17)
	{
		mAttackBox = RectMakeCenter(2000, 2000, 1, 1);
	}
}
//공격2 칼렉트
void Fennel::Attack2Sword()
{
	if (mCurrentAnimation->GetNowFrameX() >= 1 && mCurrentAnimation->GetNowFrameX() <= 9)
	{
		if (mDirection == Direction::Left)
			mAttackBox = RectMakeCenter(mX + 10, mY, 200, 100);
		else
			mAttackBox = RectMakeCenter(mX + 10, mY, 200, 100);

		//소리
		if (mCurrentAnimation->GetNowFrameX() == 3)
			SOUNDMANAGER->Play(L"FennelAtk2", 0.02f);
	}
	else
	{
		mAttackBox = RectMakeCenter(2000, 2000, 1, 1);
	}
}

//위치조정 및
void Fennel::AttackRect() 
{
	if (mCurrentAnimation->GetNowFrameX() >= 2 && mCurrentAnimation->GetNowFrameX() < 5)
	{
		if (mDirection == Direction::Left)
			mX -= 75 * TIME->DeltaTime();
		else
			mX += 75 * TIME->DeltaTime();
	}
	if (mCurrentAnimation->GetNowFrameX() == 6 || mCurrentAnimation->GetNowFrameX() == 14)
	{
		if (mDirection == Direction::Left)
			mX -= 330 * TIME->DeltaTime();
		else
			mX += 330 * TIME->DeltaTime();
	}
	if (mCurrentAnimation->GetNowFrameX() == 15)
	{
		if (mDirection == Direction::Left)
			mX -= 150 * TIME->DeltaTime();
		else
			mX += 150 * TIME->DeltaTime();
	}
	AttackSword();
	SetAfterImages(5, 10, 14);

}
void Fennel::Attack2Rect() 
{
	float angle;
	//올라가고
	if (mCurrentAnimation->GetNowFrameX() >= 0 && mCurrentAnimation->GetNowFrameX() < 6)
	{
		if (mDirection == Direction::Left)
		{
			angle = PI * 15 / 16;
			mX += cos(angle) * 370 * TIME->DeltaTime();
			mY -= sin(angle) * 370 * TIME->DeltaTime();
		}
		else
		{
			angle = PI / 16;
			mX += cos(angle) * 370 * TIME->DeltaTime();
			mY -= sin(angle) * 370 * TIME->DeltaTime();
		}

	}
	//내려가고
	if (mCurrentAnimation->GetNowFrameX() >= 6)
	{
		if (mDirection == Direction::Left)
		{
			angle = PI * 17 / 16;
			mX += cos(angle) * 370 * TIME->DeltaTime();
			mY -= sin(angle) * 370 * TIME->DeltaTime();
		}
		else
		{
			angle = PI * 31 / 16;
			mX += cos(angle) * 370 * TIME->DeltaTime();
			mY -= sin(angle) * 370 * TIME->DeltaTime();
		}
	}
	Attack2Sword();

	//잔상
	SetAfterImages(0, 3, 8);

}

void Fennel::BackflipRect() 
{
	if (mCurrentAnimation->GetNowFrameX() >= 3 && mCurrentAnimation->GetNowFrameX() < 9)
	{
		if (mDirection == Direction::Left)
			mX += 120 * TIME->DeltaTime();
		else
			mX -= 120 * TIME->DeltaTime();
	}

	//잔상
	SetAfterImages(3, 6, 8);
}

void Fennel::JumpRect() 
{
	float angle;
	if (mCurrentAnimation->GetNowFrameX() >= 0 && mCurrentAnimation->GetNowFrameX() < 4)
	{
		if (mDirection == Direction::Left)
		{
			angle = PI * 5 / 8;
			mX += cos(angle) * 550 * TIME->DeltaTime();
			mY -= sin(angle) * 200 * TIME->DeltaTime();

		}
		else
		{
			angle = PI * 3 / 8;
			mX += cos(angle) * 550 * TIME->DeltaTime();
			mY -= sin(angle) * 200 * TIME->DeltaTime();
		}
	}
	else
	{
		if (mDirection == Direction::Left)
		{
			angle = PI * 5 / 4;
			mX += cos(angle) * 70 * TIME->DeltaTime();
			mY -= sin(angle) * 70 * TIME->DeltaTime();

		}
		else
		{
			angle = PI * 7 / 4;
			mX += cos(angle) * 70 * TIME->DeltaTime();
			mY -= sin(angle) * 70 * TIME->DeltaTime();
		}
	}

	//잔상
	SetAfterImages(1,2,3);
	
}
void Fennel::PlungeRect() 
{
	if (mY < mStart.y)
	{
		mY += 700 * TIME->DeltaTime();
	}
	if (mY > mStart.y)
	{
		mImpact = RectMakeCenter(mX, mY - 200, mImpactImg->GetFrameWidth() * 2, mImpactImg->GetFrameHeight() * 2);
		mCurrentImpact->Play();
		mY = mStart.y;
		//소리
		SOUNDMANAGER->Play(L"FennelAtk3", 0.6f);
	}
	if (mCurrentImpact->GetNowFrameX() == 7)
	{
		mImpact = RectMakeCenter(1000, 1000, 1, 1);
	}
}
void Fennel::ThunderRect() 
{
	//번개떨어질곳 설정
	if (mCurrentAnimation->GetNowFrameX() == 10)
	{
		mTarget.x = mPlayer->GetX();
		mTarget.y = mPlayer->GetY();
	}
	//번개만들기
	if (mCurrentAnimation->GetNowFrameX() == 14)
	{
		mThunder = RectMakeCenter(mTarget.x, 550, mThunderImg->GetFrameWidth() * 2 - 50, 500);
		mCurrentThunder->Play();

		//소리
		SOUNDMANAGER->Play(L"FennelThunder", 0.02f);
	}
	//번개끝
	if (mCurrentAnimation->GetNowFrameX() == 21)
	{
		mThunder = RectMakeCenter(1000, 1000, 1, 1);
		mCurrentThunder->Pause();

	}
}

void Fennel::DashRect()
{
	if ((Math::GetDistance(mPlayer->GetX(), 0, mX, 0) > 100))
	{
		if (mDirection == Direction::Left)
			mX -= 600 * TIME->DeltaTime();
		else
			mX += 600 * TIME->DeltaTime();
		mTimer += TIME->DeltaTime();

	}
	else
	{
		mTimer = 0;
		mFennelState = FennelState::Attack;
		SetImageAnimation();
	}
	if (mTimer == TIME->DeltaTime() && mAfterImages[0].cAlpha == 0.8f)
	{
		mAfterImages[0].cRect = mRect;
		mAfterImages[0].cAnimation = mCurrentAnimation;
		mAfterImages[0].cFrameX = mCurrentAnimation->GetNowFrameX();
		mAfterImages[0].cFrameY = mCurrentAnimation->GetNowFrameY();
		mAfterImages[0].cImage = mImage;
		mAfterImages[0].cAlpha -= TIME->DeltaTime();
	}
	if ((mTimer > 0.5) && mAfterImages[1].cAlpha == 0.8f)
	{
		mAfterImages[1].cRect = mRect;
		mAfterImages[1].cAnimation = mCurrentAnimation;
		mAfterImages[1].cFrameX = mCurrentAnimation->GetNowFrameX();
		mAfterImages[1].cFrameY = mCurrentAnimation->GetNowFrameY();
		mAfterImages[1].cImage = mImage;
		mAfterImages[1].cAlpha -= TIME->DeltaTime();
	}



}

void Fennel::SetAfterImages(int frame1, int frame2, int frame3)
{
	if (mCurrentAnimation->GetNowFrameX() == frame1 && mAfterImages[0].cAlpha == 0.8f)
	{
		mAfterImages[0].cRect = mRect;
		mAfterImages[0].cAnimation = mCurrentAnimation;
		mAfterImages[0].cFrameX = mCurrentAnimation->GetNowFrameX();
		mAfterImages[0].cFrameY = mCurrentAnimation->GetNowFrameY();
		mAfterImages[0].cImage = mImage;
		mAfterImages[0].cAlpha -= TIME->DeltaTime();
	}
	if (mCurrentAnimation->GetNowFrameX() == frame2 && mAfterImages[1].cAlpha == 0.8f)
	{
		mAfterImages[1].cRect = mRect;
		mAfterImages[1].cAnimation = mCurrentAnimation;
		mAfterImages[1].cFrameX = mCurrentAnimation->GetNowFrameX();
		mAfterImages[1].cFrameY = mCurrentAnimation->GetNowFrameY();
		mAfterImages[1].cImage = mImage;
		mAfterImages[1].cAlpha -= TIME->DeltaTime();

	}
	if (mCurrentAnimation->GetNowFrameX() == frame3 && mAfterImages[2].cAlpha == 0.8f)
	{
		mAfterImages[2].cRect = mRect;
		mAfterImages[2].cAnimation = mCurrentAnimation;
		mAfterImages[2].cFrameX = mCurrentAnimation->GetNowFrameX();
		mAfterImages[2].cFrameY = mCurrentAnimation->GetNowFrameY();
		mAfterImages[2].cImage = mImage;
		mAfterImages[2].cAlpha -= TIME->DeltaTime();

	}
}


//공격후 백플립으로
void Fennel::EndAttack()
{
	mFennelState = FennelState::Attack2;
	SetDirection();
	SetImageAnimation();
}

//공격2후 백플립으로
void Fennel::EndAttack2()
{
	mFennelState = FennelState::BackFlip;
	SetDirection();
	mImage = IMAGEMANAGER->FindImage(L"Fennelbackflip");
	SetImageAnimation();
}

//행동후 아이들로
void Fennel::EndMove()
{
	mFennelState = FennelState::Idle;
	mImage = IMAGEMANAGER->FindImage(L"Fennelidle");
	SetDirection();
	SetImageAnimation();

	//바닥효과없애기
	mCurrentFloor->Pause();
	mFloorEffect = { -2000,3000 };
}

//점프준비에서 점프
void Fennel::JumpReadytoJump()
{
	mFennelState = FennelState::Jump;
	mImage = IMAGEMANAGER->FindImage(L"Fenneljump");
	SetImageAnimation();
}
//점프후 플런지
void Fennel::JumptoPlunge()
{
	mFennelState = FennelState::Plunge;
	mImage = IMAGEMANAGER->FindImage(L"Fennelplunge");
	mCurrentImpact->Stop();
	mCurrentImpact = mImpactAni;
	mCurrentImpact->Play();
	SetImageAnimation();
}
//플런지 후 임팩트 없애고 아이들
void Fennel::EndPlunge()
{
	mFennelState = FennelState::Idle;
	mImage = IMAGEMANAGER->FindImage(L"Fennelidle");
	SetImageAnimation();
}
//버프하고 공격1에 패턴추가
void Fennel::EndBuff()
{
	mFennelState = FennelState::Idle;
	SetImageAnimation();
	mRightAtk->SetCallbackFunc(bind(&Fennel::EndAttack, this));
	mLeftAtk->SetCallbackFunc(bind(&Fennel::EndAttack, this));
}
//죽고 알파값 낮추기
void Fennel::EndDeath()
{
	mAlpha -= TIME->DeltaTime();
}


void Fennel::EndIntro1()
{
	mCurrentAnimation->Stop();
	mImage = IMAGEMANAGER->FindImage(L"Fennelintro2");
	mCurrentAnimation = mIntro2;
	mCurrentAnimation->Play();
	/////음악넣기////

}
void Fennel::EndIntro2()
{
	mCurrentAnimation->Stop();
	mImage = IMAGEMANAGER->FindImage(L"Fennelintro3");
	mCurrentAnimation = mIntro3;
	mCurrentAnimation->Play();
}
void Fennel::EndIntro3()
{
	mCurrentAnimation->Stop();
	mFennelState = FennelState::Idle;
	SetImageAnimation();
	mCurrentAnimation = mLeftIdle;
	mCurrentAnimation->Play();
	mIntroEnd = true;
}

void Fennel::SetImageAnimation()
{
	mCurrentAnimation->Stop();

	//왼쪽
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
	//오른쪽
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

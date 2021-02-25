#include "pch.h"
#include "Fennel.h"
#include "Image.h"
#include "Animation.h"
#include "Camera.h"
#include "Player.h"
#include "Staff.h"

void Fennel::Init()
{
	mImage = IMAGEMANAGER->FindImage(L"Fennelidle");
	mImpactImg = IMAGEMANAGER->FindImage(L"Fennelimpact");
	mThunderImg = IMAGEMANAGER->FindImage(L"Thunder");

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

	//���� ////// ���߿� �ٲٱ�////////////
	mHp = 200;
	mAtk = 10;

	///////////////////////////////////

	/////�浹������ ��Ʈ��//////////////////
	mImpact = RectMakeCenter(1000, 1000, 1, 1);
	mThunder = RectMakeCenter(1000, 1000, 1, 1);
	mSword = RectMakeCenter(1000, 1000, 1, 1);
	


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
	mRightDash->SetCallbackFunc(bind(&Fennel::EndMove, this));

	mLeftDash = new Animation();
	mLeftDash->InitFrameByStartEnd(0, 0, 14, 0, false);
	mLeftDash->SetIsLoop(false);
	mLeftDash->SetFrameUpdateTime(0.2f);
	mLeftDash->SetCallbackFunc(bind(&Fennel::EndMove, this));

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

	mEnemyState = EnemyState::Idle;
	mDirection = Direction::Left;
	mCurrentAnimation = mLeftIdle;
	mCurrentAnimation->Play();

	//�ܻ�
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

}

void Fennel::Update()
{
	
	if (mFennelState == FennelState::Idle)
	{
		mAttackSpeed += TIME->DeltaTime();
		if (mAttackSpeed > 1)
		{
			//Ȯ��= RANDOM->RandomInt(3)
			int rand =1;
			if (rand == 0)
			{
				//if (Math::GetDistance(mPlayer->GetX(), 0, mX, 0) > 300)
				//{
				//	Dash();
				//}
				Attack();
			}
			else if(rand == 1)
			{
				Plunge();
			}
			else
			{
				Thunder();
			}

			//�����ֱ�
			//if (mAtk < 20)
			//{
			//	if (mHp < 300)
			//	{
			//		mAtk = 30;
			//		Buff();
			//	}
			//}
			//else
			//{
			//	Attack();
			//}

		}
	}
	
	//���݋� �̵�
	if (mFennelState == FennelState::Attack)
	{
		AttackRect();
	}
	//����2 �̵�
	if (mFennelState == FennelState::Attack2)
	{
		Attack2Rect();
	}
	//�ޱ����� �̵�
	if (mFennelState == FennelState::BackFlip)
	{
		BackflipRect();
	}
	//���� �̵�
	if (mFennelState == FennelState::Jump)
	{
		JumpRect();
	}
	//���
	if (mFennelState == FennelState::Plunge)
	{
		PlungeRect();
	}
	//����
	if (mFennelState == FennelState::Thunder)
	{
		ThunderRect();
	}
	//���
	if (mFennelState == FennelState::Dash)
	{
		DashRect();
	}

	//������
	//if (isHit)
	//{
	//	SetDirection();
	//	//mFennelState == FennelState::Hurt;
	//	SetImageAnimation();
	//	isHit = false;
	//}

	//�׾�
	if (mHp < 0 && mFennelState != FennelState::Death)
	{
		SetDirection();
		mFennelState = FennelState::Death;
		SetImageAnimation();
	}

	if (mAlpha > 0 && mAlpha < 1)
		mAlpha -= TIME->DeltaTime();

	mCurrentImpact->Update();
	mCurrentAnimation->Update();
	mCurrentThunder->Update();
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);

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
	//�ܻ����
	//mTimer += TIME->DeltaTime();
	//if (mTimer > 1 && mTimer <= 2)
	//{
	//	mAfterImages[0].cRect = mRect;
	//	mAfterImages[0].cAnimation = mCurrentAnimation;
	//	mAfterImages[0].cImage = mImage;
	//}
	//else if (mTimer > 2 && mTimer <= 3)
	//{
	//	mAfterImages[1].cRect = mRect;
	//	mAfterImages[1].cAnimation = mCurrentAnimation;
	//	mAfterImages[1].cImage = mImage;
	//}
	//else if (mTimer > 3 && mTimer <= 4)
	//{
	//	mAfterImages[2].cRect = mRect;
	//	mAfterImages[2].cAnimation = mCurrentAnimation;
	//	mAfterImages[2].cImage = mImage;
	//}
	//else if (mTimer > 4) {
	//	mTimer = 0;
	//}
	
	//��Ʈ�ڽ�
	if(mDirection == Direction::Left)
		mHitBox = RectMakeCenter(mX + 10, mY, 50, 100);
	else
		mHitBox = RectMakeCenter(mX - 10, mY, 50, 100);
}

void Fennel::Render(HDC hdc)
{
	//CAMERAMANAGER->GetMainCamera()->RenderRectInCamera(hdc, mHitBox);
	//CAMERAMANAGER->GetMainCamera()->RenderRectInCamera(hdc, mSword);
	CAMERAMANAGER->GetMainCamera()->AlphaScaleFrameRender(hdc, mImage, mRect.left, mRect.top, mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY(), mSizeX, mSizeY,mAlpha);
	CAMERAMANAGER->GetMainCamera()->AlphaScaleFrameRender(hdc, mImpactImg, mImpact.left, mImpact.top, mCurrentImpact->GetNowFrameX(), mCurrentImpact->GetNowFrameY(), mImpactImg->GetFrameWidth() * 2, mImpactImg->GetFrameHeight() * 2, 0.5f);
	CAMERAMANAGER->GetMainCamera()->ScaleFrameRender(hdc, mThunderImg, mThunder.left, mThunder.top, mCurrentThunder->GetNowFrameX(), mCurrentThunder->GetNowFrameY(), mThunderImg->GetFrameWidth() * 2 - 50, 500);
	
	for (int i = 0;i < 3;i++)
	{
		CAMERAMANAGER->GetMainCamera()->AlphaScaleFrameRender(hdc, mAfterImages[i].cImage, mAfterImages[i].cRect.left, mAfterImages[i].cRect.top, mAfterImages[i].cAnimation->GetNowFrameX(), mAfterImages[i].cAnimation->GetNowFrameY(), mSizeX, mSizeY, mAfterImages[i].cAlpha);
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
	//��������� �����ʴ���
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

//����1 Į��Ʈ
void Fennel::AttackSword()
{
	if (mCurrentAnimation->GetNowFrameX() == 6 || mCurrentAnimation->GetNowFrameX() == 7)
	{
		if (mDirection == Direction::Left)
			mSword = RectMakeCenter(mX - 30, mY, 170, 100);
		else
			mSword = RectMakeCenter(mX + 30, mY, 170, 100);
	}
	if (mCurrentAnimation->GetNowFrameX() == 8)
	{
		mSword = RectMakeCenter(2000, 2000, 1, 1);
	}
	if (mCurrentAnimation->GetNowFrameX() == 15 || mCurrentAnimation->GetNowFrameX() == 16)
	{
		if (mDirection == Direction::Left)
			mSword = RectMakeCenter(mX, mY, 170, 100);
		else
			mSword = RectMakeCenter(mX + 10, mY, 170, 100);
	}
}
//����2 Į��Ʈ
void Fennel::Attack2Sword()
{
	if (mCurrentAnimation->GetNowFrameX() >= 1 && mCurrentAnimation->GetNowFrameX() <= 9)
	{
		if (mDirection == Direction::Left)
			mSword = RectMakeCenter(mX + 10, mY, 200, 100);
		else
			mSword = RectMakeCenter(mX + 10, mY, 200, 100);
	}
	else
	{
		mSword = RectMakeCenter(2000, 2000, 1, 1);
	}
}

//��ġ���� ��
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
}
void Fennel::Attack2Rect() 
{
	float angle;
	//�ö󰡰�
	if (mCurrentAnimation->GetNowFrameX() >= 0 && mCurrentAnimation->GetNowFrameX() < 6)
	{
		if (mDirection == Direction::Left)
		{
			angle = PI * 15 / 16;
			mX += cos(angle) * 350 * TIME->DeltaTime();
			mY -= sin(angle) * 350 * TIME->DeltaTime();
		}
		else
		{
			angle = PI / 16;
			mX += cos(angle) * 350 * TIME->DeltaTime();
			mY -= sin(angle) * 350 * TIME->DeltaTime();
		}

	}
	//��������
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

	//�ܻ�
	
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

	//�ܻ�
	SetAfterImages(1,2,5);
	
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
	}
	if (mCurrentImpact->GetNowFrameX() == 7)
	{
		mImpact = RectMakeCenter(1000, 1000, 1, 1);
	}
}
void Fennel::ThunderRect() 
{
	//������������ ����
	if (mCurrentAnimation->GetNowFrameX() == 10)
	{
		mTarget.x = mPlayer->GetX();
		mTarget.y = mPlayer->GetY();
	}
	//���������
	if (mCurrentAnimation->GetNowFrameX() == 14)
	{
		mThunder = RectMakeCenter(mTarget.x, 400, mThunderImg->GetFrameWidth() * 2 - 50, 500);
		mCurrentThunder->Play();
	}
	//������
	if (mCurrentAnimation->GetNowFrameX() == 21)
	{
		mThunder = RectMakeCenter(1000, 1000, 1, 1);
		mCurrentThunder->Pause();

	}
}

void Fennel::DashRect()
{

}

void Fennel::SetAfterImages(int frame1, int frame2, int frame3)
{
	if (mCurrentAnimation->GetNowFrameX() == frame1 && mAfterImages[0].cAlpha == 0.8f)
	{
		mAfterImages[0].cRect = mRect;
		mAfterImages[0].cAnimation = mCurrentAnimation;
		mAfterImages[0].cImage = mImage;
		mAfterImages[0].cAlpha -= TIME->DeltaTime();
	}
	if (mCurrentAnimation->GetNowFrameX() == frame2 && mAfterImages[0].cAlpha == 0.8f)
	{
		mAfterImages[1].cRect = mRect;
		mAfterImages[1].cAnimation = mCurrentAnimation;
		mAfterImages[1].cImage = mImage;
		mAfterImages[1].cAlpha -= TIME->DeltaTime();

	}
	if (mCurrentAnimation->GetNowFrameX() == frame3 && mAfterImages[0].cAlpha == 0.8f)
	{
		mAfterImages[2].cRect = mRect;
		mAfterImages[2].cAnimation = mCurrentAnimation;
		mAfterImages[2].cImage = mImage;
		mAfterImages[2].cAlpha -= TIME->DeltaTime();

	}
}


//������ ���ø�����
void Fennel::EndAttack()
{
	mFennelState = FennelState::Attack2;
	SetDirection();
	SetImageAnimation();
}

//����2�� ���ø�����
void Fennel::EndAttack2()
{
	mFennelState = FennelState::BackFlip;
	SetDirection();
	mImage = IMAGEMANAGER->FindImage(L"Fennelbackflip");
	SetImageAnimation();
}

//�ൿ�� ���̵��
void Fennel::EndMove()
{
	mFennelState = FennelState::Idle;
	mImage = IMAGEMANAGER->FindImage(L"Fennelidle");
	SetDirection();
	SetImageAnimation();
}

//�����غ񿡼� ����
void Fennel::JumpReadytoJump()
{
	mFennelState = FennelState::Jump;
	mImage = IMAGEMANAGER->FindImage(L"Fenneljump");
	SetImageAnimation();
}
//������ �÷���
void Fennel::JumptoPlunge()
{
	mFennelState = FennelState::Plunge;
	mImage = IMAGEMANAGER->FindImage(L"Fennelplunge");
	mCurrentImpact->Stop();
	mCurrentImpact = mImpactAni;
	mCurrentImpact->Play();
	SetImageAnimation();
}
//�÷��� �� ����Ʈ ���ְ� ���̵�
void Fennel::EndPlunge()
{
	mFennelState = FennelState::Idle;
	mImage = IMAGEMANAGER->FindImage(L"Fennelidle");
	SetImageAnimation();
}
//�����ϰ� ����1�� �����߰�
void Fennel::EndBuff()
{
	mFennelState = FennelState::Idle;
	SetImageAnimation();
	mRightAtk->SetCallbackFunc(bind(&Fennel::EndAttack, this));
	mLeftAtk->SetCallbackFunc(bind(&Fennel::EndAttack, this));
}
//�װ� ���İ� ���߱�
void Fennel::EndDeath()
{
	mAlpha -= TIME->DeltaTime();
}

void Fennel::SetImageAnimation()
{
	mCurrentAnimation->Stop();

	//����
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
	//������
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

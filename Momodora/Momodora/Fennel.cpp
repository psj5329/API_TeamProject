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

	mStart.x = WINSIZEX / 2;
	mStart.y = WINSIZEY / 2;
	mX = mStart.x;
	mY = mStart.y;
	mSizeX = mImage->GetFrameWidth() * 2;
	mSizeY = mImage->GetFrameHeight() * 2;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	mHitBox = RectMakeCenter(mX, mY, 50, 50);
	mAttackSpeed = 0;





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
	mRightAtk->SetFrameUpdateTime(0.2f);
	//mRightAtk->SetCallbackFunc(bind(&Witch::EndAttack, this));

	mLeftAtk = new Animation();
	mLeftAtk->InitFrameByStartEnd(0, 0, 22, 0, false);
	mLeftAtk->SetIsLoop(false);
	mLeftAtk->SetFrameUpdateTime(0.2f);
	//mLeftAtk->SetCallbackFunc(bind(&Witch::EndAttack, this));

	mRightAtk2 = new Animation();
	mRightAtk2->InitFrameByStartEnd(0, 1, 11, 1, false);
	mRightAtk2->SetIsLoop(false);
	mRightAtk2->SetFrameUpdateTime(0.2f);
	//mRightAtk->SetCallbackFunc(bind(&Witch::EndAttack, this));

	mLeftAtk2 = new Animation();
	mLeftAtk2->InitFrameByStartEnd(0, 0, 11, 0, false);
	mLeftAtk2->SetIsLoop(false);
	mLeftAtk2->SetFrameUpdateTime(0.2f);
	//mLeftAtk->SetCallbackFunc(bind(&Witch::EndAttack, this));

	mRightBackflip = new Animation();
	mRightBackflip->InitFrameByStartEnd(0, 1, 12, 1, false);
	mRightBackflip->SetIsLoop(false);
	mRightBackflip->SetFrameUpdateTime(0.2f);
	//mRightAtk->SetCallbackFunc(bind(&Witch::EndAttack, this));

	mLeftBackflip = new Animation();
	mLeftBackflip->InitFrameByStartEnd(0, 0, 12, 0, false);
	mLeftBackflip->SetIsLoop(false);
	mLeftBackflip->SetFrameUpdateTime(0.2f);
	//mLeftAtk->SetCallbackFunc(bind(&Witch::EndAttack, this));
	
	mRightBuff = new Animation();
	mRightBuff->InitFrameByStartEnd(0, 1, 14, 1, false);
	mRightBuff->SetIsLoop(false);
	mRightBuff->SetFrameUpdateTime(0.2f);
	//mRightBuff->SetCallbackFunc(bind(&Witch::EndCatch, this));

	mLeftBuff = new Animation();
	mLeftBuff->InitFrameByStartEnd(0, 0, 14, 0, false);
	mLeftBuff->SetIsLoop(false);
	mLeftBuff->SetFrameUpdateTime(0.2f);
	//mLeftBuff->SetCallbackFunc(bind(&Witch::EndCatch, this));

	mRightDash = new Animation();
	mRightDash->InitFrameByStartEnd(0, 1, 14, 1, false);
	mRightDash->SetIsLoop(false);
	mRightDash->SetFrameUpdateTime(0.2f);
	//mRightBuff->SetCallbackFunc(bind(&Witch::EndCatch, this));

	mLeftBuff = new Animation();
	mLeftBuff->InitFrameByStartEnd(0, 0, 14, 0, false);
	mLeftBuff->SetIsLoop(false);
	mLeftBuff->SetFrameUpdateTime(0.2f);
	//mLeftBuff->SetCallbackFunc(bind(&Witch::EndCatch, this));

	mRightDeath = new Animation();
	mRightDeath->InitFrameByStartEnd(0, 0, 6, 0, false);
	mRightDeath->SetIsLoop(false);
	mRightDeath->SetFrameUpdateTime(0.2f);

	mLeftDeath = new Animation();
	mLeftDeath->InitFrameByStartEnd(0, 1, 6, 1, false);
	mLeftDeath->SetIsLoop(false);
	mLeftDeath->SetFrameUpdateTime(0.2f);




	mRightHurt = new Animation();
	mRightHurt->InitFrameByStartEnd(0, 0, 0, 0, false);
	mRightHurt->SetIsLoop(false);
	mRightHurt->SetFrameUpdateTime(0.2f);

	mLeftHurt = new Animation();
	mLeftHurt->InitFrameByStartEnd(0, 1, 0, 1, false);
	mLeftHurt->SetIsLoop(false);
	mLeftHurt->SetFrameUpdateTime(0.2f);


	mEnemyState = EnemyState::Idle;
	mDirection = Direction::Left;
	mCurrentAnimation = mLeftIdle;
	mCurrentAnimation->Play();
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


}

void Fennel::Update()
{

	

	//맞으면



	mCurrentAnimation->Update();
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
}

void Fennel::Render(HDC hdc)
{
	CAMERAMANAGER->GetMainCamera()->ScaleFrameRender(hdc, mImage, mRect.left, mRect.top, mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY(), mSizeX, mSizeY);
}

//공격후 상태바꾸기
void Fennel::EndAttack()
{
	mEnemyState = EnemyState::Idle;
	mImage = IMAGEMANAGER->FindImage(L"Witchidle2");
	SetAnimation();
}


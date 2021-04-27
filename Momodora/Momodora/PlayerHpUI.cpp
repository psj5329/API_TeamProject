#include "pch.h"
#include "PlayerHpUI.h"

#include "Image.h"
#include "Camera.h"
#include "ObjectManager.h"
#include "Player.h"
#include "Enemy.h"

void PlayerHpUI::Init()
{
	mName = "PlayerHpUI";
	mImage = IMAGEMANAGER->FindImage(L"Player_HpBar");
	mBackImage = IMAGEMANAGER->FindImage(L"Player_Hp");
	mLessImage = IMAGEMANAGER->FindImage(L"Player_HpLess");
	mX = 150;
	mY = 35;
	mSizeX = mImage->GetWidth() / 2;
	mSizeY = mImage->GetHeight() / 2;

	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);

	mMaxHp = 0;
	mHp = 0;
	mPreHp = 0;

	mLessHpSizeX = 0.f;
}

void PlayerHpUI::Release()
{
}

void PlayerHpUI::Update()
{
	if(mHp != OBJECTMANAGER->GetPlayer()->GetHp())
	{
		// 체력이 줄었을 경우 mLessHpSizeX 셋팅
		mPreHp = mHp;
		mHp = OBJECTMANAGER->GetPlayer()->GetHp();
		if (mHp <= 0)
			mHp = 0;
		mLessHpSizeX = mPreHp - mHp;
	}

	mSizeX = mImage->GetWidth() / 2 * mHp / mMaxHp;
	mLessHpSizeX -= 0.5f;
}

void PlayerHpUI::Render(HDC hdc)
{
	CAMERAMANAGER->GetMainCamera()->ScaleRender(hdc, mBackImage, mX - mBackImage->GetWidth() / 4, mY - mBackImage->GetHeight() / 4, mBackImage->GetWidth() / 2, mBackImage->GetHeight() / 2, true);
	CAMERAMANAGER->GetMainCamera()->ScaleRender(hdc, mImage, mRect.left, mRect.top, mSizeX, mSizeY, true);
	CAMERAMANAGER->GetMainCamera()->ScaleRender(hdc, mLessImage, mRect.left + mSizeX, mRect.top, mLessHpSizeX, mLessImage->GetHeight() / 2, true);
}
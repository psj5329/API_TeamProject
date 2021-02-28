#include "pch.h"
#include "BossHpUI.h"

#include "Image.h"
#include "Camera.h"
#include "ObjectManager.h"
#include "Enemy.h"

void BossHpUI::Init()
{
	mName = "BossHpUI";
	mImage = IMAGEMANAGER->FindImage(L"Boss_HpBar");
	mBackImage = IMAGEMANAGER->FindImage(L"Boss_Hp");
	mLessImage = IMAGEMANAGER->FindImage(L"Boss_HpLess");
	mX = WINSIZEX / 2;
	mY = WINSIZEY - 50;
	mSizeX = mImage->GetWidth() / 2;
	mSizeY = mImage->GetHeight() / 2;

	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);

	mMaxHp = 0;
	mHp = 0;
	mPreHp = 0;

	mLessHpSizeX = 0.f;
}

void BossHpUI::Release()
{
}

void BossHpUI::Update()
{
	if (mHp != ((Enemy*)OBJECTMANAGER->FindObject(ObjectLayer::Boss, "Boss"))->GetHP())
	{
		// 체력이 줄었을 경우 mLessHpSizeX 셋팅
		mPreHp = mHp;
		mHp = ((Enemy*)OBJECTMANAGER->FindObject(ObjectLayer::Boss, "Boss"))->GetHP();
		if (mHp <= 0)
			mHp = 0;
		mLessHpSizeX = mPreHp - mHp;
	}

	mSizeX = mImage->GetWidth() / 2 * mHp / mMaxHp;
	mLessHpSizeX -= 0.5f;

	//mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
}

void BossHpUI::Render(HDC hdc)
{
	CAMERAMANAGER->GetMainCamera()->ScaleRender(hdc, mBackImage, mX - mBackImage->GetWidth() / 4, mY - mBackImage->GetHeight() / 4, mBackImage->GetWidth() / 2, mBackImage->GetHeight() / 2);
	CAMERAMANAGER->GetMainCamera()->ScaleRender(hdc, mImage, mRect.left, mRect.top, mSizeX, mSizeY);
	CAMERAMANAGER->GetMainCamera()->ScaleRender(hdc, mLessImage, mRect.left + mSizeX, mRect.top, mLessHpSizeX, mLessImage->GetHeight() / 2);
}

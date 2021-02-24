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
}

void PlayerHpUI::Release()
{
}

void PlayerHpUI::Update()
{
	//mHp = OBJECTMANAGER->GetPlayer()->GetHp();
	mHp = ((Enemy*)OBJECTMANAGER->FindObject(ObjectLayer::Boss, "Boss"))->GetHP();	// 플레이어 체력 아직 없움

	mSizeX = mImage->GetWidth() / 2 * mHp / mMaxHp;
}

void PlayerHpUI::Render(HDC hdc)
{
	CAMERAMANAGER->GetMainCamera()->ScaleRender(hdc, mBackImage, mX - mBackImage->GetWidth() / 4, mY - mBackImage->GetHeight() / 4, mBackImage->GetWidth() / 2, mBackImage->GetHeight() / 2);
	CAMERAMANAGER->GetMainCamera()->ScaleRender(hdc, mImage, mRect.left, mRect.top, mSizeX, mSizeY);
}

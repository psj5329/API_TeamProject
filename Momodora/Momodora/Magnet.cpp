#include "pch.h"
#include "Magnet.h"
#include "Image.h"
#include "Player.h"
#include "Camera.h"

Magnet::Magnet()
	:GameObject()
{
}

Magnet::Magnet(float x, float y)
	: GameObject(x, y)
{
}

void Magnet::Init()
{
}

void Magnet::Init(float x, float y)
{
	mImage = IMAGEMANAGER->FindImage(L"Magnet");

	mX = x;
	mY = y;
	mSizeX = mImage->GetFrameWidth() - 70;
	mSizeY = mImage->GetFrameHeight() - 70;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);

	//플레이어 찾아오기
	vector<GameObject*> player = OBJECTMANAGER->GetObjectList(ObjectLayer::Player);
	mPlayer = (Player*)player[0];
}

void Magnet::Release()
{
}

void Magnet::Update()
{
	RECT playerRect = mPlayer->GetRect();
	RECT temp;
	if (IntersectRect(&temp, &playerRect, &mRect))
	{
		mPlayer->SetHaveMagnet(true);

		this->SetIsDestroy(true);
	}
}

void Magnet::Render(HDC hdc)
{
	CAMERAMANAGER->GetMainCamera()->ScaleFrameRender(hdc, mImage, mX, mY, 0, 0, mSizeX, mSizeY);
}
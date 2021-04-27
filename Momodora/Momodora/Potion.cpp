#include "pch.h"
#include "Potion.h"
#include "Image.h"
#include "Player.h"
#include "Camera.h"

Potion::Potion()
	:GameObject()
{
}

Potion::Potion(float x, float y)
	:GameObject(x, y)
{
}

void Potion::Init()
{
}

void Potion::Init(float x, float y, int type)
{
	mImage = IMAGEMANAGER->FindImage(L"Potion");

	mX = x;
	mY = y;
	mSizeX = mImage->GetFrameWidth() * 2;
	mSizeY = mImage->GetFrameHeight() * 2;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	mType = type;

	//플레이어 찾아오기
	vector<GameObject*> player = OBJECTMANAGER->GetObjectList(ObjectLayer::Player);
	mPlayer = (Player*)player[0];

}

void Potion::Release()
{
}

void Potion::Update()
{
	RECT playerRect = mPlayer->GetRect();
	RECT temp;
	if (IntersectRect(&temp, &playerRect, &mRect))
	{
		//플레이어의 물약숫자 늘려주기
		if (mType == 0)
		{
			mPlayer->AddPotion();
		}

		this->SetIsDestroy(true);
	}
}

void Potion::Render(HDC hdc)
{
	CAMERAMANAGER->GetMainCamera()->ScaleFrameRender(hdc, mImage, mX, mY, 0, mType, mSizeX, mSizeY);
}
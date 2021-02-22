#include "pch.h"
#include "BombImp.h"
#include "Image.h"

void BombImp::Init()
{
	IMAGEMANAGER->LoadFromFile(L"Imp", Resources(L"Imp"), 320, 384, 10, 12, true);
	mImage = IMAGEMANAGER->FindImage(L"Imp");

	mStart.x = WINSIZEX / 2;
	mStart.y = WINSIZEY / 2;
	mX = mStart.x;
	mY = mStart.y;
	mSizeX = mImage->GetFrameWidth();
	mSizeY = mImage->GetFrameHeight();
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	mHitBox = RectMakeCenter(mX, mY, 50, 50);
}

void BombImp::Release()
{


}

void BombImp::Update()
{


}

void BombImp::Render(HDC hdc)
{


}
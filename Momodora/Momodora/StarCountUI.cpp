#include "pch.h"
#include "StarCountUI.h"

#include "Image.h"
#include "Camera.h"

void StarCountUI::Init()
{
	mName = "StarCountUI";
	mImage = IMAGEMANAGER->FindImage(L"Star_UI");
	mHundredImage = IMAGEMANAGER->FindImage(L"Number0");
	mTenImage = IMAGEMANAGER->FindImage(L"Number0");
	mOneImage = IMAGEMANAGER->FindImage(L"Number0");
	mX = 90;
	mY = 60;
	mSizeX = mImage->GetWidth() / 2;
	mSizeY = mImage->GetHeight() / 2;

	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);

	mStarCount = 1;

	mHundredSizeX = mHundredImage->GetWidth() / 2;
	mHundredSizeY = mHundredImage->GetHeight() / 2;
	mTenSizeX = mTenImage->GetWidth() / 2;
	mTenSizeY = mTenImage->GetHeight() / 2;
	mOneSizeX = mOneImage->GetWidth() / 2;
	mOneSizeY = mOneImage->GetHeight() / 2;
}

void StarCountUI::Release()
{
}

void StarCountUI::Update()
{
	wstring numH = L"Number" + to_wstring(mStarCount / 100);
	mHundredImage = IMAGEMANAGER->FindImage(numH);
	wstring numT = L"Number" + to_wstring((mStarCount % 100) / 10);
	mTenImage = IMAGEMANAGER->FindImage(numT);
	wstring numO = L"Number" + to_wstring((mStarCount % 100) % 10);
	mOneImage = IMAGEMANAGER->FindImage(numO);
}

void StarCountUI::Render(HDC hdc)
{
	CAMERAMANAGER->GetMainCamera()->ScaleRender(hdc, mImage, mRect.left, mRect.top, mSizeX, mSizeY, true);
	CAMERAMANAGER->GetMainCamera()->ScaleRender(hdc, mHundredImage, mRect.right + mHundredSizeX, mY, mHundredSizeX, mHundredSizeY, true);
	CAMERAMANAGER->GetMainCamera()->ScaleRender(hdc, mTenImage, mRect.right + mHundredSizeX + mTenSizeX , mY, mTenSizeX, mTenSizeY, true);
	CAMERAMANAGER->GetMainCamera()->ScaleRender(hdc, mOneImage, mRect.right + mHundredSizeX + mTenSizeX  + mOneSizeX, mY, mOneSizeX, mOneSizeY, true);
}
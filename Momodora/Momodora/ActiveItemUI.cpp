#include "pch.h"
#include "ActiveItemUI.h"

#include "Image.h"
#include "Camera.h"

void ActiveItemUI::Init()
{
	mName = "ActiveItemUI";
	mImage = IMAGEMANAGER->FindImage(L"Item_UI");
	mItemImage = IMAGEMANAGER->FindImage(L"Flower_UI");
	mItemCountImage = IMAGEMANAGER->FindImage(L"Number0");
	mX = 50;
	mY = 50;
	mSizeX = mImage->GetWidth() / 2;
	mSizeY = mImage->GetHeight() / 2;

	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);

	mItemMaxCount = 9;
	mItemCount = 9;

	mItemSizeX = mItemImage->GetWidth() / 2;
	mItemSizeY = mItemImage->GetHeight() / 2;
	mItemCountSizeX = mItemCountImage->GetWidth() / 2;
	mItemCountSizeY = mItemCountImage->GetHeight() / 2;
}

void ActiveItemUI::Release()
{
}

void ActiveItemUI::Update()
{
	wstring num = L"Number" + to_wstring(mItemCount);
	mItemCountImage = IMAGEMANAGER->FindImage(num);
}

void ActiveItemUI::Render(HDC hdc)
{
	CAMERAMANAGER->GetMainCamera()->ScaleRender(hdc, mImage, mRect.left, mRect.top, mSizeX, mSizeY, true);
	CAMERAMANAGER->GetMainCamera()->ScaleRender(hdc, mItemImage, mX - mItemSizeX / 2, mY - mItemSizeY / 2, mItemSizeX, mItemSizeY, true);
	CAMERAMANAGER->GetMainCamera()->ScaleRender(hdc, mItemCountImage, mX + mItemCountSizeX / 2, mY + mItemCountSizeY / 2, mItemCountSizeX, mItemCountSizeY, true);
}

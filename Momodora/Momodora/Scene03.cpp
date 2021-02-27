#include "pch.h"
#include "Scene03.h"

void Scene03::Init()
{
	mMapImage = IMAGEMANAGER->FindImage(L"MapImage03");
	mSceneSizeX = mMapImage->GetWidth();
	mSceneSizeY = mMapImage->GetHeight();
}

void Scene03::Release()
{
}

void Scene03::Update()
{
}

void Scene03::Render(HDC hdc)
{
}
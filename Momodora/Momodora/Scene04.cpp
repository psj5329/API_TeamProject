#include "pch.h"
#include "Scene04.h"

void Scene04::Init()
{
	mMapImage = IMAGEMANAGER->FindImage(L"MapImage04");
	mSceneSizeX = mMapImage->GetWidth();
	mSceneSizeY = mMapImage->GetHeight();
}

void Scene04::Release()
{
}

void Scene04::Update()
{
}

void Scene04::Render(HDC hdc)
{
}
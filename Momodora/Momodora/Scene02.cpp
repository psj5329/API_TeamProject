#include "pch.h"
#include "Scene02.h"

void Scene02::Init()
{
	mMapImage = IMAGEMANAGER->FindImage(L"MapImage02");
	mSceneSizeX = mMapImage->GetWidth();
	mSceneSizeY = mMapImage->GetHeight();
}

void Scene02::Release()
{
}

void Scene02::Update()
{
}

void Scene02::Render(HDC hdc)
{
}
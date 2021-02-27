#include "pch.h"
#include "Scene01.h"

void Scene01::Init()
{
	mMapImage = IMAGEMANAGER->FindImage(L"MapImage01");
	mSceneSizeX = mMapImage->GetWidth();
	mSceneSizeY = mMapImage->GetHeight();
}

void Scene01::Release()
{
}

void Scene01::Update()
{
}

void Scene01::Render(HDC hdc)
{
}
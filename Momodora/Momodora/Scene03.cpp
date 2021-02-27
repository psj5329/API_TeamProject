#include "pch.h"
#include "Scene03.h"
#include "Camera.h"
#include "Platform.h"

void Scene03::Init()
{
	mMapImage = IMAGEMANAGER->FindImage(L"MapImage03");
	mSceneSizeX = mMapImage->GetWidth();
	mSceneSizeY = mMapImage->GetHeight();

	PlaceRect();

	Camera* main = CAMERAMANAGER->GetMainCamera();
	main->SetMode(Camera::Mode::Follow);
	GameObject* player = (GameObject*)(OBJECTMANAGER->GetPlayer());
	main->SetTarget(player);

	// 플레이어가 서 있는 위치 고려해서 고정 카메라로 했다가 바꿔야 함
	if (mEntrance == 1)
	{
		player->SetX(200);
		player->SetY(400);
	}
	else if (mEntrance == 2)
	{
		player->SetX(2200);
		player->SetY(400);
	}
	
	//적배치
	AddBombImp(800, 600);
	AddShieldImp(900, 600);

	AddWitch(1680,300);
	AddWitch(2073, 230);

	AddDaggerImp(1550, 540);
	AddDaggerImp(1750, 540);
	
}

void Scene03::Release()
{
}

void Scene03::Update()
{
	OBJECTMANAGER->Update();

	GameObject* player = (GameObject*)(OBJECTMANAGER->GetPlayer());
	float x = player->GetX();

	if ((int)x <= 0)
		SCENEMANAGER->LoadScene(L"Scene02", 2);
	if ((int)x >= mSceneSizeX)
		SCENEMANAGER->LoadScene(L"Scene04", 1);



	//충돌확인
	AllCollision();

}

void Scene03::Render(HDC hdc)
{
	CAMERAMANAGER->GetMainCamera()->Render(hdc, mMapImage, 0, 0);

	OBJECTMANAGER->Render(hdc);

	//RECT rect;
	//vector<GameObject*> platformList = OBJECTMANAGER->GetObjectList(ObjectLayer::Platform);
	//vector<GameObject*>::iterator iter = platformList.begin();
	//for (; iter != platformList.end(); ++iter)
	//{
	//	rect = (*iter)->GetRect();
	//	CAMERAMANAGER->GetMainCamera()->RenderRectInCamera(hdc, rect);
	//}
}

void Scene03::PlaceRect()
{
	Platform* platform01 = new Platform();
	platform01->SetPlatform(-120, 600, 360, 900, PlatformType::Normal);
	OBJECTMANAGER->AddObject(ObjectLayer::Platform, (GameObject*)platform01);

	Platform* platform02 = new Platform();
	platform02->SetPlatform(360, 840, 660, 900, PlatformType::Normal);
	OBJECTMANAGER->AddObject(ObjectLayer::Platform, (GameObject*)platform02);

	Platform* platform03 = new Platform();
	platform03->SetPlatform(660, 600, 1080, 900, PlatformType::Normal);
	OBJECTMANAGER->AddObject(ObjectLayer::Platform, (GameObject*)platform03);

	Platform* platform04 = new Platform();
	platform04->SetPlatform(1080, 540, 1980, 900, PlatformType::Normal);
	OBJECTMANAGER->AddObject(ObjectLayer::Platform, (GameObject*)platform04);

	Platform* platform05 = new Platform();
	platform05->SetPlatform(1980, 660, 2520, 900, PlatformType::Normal);
	OBJECTMANAGER->AddObject(ObjectLayer::Platform, (GameObject*)platform05);
}
#include "pch.h"
#include "Scene02.h"
#include "Camera.h"
#include "Platform.h"
#include "Magnet.h"

void Scene02::Init()
{
	mMapImage = IMAGEMANAGER->FindImage(L"MapImage02");
	mSceneSizeX = mMapImage->GetWidth();
	mSceneSizeY = mMapImage->GetHeight();

	PlaceRect();

	Camera* main = CAMERAMANAGER->GetMainCamera();
	main->SetMode(Camera::Mode::Follow);
	GameObject* player = (GameObject*)(OBJECTMANAGER->GetPlayer());
	main->SetTarget(player);

	if (mEntrance == 1)
	{
		player->SetX(50);
		player->SetY(552);
		main->SetX(480);
		main->SetY(540);
	}
	else if (mEntrance == 2)
	{
		player->SetX(2350);
		player->SetY(492);
		main->SetX(1920);
		main->SetY(540);
	}

	AddDaggerImp(750, 420);
	AddDaggerImp(850, 420);
	AddShieldImp(1140, 840);
	AddBombImp(1720, 660);
	AddBombImp(1910, 540);
	AddPotion(2100, 500);

	//자석
	Magnet* Magnet1 = new Magnet();
	Magnet1->Init(950, 740);
	Magnet1->SetObject();
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Item, Magnet1);
}

void Scene02::Release()
{
}

void Scene02::Update()
{
	OBJECTMANAGER->Update();

	GameObject* player = (GameObject*)(OBJECTMANAGER->GetPlayer());
	float x = player->GetX();

	if ((int)x <= 0)
		SCENEMANAGER->LoadScene(L"Scene01", 2);
	if ((int)x >= mSceneSizeX)
		SCENEMANAGER->LoadScene(L"Scene03", 1);

	//충돌확인
	AllCollision();
}

void Scene02::Render(HDC hdc)
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

void Scene02::PlaceRect()
{
	Platform* platform01 = new Platform();
	platform01->SetPlatform(-120, 600, 300, 900, PlatformType::Normal);
	OBJECTMANAGER->AddObject(ObjectLayer::Platform, (GameObject*)platform01);

	Platform* platform02 = new Platform();
	platform02->SetPlatform(300, 420, 840, 900, PlatformType::Normal);
	OBJECTMANAGER->AddObject(ObjectLayer::Platform, (GameObject*)platform02);

	Platform* platform03 = new Platform();
	platform03->SetPlatform(840, 420, 1200, 660, PlatformType::Normal);
	OBJECTMANAGER->AddObject(ObjectLayer::Platform, (GameObject*)platform03);

	Platform* platform04 = new Platform();
	platform04->SetPlatform(840, 840, 1620, 900, PlatformType::Normal);
	OBJECTMANAGER->AddObject(ObjectLayer::Platform, (GameObject*)platform04);

	Platform* platform05 = new Platform();
	platform05->SetPlatform(1620, 660, 1800, 900, PlatformType::Normal);
	OBJECTMANAGER->AddObject(ObjectLayer::Platform, (GameObject*)platform05);

	Platform* platform06 = new Platform();
	platform06->SetPlatform(1800, 540, 2520, 900, PlatformType::Normal);
	OBJECTMANAGER->AddObject(ObjectLayer::Platform, (GameObject*)platform06);
}
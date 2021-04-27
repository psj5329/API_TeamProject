#include "pch.h"
#include "Scene01.h"
#include "Camera.h"
#include "Platform.h"
#include "Fennel.h"
#include "PlayerHpUI.h"
#include "StarCountUI.h"
#include "ActiveItemUI.h"
#include "Player.h"

#include "PlayerHpUI.h"
#include "StarCountUI.h"
#include "ActiveItemUI.h"
#include "Player.h"

void Scene01::Init()
{
	mMapImage = IMAGEMANAGER->FindImage(L"MapImage01");
	mSceneSizeX = mMapImage->GetWidth();
	mSceneSizeY = mMapImage->GetHeight();

	PlaceRect();

	Camera* main = CAMERAMANAGER->GetMainCamera();
	main->SetMode(Camera::Mode::Follow);
	GameObject* player = (GameObject*)(OBJECTMANAGER->GetPlayer());
	main->SetTarget(player);

	if (mEntrance == 0)
	{
		player->SetX(100);
		player->SetY(552);
		main->SetX(480);
		main->SetY(540);
	}
	else if (mEntrance == 2)
	{
		player->SetX(1150);
		player->SetY(552);
		main->SetX(720);
		main->SetY(540);
	}

	//몬스터 배치
	AddMonkey(900, 600);

	PlayerHpUI* playerui = new PlayerHpUI;
	playerui->Init();
	playerui->SetHp(OBJECTMANAGER->GetPlayer()->GetHp());
	OBJECTMANAGER->AddObject(ObjectLayer::UI, playerui);

	ActiveItemUI* activeItemui = new ActiveItemUI;
	activeItemui->Init();
	OBJECTMANAGER->AddObject(ObjectLayer::UI, activeItemui);

	StarCountUI* starCountui = new StarCountUI;
	starCountui->Init();
	OBJECTMANAGER->AddObject(ObjectLayer::UI, starCountui);
}

void Scene01::Release()
{
}

void Scene01::Update()
{
	OBJECTMANAGER->Update();

	GameObject* player = (GameObject*)(OBJECTMANAGER->GetPlayer());
	float x = player->GetX();

	if ((int)x >= mSceneSizeX)
		SCENEMANAGER->LoadScene(L"Scene02", 1);

	//충돌확인
	AllCollision();
}

void Scene01::Render(HDC hdc)
{
	CAMERAMANAGER->GetMainCamera()->Render(hdc, mMapImage, 0, 0);

	OBJECTMANAGER->Render(hdc);

	OBJECTMANAGER->RenderUI(hdc);
}

void Scene01::PlaceRect()
{
	Platform* platform01 = new Platform();
	platform01->SetPlatform(-120, 600, 1320, 900, PlatformType::Normal);
	OBJECTMANAGER->AddObject(ObjectLayer::Platform, (GameObject*)platform01);

	Platform* platform02 = new Platform();
	platform02->SetPlatform(-120, 0, 900, 120, PlatformType::Normal);
	OBJECTMANAGER->AddObject(ObjectLayer::Platform, (GameObject*)platform02);

	Platform* platform03 = new Platform();
	platform03->SetPlatform(900, 0, 1320, 240, PlatformType::Normal);
	OBJECTMANAGER->AddObject(ObjectLayer::Platform, (GameObject*)platform03);
}
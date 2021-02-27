#include "pch.h"
#include "Scene01.h"
#include "Camera.h"
#include "Platform.h"
#include "Ladder.h"
#include "Potion.h"
#include "Player.h"
#include "Image.h"

void Scene01::Init()
{
	// {{ 충돌 체크용 맵
	mMapImage = IMAGEMANAGER->FindImage(L"map0001");

	mSceneSizeX = mMapImage->GetWidth();
	mSceneSizeY = mMapImage->GetHeight();

	Platform* platform01 = new Platform();
	platform01->SetPlatform(0, 600, 4000, 650, PlatformType::Normal);
	OBJECTMANAGER->AddObject(ObjectLayer::Platform, (GameObject*)platform01);

	Platform* platform02 = new Platform();
	platform02->SetPlatform(600, 400, 800, 450, PlatformType::DownJump);
	OBJECTMANAGER->AddObject(ObjectLayer::Platform, (GameObject*)platform02);

	Ladder* ladder01 = new Ladder();
	ladder01->SetLadder(675, 450, 725, 600);
	OBJECTMANAGER->AddObject(ObjectLayer::Ladder, (GameObject*)ladder01);
	// 충돌 체크용 맵 }}

	//템
	Potion* potion1 = new Potion();
	potion1->Init(WINSIZEX / 2 + 350, 550,0);
	potion1->SetObject();
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Item, potion1);


	Camera* main = CAMERAMANAGER->GetMainCamera();
	main->SetMode(Camera::Mode::Follow);
	GameObject* player = (GameObject*)(OBJECTMANAGER->GetPlayer());
	main->SetTarget(player);
}

void Scene01::Release()
{
	//ObjectManager::GetInstance()->Release();
}

void Scene01::Update()
{
	OBJECTMANAGER->Update();

	//Player* player = (Player*)(OBJECTMANAGER->FindObject("PLAYER"));
	//player->Update();
}

void Scene01::Render(HDC hdc)
{
	// {{ 충돌 체크용 맵
	CAMERAMANAGER->GetMainCamera()->Render(hdc, mMapImage, 0, 0);

	vector<GameObject*> platformList = OBJECTMANAGER->GetObjectList(ObjectLayer::Platform);
	vector<GameObject*>::iterator iter1 = platformList.begin();
	for (; iter1 != platformList.end(); ++iter1)
		CAMERAMANAGER->GetMainCamera()->RenderRectInCamera(hdc, (*iter1)->GetRect());

	vector<GameObject*> ladderList = OBJECTMANAGER->GetObjectList(ObjectLayer::Ladder);
	vector<GameObject*>::iterator iter2 = ladderList.begin();
	for (; iter2 != ladderList.end(); ++iter2)
		CAMERAMANAGER->GetMainCamera()->RenderRectInCamera(hdc, (*iter2)->GetRect());
	// 충돌 체크용 맵 }}

	wstring str = L"씬1 페이지";
	TextOut(hdc, WINSIZEX / 2, WINSIZEY / 2, str.c_str(), (int)str.length());

	OBJECTMANAGER->Render(hdc);

	//Player* player = (Player*)(OBJECTMANAGER->FindObject("PLAYER"));
	//player->Render(hdc);
}
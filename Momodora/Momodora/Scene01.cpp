#include "pch.h"
#include "Scene01.h"
#include "Camera.h"
#include "Platform.h"
#include "Ladder.h"

#include "Player.h"
#include "Image.h"

void Scene01::Init()
{
	// {{ �浹 üũ�� ��
	Platform* platform01 = new Platform();
	platform01->SetPlatform(0, 600, 800, 650, PlatformType::Normal);
	OBJECTMANAGER->AddObject(ObjectLayer::Platform, (GameObject*)platform01);

	Platform* platform02 = new Platform();
	platform02->SetPlatform(600, 400, 800, 450, PlatformType::DownJump);
	OBJECTMANAGER->AddObject(ObjectLayer::Platform, (GameObject*)platform02);

	Ladder* ladder01 = new Ladder();
	ladder01->SetLadder(675, 450, 725, 600);
	OBJECTMANAGER->AddObject(ObjectLayer::Ladder, (GameObject*)ladder01);
	// �浹 üũ�� �� }}
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
	// {{ �浹 üũ�� ��
	vector<GameObject*> platformList = OBJECTMANAGER->GetObjectList(ObjectLayer::Platform);
	vector<GameObject*>::iterator iter1 = platformList.begin();
	for (; iter1 != platformList.end(); ++iter1)
		CAMERAMANAGER->GetMainCamera()->RenderRectInCamera(hdc, (*iter1)->GetRect());

	vector<GameObject*> ladderList = OBJECTMANAGER->GetObjectList(ObjectLayer::Ladder);
	vector<GameObject*>::iterator iter2 = ladderList.begin();
	for (; iter2 != ladderList.end(); ++iter2)
		CAMERAMANAGER->GetMainCamera()->RenderRectInCamera(hdc, (*iter2)->GetRect());
	// �浹 üũ�� �� }}

	wstring str = L"��1 ������";
	TextOut(hdc, WINSIZEX / 2, WINSIZEY / 2, str.c_str(), (int)str.length());

	OBJECTMANAGER->Render(hdc);

	//Player* player = (Player*)(OBJECTMANAGER->FindObject("PLAYER"));
	//player->Render(hdc);
}
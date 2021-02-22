#include "pch.h"
#include "Scene01.h"
#include "Camera.h"

#include "Player.h"
#include "Image.h"

void Scene01::Init()
{
	Player* player = new Player;
	player->Init();
	player->SetName("PLAYER");

	ObjectManager::GetInstance()->AddObject(ObjectLayer::Player, player);
	
}

void Scene01::Release()
{
	ObjectManager::GetInstance()->Release();
}

void Scene01::Update()
{
	Player* player = (Player*)(OBJECTMANAGER->FindObject("PLAYER"));
	player->Update();
}

void Scene01::Render(HDC hdc)
{
	wstring str = L"¾À1 ÆäÀÌÁö";
	TextOut(hdc, WINSIZEX / 2, WINSIZEY / 2, str.c_str(), (int)str.length());


	Player* player = (Player*)(OBJECTMANAGER->FindObject("PLAYER"));
	player->Render(hdc);
}
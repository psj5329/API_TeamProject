#include "pch.h"
#include "Scene08.h"
#include "Camera.h"
#include "Enemy.h"
#include "Platform.h"
#include "Fennel.h"
#include "Player.h"
#include "Magnet.h"
#include "CollisionManager.h"


void Scene08::Init()
{
	// 맵 배경으로 깔고 그 사이즈 받아서 맵 사이즈 초기화 해야 함
	mSceneSizeX = 3000;
	mSceneSizeY = 3000;
	// 여기까지는 임시 데이터

	vector<GameObject*> player = OBJECTMANAGER->GetObjectList(ObjectLayer::Player);
	mPlayer = (Player*)player[0];
	
	//플랫폼만들기
	mPlatform01 = new Platform();
	mPlatform01->SetPlatform(0, 600, 800, 650, PlatformType::Normal);
	OBJECTMANAGER->AddObject(ObjectLayer::Platform, (GameObject*)mPlatform01);
	mGround = { 0,600,800,650 };


	//적만들기
	//AddMonkey(WINSIZEX / 2 - 100, mPlatform01->GetRect().top);
	AddBombImp(WINSIZEX / 2, mPlatform01->GetRect().top);
	//AddDaggerImp(WINSIZEX / 2 - 300, mPlatform01->GetRect().top);
	AddWitch(WINSIZEX / 2 + 100,mPlatform01->GetRect().top);
	//AddPotion(WINSIZEX / 2 + 350, 550);



	mMap = IMAGEMANAGER->FindImage(L"MapTest");



	Camera* main = CAMERAMANAGER->GetMainCamera();
	main->SetMode(Camera::Mode::Follow);
	GameObject* player99 = (GameObject*)(OBJECTMANAGER->GetPlayer());
	main->SetTarget(player99);
}
void Scene08::Release()
{
	//적 세이프딜리트

}

void Scene08::Update()
{
	OBJECTMANAGER->Update();

	//RECT temp;
	//Player* player = OBJECTMANAGER->GetPlayer();
	//RECT playerRect = player->GetRect();
	//GameObject* fennel1 = OBJECTMANAGER->FindObject(ObjectLayer::Enemy, "Fennel");
	//RECT fennel = ((Enemy*)fennel1)->GetHitBox();
	//if (IntersectRect(&temp, &playerRect, &fennel))
	//{
	//	((Enemy*)fennel1)->SetIsHit(true);
	//}

	
}

void Scene08::Render(HDC hdc)
{
	wstring str = L"씬2 페이지";
	TextOut(hdc, 100, 200, str.c_str(), (int)str.length());
	

	CAMERAMANAGER->GetMainCamera()->Render(hdc, mMap, 0, 0);
	OBJECTMANAGER->Render(hdc);

	CAMERAMANAGER->GetMainCamera()->RenderRectInCamera(hdc,mGround);

	wstring str3 = L"MouseX:" + to_wstring(_mousePosition.x);
	TextOut(hdc, _mousePosition.x+10, _mousePosition.y + 10, str3.c_str(), str3.length());
	wstring str4 = L"MouseY:" + to_wstring(_mousePosition.y);
	TextOut(hdc, _mousePosition.x+10, _mousePosition.y + 30, str4.c_str(), str4.length());
}

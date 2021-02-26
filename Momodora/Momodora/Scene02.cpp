#include "pch.h"
#include "Scene02.h"
#include "Camera.h"
#include "Enemy.h"
#include "Monkey.h"
#include "DaggerImp.h"
#include "Platform.h"
#include "BombImp.h"
#include "ShieldImp.h"
#include "Witch.h"
#include "Fennel.h"
#include "Player.h"
#include "Potion.h"
#include "Magnet.h"
#include "CollisionManager.h"

void Scene02::Init()
{
	Platform* platform01 = new Platform();
	platform01->SetPlatform(0, 600, 800, 650, PlatformType::Normal);
	OBJECTMANAGER->AddObject(ObjectLayer::Platform, (GameObject*)platform01);
	mGround = { 0,600,800,650 };

	vector<GameObject*> player = OBJECTMANAGER->GetObjectList(ObjectLayer::Player);


	//몽키생성
	//Monkey* monkey1 = new Monkey();
	//monkey1->Init();
	//monkey1->SetObject();
	//monkey1->SetPosition(WINSIZEX / 2, platform01->GetRect().top);
	//monkey1->SetPlayerPtr((Player*)player[0]);
	//ObjectManager::GetInstance()->AddObject(ObjectLayer::Enemy, monkey1);

	//칼든애
	//DaggerImp* DaggerImp1 = new DaggerImp();
	//DaggerImp1->Init();
	//DaggerImp1->SetObject();
	//DaggerImp1->SetPosition(WINSIZEX / 2 - 300, platform01->GetRect().top);
	//DaggerImp1->SetPlayerPtr((Player*)player[0]);
	//ObjectManager::GetInstance()->AddObject(ObjectLayer::Enemy, DaggerImp1);
	
	//폭탄
	//BombImp * BombImp1 = new BombImp();
	//BombImp1->Init();
	//BombImp1->SetObject();
	//BombImp1->SetPosition(WINSIZEX / 2 , platform01->GetRect().top);
	//BombImp1->SetPlayerPtr((Player*)player[0]);
	//ObjectManager::GetInstance()->AddObject(ObjectLayer::Enemy, BombImp1);

	//방패
	//ShieldImp* ShieldImp1 = new ShieldImp();
	//ShieldImp1->Init();
	//ShieldImp1->SetObject();
	//ShieldImp1->SetPosition(WINSIZEX / 2 - 300, platform01->GetRect().top);
	//ShieldImp1->SetPlayerPtr((Player*)player[0]);
	//ObjectManager::GetInstance()->AddObject(ObjectLayer::Enemy, ShieldImp1);

	//마녀
	Witch* Witch1 = new Witch();
	Witch1->Init();
	Witch1->SetObject();
	Witch1->SetPosition(WINSIZEX / 2 + 100, platform01->GetRect().top);
	Witch1->SetPlayerPtr((Player*)player[0]);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Enemy, Witch1);

	////페넬
	//Fennel* Fennel1 = new Fennel();
	//Fennel1->Init();
	//Fennel1->SetObject();
	//Fennel1->SetPosition(WINSIZEX / 2 + 300, platform01->GetRect().top);
	//Fennel1->SetPlayerPtr((Player*)player[0]);
	//ObjectManager::GetInstance()->AddObject(ObjectLayer::Enemy, Fennel1);

	//템
	//Potion* potion1 = new Potion();
	//potion1->Init(WINSIZEX / 2 + 350, 550,0);
	//potion1->SetObject();
	//ObjectManager::GetInstance()->AddObject(ObjectLayer::Item, potion1);
	
	Magnet* Magnet1 = new Magnet();
	Magnet1->Init(WINSIZEX / 2 + 350, 550);
	Magnet1->SetObject();
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Item, Magnet1);

	mMap = IMAGEMANAGER->FindImage(L"MapTest");



	Camera* main = CAMERAMANAGER->GetMainCamera();
	main->SetMode(Camera::Mode::Follow);
	GameObject* player99 = (GameObject*)(OBJECTMANAGER->GetPlayer());
	main->SetTarget(player99);
}
void Scene02::Release()
{
	//적 세이프딜리트

}

void Scene02::Update()
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


	
	vector<GameObject*> enemyList = OBJECTMANAGER->GetObjectList(ObjectLayer::Enemy);
	vector<GameObject*> arrowList = OBJECTMANAGER->GetObjectList(ObjectLayer::PlayerProjectile);

	//적히트박스, 플레이어 화살 충돌
	//for (int i = 0;i < enemyList.size();i++)
	//{
	//	for (int j = 0;j < arrowList.size(); j++)
	//	{
	//		RECT temp;
	//		RECT hitBox = enemyList[i]->GetHitBox();
	//		RECT arrow = arrowList[j]->GetRect();
	//		if (IntersectRect(&temp, &hitBox, &arrow))
	//		{
	//			//화살 없애고
	//			arrowList[i]->SetIsDestroy(true);
	//			//에너미 체력조정
	//			enemyList[i].
	//		}
	//	}
	//	//RECT hitBox = enemyList[i]->GetHitBox();
	//	//COLLISIONMANAGER->IsCollision(hitB)
	//
	//}







}

void Scene02::Render(HDC hdc)
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
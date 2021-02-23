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
void Scene02::Init()
{
	//根虐积己
	//Monkey* monkey1 = new Monkey();
	//monkey1->Init();
	//monkey1->SetObject();
	//monkey1->SetPosition(WINSIZEX / 2, 500);
	//vector<GameObject*> player = OBJECTMANAGER->GetObjectList(ObjectLayer::Player);
	//monkey1->SetPlayerPtr((Player*)player[0]);
	//ObjectManager::GetInstance()->AddObject(ObjectLayer::Enemy, monkey1);

	//漠电局
	//DaggerImp* DaggerImp1 = new DaggerImp();
	//DaggerImp1->Init();
	//DaggerImp1->SetObject();
	//DaggerImp1->SetPosition(WINSIZEX / 2 - 300, 550);
	//vector<GameObject*> player = OBJECTMANAGER->GetObjectList(ObjectLayer::Player);
	//DaggerImp1->SetPlayerPtr((Player*)player[0]);
	//ObjectManager::GetInstance()->AddObject(ObjectLayer::Enemy, DaggerImp1);
	
	//气藕
	//BombImp * BombImp1 = new BombImp();
	//BombImp1->Init();
	//BombImp1->SetObject();
	//BombImp1->SetPosition(WINSIZEX / 2 , 550);
	//vector<GameObject*> player = OBJECTMANAGER->GetObjectList(ObjectLayer::Player);
	//BombImp1->SetPlayerPtr((Player*)player[0]);
	//ObjectManager::GetInstance()->AddObject(ObjectLayer::Enemy, BombImp1);

	//规菩
	//ShieldImp* ShieldImp1 = new ShieldImp();
	//ShieldImp1->Init();
	//ShieldImp1->SetObject();
	//ShieldImp1->SetPosition(WINSIZEX / 2 - 300, 550);
	//vector<GameObject*> player = OBJECTMANAGER->GetObjectList(ObjectLayer::Player);
	//ShieldImp1->SetPlayerPtr((Player*)player[0]);
	//ObjectManager::GetInstance()->AddObject(ObjectLayer::Enemy, ShieldImp1);

	//付赤
	Witch* Witch1 = new Witch();
	Witch1->Init();
	Witch1->SetObject();
	Witch1->SetPosition(WINSIZEX / 2 + 100, 550);
	vector<GameObject*> player = OBJECTMANAGER->GetObjectList(ObjectLayer::Player);
	Witch1->SetPlayerPtr((Player*)player[0]);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Enemy, Witch1);

	IMAGEMANAGER->LoadFromFile(L"MapTest", Resources(L"Map/map2"), 1200, 900, false);
	mMap = IMAGEMANAGER->FindImage(L"MapTest");

	mPlatform01 = new Platform();
	RECT rect01 = { 0, 602, 600, 650 };
	mPlatform01->SetRect(rect01);
	OBJECTMANAGER->AddObject(ObjectLayer::Platform, (GameObject*)mPlatform01);
}
void Scene02::Release()
{
	//利 技捞橇掉府飘

}

void Scene02::Update()
{
	OBJECTMANAGER->Update();
}

void Scene02::Render(HDC hdc)
{
	wstring str = L"纠2 其捞瘤";
	TextOut(hdc, 100, 200, str.c_str(), (int)str.length());
	
	CAMERAMANAGER->GetMainCamera()->RenderRectInCamera(hdc, mPlatform01->GetRect());

	CAMERAMANAGER->GetMainCamera()->Render(hdc, mMap, 0, 0);
	OBJECTMANAGER->Render(hdc);


	wstring str3 = L"MouseX:" + to_wstring(_mousePosition.x);
	TextOut(hdc, _mousePosition.x+10, _mousePosition.y + 10, str3.c_str(), str3.length());
	wstring str4 = L"MouseY:" + to_wstring(_mousePosition.y);
	TextOut(hdc, _mousePosition.x+10, _mousePosition.y + 30, str4.c_str(), str4.length());

}
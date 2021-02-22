#include "pch.h"
#include "Scene02.h"
#include "Camera.h"
#include "Enemy.h"
#include "Monkey.h"
//<<<<<<< PNH1.0
#include "DaggerImp.h"
#include "Platform.h"
#include "BombImp.h"
#include "ShieldImp.h"
void Scene02::Init()
{
	//¸ùÅ°»ý¼º
	//Monkey* monkey1 = new Monkey();
	//monkey1->Init();
	//monkey1->SetObject();
	//monkey1->SetPosition(WINSIZEX / 2, 500);
	//ObjectManager::GetInstance()->AddObject(ObjectLayer::Enemy, monkey1);


	//DaggerImp* DaggerImp1 = new DaggerImp();
	//DaggerImp1->Init();
	//DaggerImp1->SetObject();
	//DaggerImp1->SetPosition(WINSIZEX / 2 - 300, 550);
	//ObjectManager::GetInstance()->AddObject(ObjectLayer::Enemy, DaggerImp1);
	
	//BombImp * BombImp1 = new BombImp();
	//BombImp1->Init();
	//BombImp1->SetObject();
	//BombImp1->SetPosition(WINSIZEX / 2 - 300, 550);
	//ObjectManager::GetInstance()->AddObject(ObjectLayer::Enemy, BombImp1);

	ShieldImp* ShieldImp1 = new ShieldImp();
	ShieldImp1->Init();
	ShieldImp1->SetObject();
	ShieldImp1->SetPosition(WINSIZEX / 2 - 300, 550);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Enemy, ShieldImp1);
//=======
//
//void Scene02::Init()
//{
//	Monkey* monkey1 = new Monkey();
//	monkey1->Init();
//	monkey1->SetObject();
//	monkey1->SetPosition(WINSIZEX / 2, 500);
//	ObjectManager::GetInstance()->AddObject(ObjectLayer::Enemy, monkey1);
//>>>>>>> master

	IMAGEMANAGER->LoadFromFile(L"MapTest", Resources(L"Map/map2"), 1200, 900, false);
	mMap = IMAGEMANAGER->FindImage(L"MapTest");
}
void Scene02::Release()
{
	//Àû ¼¼ÀÌÇÁµô¸®Æ®

}

void Scene02::Update()
{
	OBJECTMANAGER->Update();
}

void Scene02::Render(HDC hdc)
{
	wstring str = L"¾À2 ÆäÀÌÁö";
	TextOut(hdc, 100, 200, str.c_str(), (int)str.length());
	

	CAMERAMANAGER->GetMainCamera()->Render(hdc, mMap, 0, 0);
	OBJECTMANAGER->Render(hdc);

	wstring str3 = L"MouseX:" + to_wstring(_mousePosition.x);
	TextOut(hdc, _mousePosition.x+10, _mousePosition.y + 10, str3.c_str(), str3.length());
	wstring str4 = L"MouseY:" + to_wstring(_mousePosition.y);
	TextOut(hdc, _mousePosition.x+10, _mousePosition.y + 30, str4.c_str(), str4.length());

}
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
#include "Bomb.h"

void Scene02::Init()
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

	////페넬
	//Fennel* Fennel1 = new Fennel();
	//Fennel1->Init();
	//Fennel1->SetObject();
	//Fennel1->SetPosition(WINSIZEX / 2 + 300, mPlatform01->GetRect().top);
	//Fennel1->SetPlayerPtr((Player*)player[0]);
	//ObjectManager::GetInstance()->AddObject(ObjectLayer::Enemy, Fennel1);
	
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
	vector<GameObject*> arrowList = OBJECTMANAGER->GetObjectList(ObjectLayer::PlayerArrow);
	vector<GameObject*> daggerList = OBJECTMANAGER->GetObjectList(ObjectLayer::EnemyDagger);
	vector<GameObject*> bombList = OBJECTMANAGER->GetObjectList(ObjectLayer::EnemyBomb);
	vector<GameObject*> staffList = OBJECTMANAGER->GetObjectList(ObjectLayer::EnemyStaff);
	vector<GameObject*> leaf = OBJECTMANAGER->GetObjectList(ObjectLayer::PlayerLeaf);
	RECT playertHitBox = mPlayer->GetHitBox();
	RECT playerAtkBox = leaf[0]->GetAttackBox();

	//적히트박스, 플레이어 화살 충돌
	for (int i = 0;i < enemyList.size();i++)
	{
		for (int j = 0;j < arrowList.size(); j++)
		{
			RECT temp;
			RECT hitBox = enemyList[i]->GetHitBox();
			RECT arrow = arrowList[j]->GetRect();
			if (IntersectRect(&temp, &hitBox, &arrow))
			{
				//화살 없애고
				//arrowList[j]->Release();
				//arrowList[j]->SetIsActive(false);
				arrowList[j]->SetIsDestroy(true);
				//에너미 체력조정
				((Enemy*)(enemyList[i]))->TakeHp(20);
			}
		}
	}
	//적히트박스, 플레이어의 리프 충돌
	for (int i = 0;i < enemyList.size();i++)
	{
		//적이 이미맞은상태니?
		if (!((Enemy*)(enemyList[i]))->GetIsHit())
		{
			RECT hitBox = enemyList[i]->GetHitBox();
			RECT temp;
			if (IntersectRect(&temp, &hitBox, &playerAtkBox))
			{
				//플레이어 불값바꾸기
				mPlayer->SetEndCombo(false);
				//적체력깎기
				int atk = mPlayer->GetAttackDamage();
				((Enemy*)(enemyList[i]))->TakeHp(30);
				//에너미 맞은상태 true
				((Enemy*)(enemyList[i]))->SetIsHit(true);
			}
		}
		//플레이어의 공격애니메이션하나가 끝나면
		if (mPlayer->GetEndCombo())
		{
			((Enemy*)(enemyList[i]))->SetIsHit(false);
		}

	}

	//단도, 플레이어 히트박스 충돌
	for (int i = 0;i < daggerList.size();i++)
	{
		RECT temp;
		RECT dagger = daggerList[i]->GetHitBox();
		if (IntersectRect(&temp, &playertHitBox, &dagger))
		{
			//단도없애고
			//daggerList[i]->Release();
			daggerList[i]->SetIsDestroy(true);

			//플레이어 체력 깎기
			//방향알려줘야해
			Direction direction = COLLISIONMANAGER->CheckSide(&playertHitBox, &dagger);
			//플레이어 상태전환하고 무적시키는 함수
			mPlayer->PlayerHurt();
		}
	}
	//폭탄, 플레이어 히트박스 충돌
	for (int i = 0;i < bombList.size();i++)
	{
		RECT temp;
		RECT bomb = bombList[i]->GetHitBox();
		if (IntersectRect(&temp, &playertHitBox, &bomb))
		{
			//폭탄 터트리고
			((Bomb*)bombList[i])->Explode();

			//플레이어 체력 깎기
			//방향알려줘야해
			Direction direction = COLLISIONMANAGER->CheckSide(&playertHitBox, &bomb);
			//플레이어 상태전환하고 무적시키는 함수
			mPlayer->PlayerHurt();
		}
	}
	//지팡이, 플레이어 히트박스 충돌
	for (int i = 0;i < staffList.size();i++)
	{
		RECT temp;
		RECT staff = staffList[i]->GetRect();
		if (IntersectRect(&temp, &playertHitBox, &staff))
		{

			//플레이어 체력 깎기
			//방향알려줘야해
			Direction direction = COLLISIONMANAGER->CheckSide(&playertHitBox, &staff);
			//플레이어 상태전환하고 무적시키는 함수
			mPlayer->PlayerHurt();
		}
	}
	//적의 근접공격, 플레이어 히트박스 충돌
	for (int i = 0;i < enemyList.size();i++)
	{
		RECT temp;
		RECT atkBox = enemyList[i]->GetAttackBox();

		if (IntersectRect(&temp, &playertHitBox, &atkBox))
		{

			//플레이어 체력 깎기
			//플레이어 상태전환하고 무적시키는 함수
			Direction direction = COLLISIONMANAGER->CheckSide(&playertHitBox, &atkBox);
			//방향알려줘야해
			mPlayer->PlayerHurt();
		}
	}




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

//적생성
void Scene02::AddMonkey(float x, float y)
{
	vector<GameObject*> player = OBJECTMANAGER->GetObjectList(ObjectLayer::Player);
	//몽키생성

	Monkey* monkey1 = new Monkey();
	monkey1->Init();
	monkey1->SetObject();
	monkey1->SetPosition(x, y);
	monkey1->SetPlayerPtr((Player*)player[0]);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Enemy, monkey1);
}

void Scene02::AddWitch(float x, float y)
{
	vector<GameObject*> player = OBJECTMANAGER->GetObjectList(ObjectLayer::Player);

	//마녀
	Witch* Witch1 = new Witch();
	Witch1->Init();
	Witch1->SetObject();
	Witch1->SetPosition(x, y);
	Witch1->SetPlayerPtr((Player*)player[0]);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Enemy, Witch1);


}
void Scene02::AddBombImp(float x, float y)
{
	vector<GameObject*> player = OBJECTMANAGER->GetObjectList(ObjectLayer::Player);

	//폭탄
	BombImp * BombImp1 = new BombImp();
	BombImp1->Init();
	BombImp1->SetObject();
	BombImp1->SetPosition(x, y);
	BombImp1->SetPlayerPtr((Player*)player[0]);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Enemy, BombImp1);
}
void Scene02::AddShieldImp(float x, float y)
{
	vector<GameObject*> player = OBJECTMANAGER->GetObjectList(ObjectLayer::Player);

	//방패
	ShieldImp* ShieldImp1 = new ShieldImp();
	ShieldImp1->Init();
	ShieldImp1->SetObject();
	ShieldImp1->SetPosition(x, y);
	ShieldImp1->SetPlayerPtr((Player*)player[0]);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Enemy, ShieldImp1);

}
void Scene02::AddDaggerImp(float x, float y)
{
	vector<GameObject*> player = OBJECTMANAGER->GetObjectList(ObjectLayer::Player);

	//칼든애
	DaggerImp* DaggerImp1 = new DaggerImp();
	DaggerImp1->Init();
	DaggerImp1->SetObject();
	DaggerImp1->SetPosition(x, y);
	DaggerImp1->SetPlayerPtr((Player*)player[0]);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Enemy, DaggerImp1);

}
void Scene02::AddPotion(float x, float y)
{
	//템
	Potion* potion1 = new Potion();
	potion1->Init(x, y,0);
	potion1->SetObject();
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Item, potion1);

}
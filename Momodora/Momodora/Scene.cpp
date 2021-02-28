#include "pch.h"
#include "Scene.h"
#include "Bomb.h"
#include "Monkey.h"
#include "DaggerImp.h"
#include "BombImp.h"
#include "ShieldImp.h"
#include "Witch.h"
#include "Potion.h"
#include "Player.h"
#include "Fennel.h"

//적생성
void Scene::AddMonkey(float x, float y)
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

void Scene::AddWitch(float x, float y)
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
void Scene::AddBombImp(float x, float y)
{
	vector<GameObject*> player = OBJECTMANAGER->GetObjectList(ObjectLayer::Player);

	//폭탄
	BombImp* BombImp1 = new BombImp();
	BombImp1->Init();
	BombImp1->SetObject();
	BombImp1->SetPosition(x, y);
	BombImp1->SetPlayerPtr((Player*)player[0]);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Enemy, BombImp1);
}
void Scene::AddShieldImp(float x, float y)
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
void Scene::AddDaggerImp(float x, float y)
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
void Scene::AddPotion(float x, float y)
{
	//템
	Potion* potion1 = new Potion();
	potion1->Init(x, y, 0);
	potion1->SetObject();
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Item, potion1);

}

void Scene::AddFennel(float x, float y)
{
	vector<GameObject*> player = OBJECTMANAGER->GetObjectList(ObjectLayer::Player);

	//페넬
	Fennel* Fennel1 = new Fennel();
	Fennel1->Init();
	Fennel1->SetObject();
	Fennel1->SetPosition(x, y);
	Fennel1->SetPlayerPtr((Player*)player[0]);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Enemy, Fennel1);
}


void Scene::AllCollision()
{
	vector<GameObject*> enemyList = OBJECTMANAGER->GetObjectList(ObjectLayer::Enemy);
	vector<GameObject*> arrowList = OBJECTMANAGER->GetObjectList(ObjectLayer::PlayerArrow);
	vector<GameObject*> daggerList = OBJECTMANAGER->GetObjectList(ObjectLayer::EnemyDagger);
	vector<GameObject*> bombList = OBJECTMANAGER->GetObjectList(ObjectLayer::EnemyBomb);
	vector<GameObject*> staffList = OBJECTMANAGER->GetObjectList(ObjectLayer::EnemyStaff);
	vector<GameObject*> leaf = OBJECTMANAGER->GetObjectList(ObjectLayer::PlayerLeaf);
	Player* player = OBJECTMANAGER->GetPlayer();
	RECT playerHitBox = player->GetHitBox();
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
				player->SetHitAttack(false);

				//적체력깎기
				int atk = player->GetAttackDamage();
				((Enemy*)(enemyList[i]))->TakeHp(2);

				//방향 정하고
				Direction direction = COLLISIONMANAGER->CheckSide(&hitBox, &playerAtkBox);
				//적 아픈모션, 스턴 재생
				((Enemy*)(enemyList[i]))->Hurt(direction);


				//에너미 맞은상태 true
				((Enemy*)(enemyList[i]))->SetIsHit(true);
			}
		}
		//플레이어의 공격애니메이션하나가 끝나면
		if (player->GetHitAttack())
		{
			((Enemy*)(enemyList[i]))->SetIsHit(false);
		}

	}

	//단도, 플레이어 히트박스 충돌
	for (int i = 0;i < daggerList.size();i++)
	{
		RECT temp;
		RECT dagger = daggerList[i]->GetHitBox();
		if (IntersectRect(&temp, &playerHitBox, &dagger))
		{
			//단도없애고
			//daggerList[i]->Release();
			daggerList[i]->SetIsDestroy(true);

			//플레이어 체력 깎기
			//방향알려줘야해
			Direction direction = COLLISIONMANAGER->CheckSide(&playerHitBox, &dagger);
			//플레이어 상태전환하고 무적시키는 함수
			player->PlayerHurt(direction);
		}
	}
	//폭탄, 플레이어 히트박스 충돌
	for (int i = 0;i < bombList.size();i++)
	{
		RECT temp;
		RECT bomb = bombList[i]->GetHitBox();
		if (IntersectRect(&temp, &playerHitBox, &bomb))
		{
			//폭탄 터트리고
			((Bomb*)bombList[i])->Explode();

			//플레이어 체력 깎기

			//방향알려줘야해
			Direction direction = COLLISIONMANAGER->CheckSide(&playerHitBox, &bomb);
			//플레이어 상태전환하고 무적시키는 함수
			player->PlayerHurt(direction);
		}
	}
	//지팡이, 플레이어 히트박스 충돌
	for (int i = 0;i < staffList.size();i++)
	{
		RECT temp;
		RECT staff = staffList[i]->GetRect();
		if (IntersectRect(&temp, &playerHitBox, &staff))
		{

			//플레이어 체력 깎기

			//방향알려줘야해
			Direction direction = COLLISIONMANAGER->CheckSide(&playerHitBox, &staff);
			//플레이어 상태전환하고 무적시키는 함수
			player->PlayerHurt(direction);
		}
	}
	//적의 근접공격, 플레이어 히트박스 충돌
	for (int i = 0;i < enemyList.size();i++)
	{
		RECT temp;
		RECT atkBox = enemyList[i]->GetAttackBox();

		if (IntersectRect(&temp, &playerHitBox, &atkBox))
		{

			//플레이어 체력 깎기

			//플레이어 상태전환하고 무적시키는 함수
			Direction direction = COLLISIONMANAGER->CheckSide(&playerHitBox, &atkBox);
			//방향알려줘야해
			player->PlayerHurt(direction);
		}
	}


}
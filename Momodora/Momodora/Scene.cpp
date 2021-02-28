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
#include "Boss.h"
#include "BossBullet.h"
//#include "Effect.h"

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
	vector<GameObject*> e =  OBJECTMANAGER->GetObjectList(ObjectLayer::Boss);

	vector<GameObject*> enemyList = OBJECTMANAGER->GetObjectList(ObjectLayer::Enemy);
	vector<GameObject*> arrowList = OBJECTMANAGER->GetObjectList(ObjectLayer::PlayerArrow);
	vector<GameObject*> daggerList = OBJECTMANAGER->GetObjectList(ObjectLayer::EnemyDagger);
	vector<GameObject*> bombList = OBJECTMANAGER->GetObjectList(ObjectLayer::EnemyBomb);
	vector<GameObject*> staffList = OBJECTMANAGER->GetObjectList(ObjectLayer::EnemyStaff);
	vector<GameObject*> leaf = OBJECTMANAGER->GetObjectList(ObjectLayer::PlayerLeaf);
	vector<GameObject*> bossBullet = OBJECTMANAGER->GetObjectList(ObjectLayer::BossBullet);
	Player* player = OBJECTMANAGER->GetPlayer();
	RECT playerHitBox = player->GetHitBox();
	RECT playerAtkBox = leaf[0]->GetAttackBox();

	//적히트박스, 플레이어 화살 충돌
	for (int i = 0; i < enemyList.size(); i++)
	{
		for (int j = 0; j < arrowList.size(); j++)
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

				//이펙트 만들고
				Effect* effect1 = new Effect();
				effect1->Init(L"Hit", temp.right + 20, temp.top + 10, 0, 3, 0.1);
			}
		}
	}
	//적히트박스, 플레이어의 리프 충돌
	for (int i = 0; i < enemyList.size(); i++)
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

				//이펙트 만들고
				Effect* effect1 = new Effect();
				effect1->Init(L"Hit", temp.right + 20, temp.top + 10, 0, 3, 0.1);
			}
		}
		//플레이어의 공격애니메이션하나가 끝나면
		if (player->GetHitAttack())
		{
			((Enemy*)(enemyList[i]))->SetIsHit(false);
		}

	}

	//단도, 플레이어 히트박스 충돌
	for (int i = 0; i < daggerList.size(); i++)
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
	for (int i = 0; i < bombList.size(); i++)
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
	for (int i = 0; i < staffList.size(); i++)
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
	for (int i = 0; i < enemyList.size(); i++)
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
	// 보스 공격이랑 플레이어 충돌
	for (int i = 0; i < bossBullet.size(); i++)
	{
		RECT temp;
		RECT atkBox = bossBullet[i]->GetAttackBox();

		if (((BossBullet*)bossBullet[i])->GetShoot())
		{
			if (IntersectRect(&temp, &playerHitBox, &atkBox))
			{
				bossBullet[i]->SetIsActive(false);
				bossBullet[i]->SetIsDestroy(true);
				//플레이어 체력 깎기

				//플레이어 상태전환하고 무적시키는 함수
				Direction direction = COLLISIONMANAGER->CheckSide(&playerHitBox, &atkBox);
				//방향알려줘야해
				player->PlayerHurt(direction);
			}
			/*bossBullet[i]->SetIsActive(false);
			bossBullet[i]->SetIsDestroy(true);
			//플레이어 체력 깎기

			//플레이어 상태전환하고 무적시키는 함수
			Direction direction = COLLISIONMANAGER->CheckSide(&playerHitBox, &atkBox);
			//방향알려줘야해
			player->PlayerHurt(direction);*/
		}
	}

	// 보스랑 화살
	if (OBJECTMANAGER->FindObject("Boss") != NULL)
	{
		for (int j = 0; j < arrowList.size(); j++)
		{
			RECT temp;
			RECT hitBox = OBJECTMANAGER->FindObject("Boss")->GetHitBox();
			RECT arrow = arrowList[j]->GetRect();
			if (IntersectRect(&temp, &hitBox, &arrow))
			{
				//화살 없애고
				//arrowList[j]->Release();
				//arrowList[j]->SetIsActive(false);
				arrowList[j]->SetIsDestroy(true);
				//에너미 체력조정
				((Boss*)OBJECTMANAGER->FindObject("Boss"))->Hit();
				((Boss*)OBJECTMANAGER->FindObject("Boss"))->SetHp(((Boss*)OBJECTMANAGER->FindObject("Boss"))->GetHP() - 5);

				//이펙트 만들고
				Effect* effect1 = new Effect();
				effect1->Init(L"Hit", temp.right, temp.top, 0, 3, 0.1);
			}
		}
	}
	//적히트박스, 플레이어의 리프 충돌
	for (int i = 0; i < e.size(); ++i) // for문 size 있을 때만 들어올 수 있게 감싸줬음
	{
		if (!((Boss*)OBJECTMANAGER->FindObject("Boss"))->GetInvincibility())
		{
			RECT hitBox = ((Boss*)OBJECTMANAGER->FindObject("Boss"))->GetHitBox();
			RECT temp;
			if (IntersectRect(&temp, &hitBox, &playerAtkBox))
			{
				//플레이어 불값바꾸기
				player->SetEndCombo(false);
				//적체력깎기
				//int atk = player->GetAttackDamage();
				((Boss*)OBJECTMANAGER->FindObject("Boss"))->SetHp(((Boss*)OBJECTMANAGER->FindObject("Boss"))->GetHP()
					- ((100 - ((Boss*)OBJECTMANAGER->FindObject("Boss"))->GetDef()) / 100.f * OBJECTMANAGER->GetPlayer()->GetAttackDamage()));
				//에너미 맞은상태 true
				((Boss*)OBJECTMANAGER->FindObject("Boss"))->Hit();
			}
		}
	}
	
	//플레이어의 공격 애니메이션 하나가 끝나면
	if (OBJECTMANAGER->FindObject("Boss") != NULL)
	{
		if (player->GetEndCombo())
		{
			((Boss*)OBJECTMANAGER->FindObject("Boss"))->SetIsHit(false);
			((Boss*)OBJECTMANAGER->FindObject("Boss"))->SetInvincibility(false);
		}
	}

}
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
#include "Effect.h"

//������
void Scene::AddMonkey(float x, float y)
{
	vector<GameObject*> player = OBJECTMANAGER->GetObjectList(ObjectLayer::Player);
	//��Ű����

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

	//����
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

	//��ź
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

	//����
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

	//Į���
	DaggerImp* DaggerImp1 = new DaggerImp();
	DaggerImp1->Init();
	DaggerImp1->SetObject();
	DaggerImp1->SetPosition(x, y);
	DaggerImp1->SetPlayerPtr((Player*)player[0]);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Enemy, DaggerImp1);

}
void Scene::AddPotion(float x, float y)
{
	//��
	Potion* potion1 = new Potion();
	potion1->Init(x, y, 0);
	potion1->SetObject();
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Item, potion1);

}

void Scene::AddFennel(float x, float y)
{
	vector<GameObject*> player = OBJECTMANAGER->GetObjectList(ObjectLayer::Player);

	//���
	Fennel* Fennel1 = new Fennel();
	Fennel1->Init();
	Fennel1->SetObject();
	Fennel1->SetPosition(x, y);
	Fennel1->SetPlayerPtr((Player*)player[0]);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Enemy, Fennel1);
}

void Scene::AllCollision()
{
	vector<GameObject*> e = OBJECTMANAGER->GetObjectList(ObjectLayer::Boss);

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

	//����Ʈ�ڽ�, �÷��̾� ȭ�� �浹
	for (int i = 0; i < enemyList.size(); i++)
	{
		for (int j = 0; j < arrowList.size(); j++)
		{
			RECT temp;
			RECT hitBox = enemyList[i]->GetHitBox();
			RECT arrow = arrowList[j]->GetRect();
			if (IntersectRect(&temp, &hitBox, &arrow))
			{
				//ȭ�� ���ְ�
				//arrowList[j]->Release();
				//arrowList[j]->SetIsActive(false);
				arrowList[j]->SetIsDestroy(true);
				//���ʹ� ü������
				((Enemy*)(enemyList[i]))->TakeHp(20);

				//����Ʈ �����
				Effect* effect1 = new Effect();
				effect1->Init(L"Hit", temp.right + 20, temp.top + 10, 0, 3, 0.1);
			}
		}
	}
	//����Ʈ�ڽ�, �÷��̾��� ���� �浹
	for (int i = 0; i < enemyList.size(); i++)
	{
		//���� �̸̹������´�?
		if (!((Enemy*)(enemyList[i]))->GetIsHit())
		{
			RECT hitBox = enemyList[i]->GetHitBox();
			RECT temp;
			if (IntersectRect(&temp, &hitBox, &playerAtkBox))
			{
				//�÷��̾� �Ұ��ٲٱ�
				player->SetHitAttack(false);

				//��ü�±��
				int atk = player->GetAttackDamage();
				((Enemy*)(enemyList[i]))->TakeHp(atk);

				//���� ���ϰ�
				Direction direction = COLLISIONMANAGER->CheckSide(&hitBox, &playerAtkBox);
				//�� ���¸��, ���� ���
				((Enemy*)(enemyList[i]))->Hurt(direction);

				//���ʹ� �������� true
				((Enemy*)(enemyList[i]))->SetIsHit(true);

				//����Ʈ �����
				Effect* effect1 = new Effect();
				effect1->Init(L"Hit", temp.right + 20, temp.top + 10, 0, 3, 0.1);

				//�Ҹ�
				SOUNDMANAGER->Play(L"Leaf", 0.05f);
			}
		}
		//�÷��̾��� ���ݾִϸ��̼��ϳ��� ������
		if (player->GetHitAttack())
		{
			((Enemy*)(enemyList[i]))->SetIsHit(false);
		}

	}

	//�ܵ�, �÷��̾� ��Ʈ�ڽ� �浹
	for (int i = 0; i < daggerList.size(); i++)
	{
		RECT temp;
		RECT dagger = daggerList[i]->GetHitBox();
		if (IntersectRect(&temp, &playerHitBox, &dagger))
		{
			//�ܵ����ְ�
			//daggerList[i]->Release();
			daggerList[i]->SetIsDestroy(true);

			//�÷��̾� ü�� ���
			player->SetHp(player->GetHp() - 10);

			//����˷������
			Direction direction = COLLISIONMANAGER->CheckSide(&playerHitBox, &dagger);
			//�÷��̾� ������ȯ�ϰ� ������Ű�� �Լ�
			player->PlayerHurt(direction);
		}
	}
	//��ź, �÷��̾� ��Ʈ�ڽ� �浹
	for (int i = 0; i < bombList.size(); i++)
	{
		RECT temp;
		RECT bomb = bombList[i]->GetHitBox();
		if (IntersectRect(&temp, &playerHitBox, &bomb))
		{
			//��ź ��Ʈ����
			((Bomb*)bombList[i])->Explode();

			//�÷��̾� ü�� ���
			player->SetHp(player->GetHp() - 30);

			//����˷������
			Direction direction = COLLISIONMANAGER->CheckSide(&playerHitBox, &bomb);
			//�÷��̾� ������ȯ�ϰ� ������Ű�� �Լ�
			player->PlayerHurt(direction);
		}
	}
	//������, �÷��̾� ��Ʈ�ڽ� �浹
	for (int i = 0; i < staffList.size(); i++)
	{
		RECT temp;
		RECT staff = staffList[i]->GetRect();
		if (IntersectRect(&temp, &playerHitBox, &staff))
		{

			//�÷��̾� ü�� ���
			player->SetHp(player->GetHp() - 20);
			//����˷������
			Direction direction = COLLISIONMANAGER->CheckSide(&playerHitBox, &staff);
			//�÷��̾� ������ȯ�ϰ� ������Ű�� �Լ�
			player->PlayerHurt(direction);
		}
	}
	//���� ��������, �÷��̾� ��Ʈ�ڽ� �浹
	for (int i = 0; i < enemyList.size(); i++)
	{
		RECT temp;
		RECT atkBox = enemyList[i]->GetAttackBox();

		if (IntersectRect(&temp, &playerHitBox, &atkBox))
		{

			//�÷��̾� ü�� ���
			player->SetHp(player->GetHp() - 10);
			//�÷��̾� ������ȯ�ϰ� ������Ű�� �Լ�
			Direction direction = COLLISIONMANAGER->CheckSide(&playerHitBox, &atkBox);
			//����˷������
			player->PlayerHurt(direction);
		}
	}
	// ���� �����̶� �÷��̾� �浹
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
				//�÷��̾� ü�� ���

				//�÷��̾� ������ȯ�ϰ� ������Ű�� �Լ�
				Direction direction = COLLISIONMANAGER->CheckSide(&playerHitBox, &atkBox);
				//����˷������
				player->PlayerHurt(direction);
			}
			/*bossBullet[i]->SetIsActive(false);
			bossBullet[i]->SetIsDestroy(true);
			//�÷��̾� ü�� ���

			//�÷��̾� ������ȯ�ϰ� ������Ű�� �Լ�
			Direction direction = COLLISIONMANAGER->CheckSide(&playerHitBox, &atkBox);
			//����˷������
			player->PlayerHurt(direction);*/
		}
	}

	// ������ ȭ��
	if (OBJECTMANAGER->FindObject("Boss") != NULL)
	{
		for (int j = 0; j < arrowList.size(); j++)
		{
			RECT temp;
			RECT hitBox = OBJECTMANAGER->FindObject("Boss")->GetHitBox();
			RECT arrow = arrowList[j]->GetRect();
			if (IntersectRect(&temp, &hitBox, &arrow))
			{
				//ȭ�� ���ְ�
				//arrowList[j]->Release();
				//arrowList[j]->SetIsActive(false);
				arrowList[j]->SetIsDestroy(true);
				//���ʹ� ü������
				((Boss*)OBJECTMANAGER->FindObject("Boss"))->Hit();
				((Boss*)OBJECTMANAGER->FindObject("Boss"))->SetHp(((Boss*)OBJECTMANAGER->FindObject("Boss"))->GetHP() - 5);

				//����Ʈ �����
				Effect* effect1 = new Effect();
				effect1->Init(L"Hit", temp.right, temp.top, 0, 3, 0.1);
			}
		}
	}
	//����Ʈ�ڽ�, �÷��̾��� ���� �浹
	for (int i = 0; i < e.size(); ++i) // for�� size ���� ���� ���� �� �ְ� ��������
	{
		if (!((Boss*)OBJECTMANAGER->FindObject("Boss"))->GetInvincibility())
		{
			RECT hitBox = ((Boss*)OBJECTMANAGER->FindObject("Boss"))->GetHitBox();
			RECT temp;
			if (IntersectRect(&temp, &hitBox, &playerAtkBox))
			{
				//�÷��̾� �Ұ��ٲٱ�
				player->SetEndCombo(false);
				//��ü�±��
				//int atk = player->GetAttackDamage();
				((Boss*)OBJECTMANAGER->FindObject("Boss"))->SetHp(((Boss*)OBJECTMANAGER->FindObject("Boss"))->GetHP()
					- ((100 - ((Boss*)OBJECTMANAGER->FindObject("Boss"))->GetDef()) / 100.f * OBJECTMANAGER->GetPlayer()->GetAttackDamage()));
				//���ʹ� �������� true
				((Boss*)OBJECTMANAGER->FindObject("Boss"))->Hit();
			}
		}
	}

	//�÷��̾��� ���� �ִϸ��̼� �ϳ��� ������
	if (OBJECTMANAGER->FindObject("Boss") != NULL)
	{
		if (player->GetEndCombo())
		{
			((Boss*)OBJECTMANAGER->FindObject("Boss"))->SetIsHit(false);
			((Boss*)OBJECTMANAGER->FindObject("Boss"))->SetInvincibility(false);
		}
	}
}
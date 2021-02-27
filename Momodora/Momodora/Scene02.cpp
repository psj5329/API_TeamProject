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
	// �� ������� ��� �� ������ �޾Ƽ� �� ������ �ʱ�ȭ �ؾ� ��
	mSceneSizeX = 3000;
	mSceneSizeY = 3000;
	// ��������� �ӽ� ������

	vector<GameObject*> player = OBJECTMANAGER->GetObjectList(ObjectLayer::Player);
	mPlayer = (Player*)player[0];
	
	//�÷��������
	mPlatform01 = new Platform();
	mPlatform01->SetPlatform(0, 600, 800, 650, PlatformType::Normal);
	OBJECTMANAGER->AddObject(ObjectLayer::Platform, (GameObject*)mPlatform01);
	mGround = { 0,600,800,650 };


	//�������
	//AddMonkey(WINSIZEX / 2 - 100, mPlatform01->GetRect().top);
	AddBombImp(WINSIZEX / 2, mPlatform01->GetRect().top);
	//AddDaggerImp(WINSIZEX / 2 - 300, mPlatform01->GetRect().top);
	AddWitch(WINSIZEX / 2 + 100,mPlatform01->GetRect().top);
	//AddPotion(WINSIZEX / 2 + 350, 550);

	////���
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
	//�� ����������Ʈ

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

	//����Ʈ�ڽ�, �÷��̾� ȭ�� �浹
	for (int i = 0;i < enemyList.size();i++)
	{
		for (int j = 0;j < arrowList.size(); j++)
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
			}
		}
	}
	//����Ʈ�ڽ�, �÷��̾��� ���� �浹
	for (int i = 0;i < enemyList.size();i++)
	{
		//���� �̸̹������´�?
		if (!((Enemy*)(enemyList[i]))->GetIsHit())
		{
			RECT hitBox = enemyList[i]->GetHitBox();
			RECT temp;
			if (IntersectRect(&temp, &hitBox, &playerAtkBox))
			{
				//�÷��̾� �Ұ��ٲٱ�
				mPlayer->SetEndCombo(false);
				//��ü�±��
				int atk = mPlayer->GetAttackDamage();
				((Enemy*)(enemyList[i]))->TakeHp(30);
				//���ʹ� �������� true
				((Enemy*)(enemyList[i]))->SetIsHit(true);
			}
		}
		//�÷��̾��� ���ݾִϸ��̼��ϳ��� ������
		if (mPlayer->GetEndCombo())
		{
			((Enemy*)(enemyList[i]))->SetIsHit(false);
		}

	}

	//�ܵ�, �÷��̾� ��Ʈ�ڽ� �浹
	for (int i = 0;i < daggerList.size();i++)
	{
		RECT temp;
		RECT dagger = daggerList[i]->GetHitBox();
		if (IntersectRect(&temp, &playertHitBox, &dagger))
		{
			//�ܵ����ְ�
			//daggerList[i]->Release();
			daggerList[i]->SetIsDestroy(true);

			//�÷��̾� ü�� ���
			//����˷������
			Direction direction = COLLISIONMANAGER->CheckSide(&playertHitBox, &dagger);
			//�÷��̾� ������ȯ�ϰ� ������Ű�� �Լ�
			mPlayer->PlayerHurt();
		}
	}
	//��ź, �÷��̾� ��Ʈ�ڽ� �浹
	for (int i = 0;i < bombList.size();i++)
	{
		RECT temp;
		RECT bomb = bombList[i]->GetHitBox();
		if (IntersectRect(&temp, &playertHitBox, &bomb))
		{
			//��ź ��Ʈ����
			((Bomb*)bombList[i])->Explode();

			//�÷��̾� ü�� ���
			//����˷������
			Direction direction = COLLISIONMANAGER->CheckSide(&playertHitBox, &bomb);
			//�÷��̾� ������ȯ�ϰ� ������Ű�� �Լ�
			mPlayer->PlayerHurt();
		}
	}
	//������, �÷��̾� ��Ʈ�ڽ� �浹
	for (int i = 0;i < staffList.size();i++)
	{
		RECT temp;
		RECT staff = staffList[i]->GetRect();
		if (IntersectRect(&temp, &playertHitBox, &staff))
		{

			//�÷��̾� ü�� ���
			//����˷������
			Direction direction = COLLISIONMANAGER->CheckSide(&playertHitBox, &staff);
			//�÷��̾� ������ȯ�ϰ� ������Ű�� �Լ�
			mPlayer->PlayerHurt();
		}
	}
	//���� ��������, �÷��̾� ��Ʈ�ڽ� �浹
	for (int i = 0;i < enemyList.size();i++)
	{
		RECT temp;
		RECT atkBox = enemyList[i]->GetAttackBox();

		if (IntersectRect(&temp, &playertHitBox, &atkBox))
		{

			//�÷��̾� ü�� ���
			//�÷��̾� ������ȯ�ϰ� ������Ű�� �Լ�
			Direction direction = COLLISIONMANAGER->CheckSide(&playertHitBox, &atkBox);
			//����˷������
			mPlayer->PlayerHurt();
		}
	}




}

void Scene02::Render(HDC hdc)
{
	wstring str = L"��2 ������";
	TextOut(hdc, 100, 200, str.c_str(), (int)str.length());
	

	CAMERAMANAGER->GetMainCamera()->Render(hdc, mMap, 0, 0);
	OBJECTMANAGER->Render(hdc);

	CAMERAMANAGER->GetMainCamera()->RenderRectInCamera(hdc,mGround);

	wstring str3 = L"MouseX:" + to_wstring(_mousePosition.x);
	TextOut(hdc, _mousePosition.x+10, _mousePosition.y + 10, str3.c_str(), str3.length());
	wstring str4 = L"MouseY:" + to_wstring(_mousePosition.y);
	TextOut(hdc, _mousePosition.x+10, _mousePosition.y + 30, str4.c_str(), str4.length());
}

//������
void Scene02::AddMonkey(float x, float y)
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

void Scene02::AddWitch(float x, float y)
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
void Scene02::AddBombImp(float x, float y)
{
	vector<GameObject*> player = OBJECTMANAGER->GetObjectList(ObjectLayer::Player);

	//��ź
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

	//����
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

	//Į���
	DaggerImp* DaggerImp1 = new DaggerImp();
	DaggerImp1->Init();
	DaggerImp1->SetObject();
	DaggerImp1->SetPosition(x, y);
	DaggerImp1->SetPlayerPtr((Player*)player[0]);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Enemy, DaggerImp1);

}
void Scene02::AddPotion(float x, float y)
{
	//��
	Potion* potion1 = new Potion();
	potion1->Init(x, y,0);
	potion1->SetObject();
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Item, potion1);

}
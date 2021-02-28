#include "pch.h"
#include "Scene09.h"
#include "Camera.h"

#include "Boss.h"
#include "StarItem.h"
#include "Player.h"

#include "Platform.h"
#include "Ladder.h"

#include "BossHpUI.h"
#include "PlayerHpUI.h"
#include "ActiveItemUI.h"
#include "StarCountUI.h"

#include "GameEvent.h"
#include "Animation.h"

#include "Scene.h"

void Scene09::Init()
{
	mMapImage = IMAGEMANAGER->FindImage(L"Background_Boss");
	mPlatformImage = IMAGEMANAGER->FindImage(L"platform1");
	mPlatformImage2 = IMAGEMANAGER->FindImage(L"platform3");
	mSceneSizeX = mMapImage->GetWidth();
	mSceneSizeY = mMapImage->GetHeight();

	Boss* boss = new Boss;
	boss->Init();
	boss->SetObject();
	boss->SetAnimation();
	OBJECTMANAGER->AddObject(ObjectLayer::Boss, boss);

	Platform* platform01 = new Platform();
	platform01->SetPlatform(0, 604, 960, 643, PlatformType::Normal);
	OBJECTMANAGER->AddObject(ObjectLayer::Platform, (GameObject*)platform01);

	Platform* platform02 = new Platform();
	platform02->SetPlatform(0, 1460, 960, 1600, PlatformType::Normal);
	OBJECTMANAGER->AddObject(ObjectLayer::Platform, (GameObject*)platform02);

	BossHpUI* ui = new BossHpUI;
	ui->Init();
	ui->SetHp(((Enemy*)OBJECTMANAGER->FindObject(ObjectLayer::Boss, "Boss"))->GetHP());
	OBJECTMANAGER->AddObject(ObjectLayer::BossUI, ui);

	PlayerHpUI* playerui = new PlayerHpUI;
	playerui->Init();
	playerui->SetHp(OBJECTMANAGER->GetPlayer()->GetHp());
	OBJECTMANAGER->AddObject(ObjectLayer::UI, playerui);

	ActiveItemUI* activeItemui = new ActiveItemUI;
	activeItemui->Init();
	OBJECTMANAGER->AddObject(ObjectLayer::UI, activeItemui);

	StarCountUI* starCountui = new StarCountUI;
	starCountui->Init();
	OBJECTMANAGER->AddObject(ObjectLayer::UI, starCountui);

	Camera* main = CAMERAMANAGER->GetMainCamera();
	main->SetMode(Camera::Mode::Fix);
	//main->SetMode(Camera::Mode::Follow);
	GameObject* player = (GameObject*)(OBJECTMANAGER->GetPlayer());
	main->SetTarget(player);

	if (mEntrance == 1)
	{
		player->SetX(50);
		player->SetY(556);
		main->SetFixX(480);
		main->SetFixY(360);
	}
	else // �� else �κ��� ���� �÷��̿����� �������� ��, �ٷ� 9�� �� �����ص� ���� ��ġ���� ������ �� �ְ� �س��� ������
	{
		player->SetX(50);
		player->SetY(556);
		main->SetFixX(480);
		main->SetFixY(360);
	}
	mCameraFix = true;

	mIsBossDead = false;
}

void Scene09::Release()
{
}

void Scene09::Update()
{
	if (mCameraFix) // �ٴ� ������ �̺�Ʈ �߻��ϴ� ���뿡 �� if�� ������ �ɵ�?
	{
		GameObject* player = (GameObject*)(OBJECTMANAGER->GetPlayer());
		if (player->GetX() >= mSceneSizeX / 2.f) // ������ �� �����ϸ� ����ī�޶󿴴ٰ� x������ �߰� ������ ī�޶� ���� �÷��̾�� �ٲ�� �س��� �̺�Ʈ �� �������� �� ���� �� �ְ� �ص�
		{
			Camera* main = CAMERAMANAGER->GetMainCamera();
			main->SetMode(Camera::Mode::Follow);
			main->SetTarget(player);
		}
	}

	if (INPUT->GetKeyDown(VK_RETURN))
	{
		StarItem* star = new StarItem;
		star->Init();
		star->SetX(200);
		star->SetY(WINSIZEY / 3 * 2);
		star->SetAngle((rand() % 180) * PI / 180.f);
		OBJECTMANAGER->AddObject(ObjectLayer::Item, star);
	}

	if (INPUT->GetKeyDown('I'))
	{
		if (((ActiveItemUI*)OBJECTMANAGER->FindObject("ActiveItemUI"))->GetItemCount() < 9)
			((ActiveItemUI*)OBJECTMANAGER->FindObject("ActiveItemUI"))->SetItemCount(
			((ActiveItemUI*)OBJECTMANAGER->FindObject("ActiveItemUI"))->GetItemCount() + 1);
	}

	if (INPUT->GetKeyDown('O'))
	{
		((Boss*)OBJECTMANAGER->FindObject("Boss"))->SetHp(0);
	}

	//mBoss->Update();
	OBJECTMANAGER->Update();

	// �浹
	AllCollision();

	/*	//vector<GameObject*> vecArrow = OBJECTMANAGER->GetObjectList(ObjectLayer::PlayerArrow);
		//vector<GameObject*> vecLeaf = OBJECTMANAGER->GetObjectList(ObjectLayer::PlayerLeaf);

		//// ȭ��� �浹
		//for (int i = 0; i < vecArrow.size(); ++i)
		//{
		//	if (COLLISIONMANAGER->IsCollision(&((Boss*)OBJECTMANAGER->FindObject("Boss"))->GetRect(), &vecArrow[i]->GetRect()))
		//	{
		//		((Boss*)OBJECTMANAGER->FindObject("Boss"))->Hit();
		//		((Boss*)OBJECTMANAGER->FindObject("Boss"))->SetHp(((Boss*)OBJECTMANAGER->FindObject("Boss"))->GetHP()
		//			- ((Arrow*)vecArrow[i])->GetArrowDamage());
		//		//vecArrow.erase(vecArrow[i]);
		//	}
		//}

		//// �÷��̾� ������ �浹
		//for (int i = 0; i < vecLeaf.size(); ++i)
		//{
		//	if (COLLISIONMANAGER->IsCollision(&((Boss*)OBJECTMANAGER->FindObject("Boss"))->GetRect(), &vecLeaf[i]->GetRect()))
		//	{
		//		((Boss*)OBJECTMANAGER->FindObject("Boss"))->Hit();
		//		((Boss*)OBJECTMANAGER->FindObject("Boss"))->SetHp(((Boss*)OBJECTMANAGER->FindObject("Boss"))->GetHP()
		//			- OBJECTMANAGER->GetPlayer()->GetAttackDamage());
		//	}
		//}
		Player* player = OBJECTMANAGER->GetPlayer();
		RECT playerrect = player->GetRect();
		if (COLLISIONMANAGER->IsCollision(&playerrect, ObjectLayer::BossBullet))	// �÷��̾� - ���� ����
		{
			if (OBJECTMANAGER->GetPlayer()->GetState() != PlayerState::Hurt)
			{
				//OBJECTMANAGER->GetPlayer()->SetHp(OBJECTMANAGER->GetPlayer()->GetHp() - 10);
				// �÷��̾� �����ǰ� �����ؾ���
				//Direction direction = COLLISIONMANAGER->CheckSide(&OBJECTMANAGER->GetPlayer()->GetHitBox(), &((Boss*)OBJECTMANAGER->FindObject("Boss"))->GetHitBox());
				//Direction direction = OBJECTMANAGER->GetPlayer()->GetDirection();
				//OBJECTMANAGER->GetPlayer()->PlayerHurt(direction);
			}
		}
		// }}*/

		// �̺�Ʈ �߰�
	if (!mIsBossAppearanceEvent && OBJECTMANAGER->GetPlayer()->GetX() >= WINSIZEX / 2)
	{
		mIsBossAppearanceEvent = true;
		GAMEEVENTMANAGER->PushEvent(new IObjectStop(true));
		GAMEEVENTMANAGER->PushEvent(new IDelayEvent(3.f));
		GAMEEVENTMANAGER->PushEvent(new IMoveGameObject(OBJECTMANAGER->FindObject("Boss"), ((Boss*)OBJECTMANAGER->FindObject("Boss"))->GetX()
			, 1600 - ((Boss*)OBJECTMANAGER->FindObject("Boss"))->GetSizeY() / 3 - 50, 0.f, -500.f));
		GAMEEVENTMANAGER->PushEvent(new IDelayEvent(1.f));

		GAMEEVENTMANAGER->PushEvent(new IObjectStop(false));	// ���� ���� �̺�Ʈ ��
	}

	if (!mIsBossDead && ((Boss*)OBJECTMANAGER->FindObject("Boss"))->GetHP() <= 0 && !((Boss*)OBJECTMANAGER->FindObject("Boss"))->GetEndEvent())
	{
		((Boss*)OBJECTMANAGER->FindObject("Boss"))->SetEndEvent(true);

		GAMEEVENTMANAGER->PushEvent(new IDelayEvent(1.f));

		GAMEEVENTMANAGER->PushEvent(new IScriptEvent(L"Boss_Dialogue1"));
		GAMEEVENTMANAGER->PushEvent(new IDelayEvent(0.5f));
		GAMEEVENTMANAGER->PushEvent(new IScriptEvent(L"Boss_Dialogue2"));
		GAMEEVENTMANAGER->PushEvent(new IDelayEvent(0.5f));

		GAMEEVENTMANAGER->PushEvent(new IEraseEvent(((Boss*)OBJECTMANAGER->FindObject("Boss"))->GetImage()
			, ((Boss*)OBJECTMANAGER->FindObject("Boss"))->GetBackImage(), 2.f, 0.07f));
	}

	GAMEEVENTMANAGER->Update();

	if (mIsBossAppearanceEvent)
	{
		mChangeImageTime += TIME->DeltaTime();

		if (mChangeImageTime >= 1.f)
		{
			mPlatformImage = IMAGEMANAGER->FindImage(L"platform2");
			OBJECTMANAGER->GetObjectList(ObjectLayer::Platform).front()->SetRect(WINSIZEX * 2, 604, WINSIZEX * 2 + 960, 643);
		}

		if (OBJECTMANAGER->GetPlayer()->GetY() >= 1600 - WINSIZEY / 2)//1460 - OBJECTMANAGER->GetPlayer()->GetSizeY() / 2)
		{
			mCameraFix = false;
			CAMERAMANAGER->GetMainCamera()->SetMode(Camera::Mode::Fix);
			CAMERAMANAGER->GetMainCamera()->SetFix(WINSIZEX / 2, 1600 - WINSIZEY / 2 - 50);

			if (!OBJECTMANAGER->FindObject("BossHpUI")->GetIsActive())
			{
				OBJECTMANAGER->FindObject("BossHpUI")->SetIsActive(true);
			}
		}
	}
}

void Scene09::Render(HDC hdc)
{
	// �� �̹���
	CAMERAMANAGER->GetMainCamera()->ScaleRender(hdc, mMapImage, 0, 0, mSceneSizeX, mSceneSizeY);

	// {{ �浹 üũ�� ��
	vector<GameObject*> platformList = OBJECTMANAGER->GetObjectList(ObjectLayer::Platform);
	vector<GameObject*>::iterator iter1 = platformList.begin();


	for (; iter1 != platformList.end(); ++iter1)
		CAMERAMANAGER->GetMainCamera()->RenderRectInCamera(hdc, (*iter1)->GetRect());

	// �浹 üũ�� �� }}

	OBJECTMANAGER->Render(hdc);

	CAMERAMANAGER->GetMainCamera()->ScaleRender(hdc, mPlatformImage, 0, 604, mPlatformImage->GetWidth(), mPlatformImage->GetHeight());
	CAMERAMANAGER->GetMainCamera()->ScaleRender(hdc, mPlatformImage2, 0, 1460, mPlatformImage->GetWidth(), mPlatformImage->GetHeight());

	OBJECTMANAGER->RenderUI(hdc);

	GAMEEVENTMANAGER->Render(hdc);
}
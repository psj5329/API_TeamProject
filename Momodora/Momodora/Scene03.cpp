#include "pch.h"
#include "Scene03.h"
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

void Scene03::Init()
{
	// 맵 배경으로 깔고 그 사이즈 받아서 맵 사이즈 초기화 해야 함
	mSceneSizeX = 960;
	mSceneSizeY = 1600;
	// 여기까지는 임시 데이터

	mMapImage = IMAGEMANAGER->FindImage(L"Background_Boss");
	mPlatformImage = IMAGEMANAGER->FindImage(L"platform1");

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

	//// {{ 충돌 체크용 맵
	//Platform* platform01 = new Platform();
	//platform01->SetPlatform(0, 600, 800, 650, PlatformType::Normal);
	//OBJECTMANAGER->AddObject(ObjectLayer::Platform, (GameObject*)platform01);

	//Platform* platform02 = new Platform();
	//platform02->SetPlatform(600, 400, 800, 450, PlatformType::DownJump);
	//OBJECTMANAGER->AddObject(ObjectLayer::Platform, (GameObject*)platform02);

	//Ladder* ladder01 = new Ladder();
	//ladder01->SetLadder(675, 450, 725, 600);
	//OBJECTMANAGER->AddObject(ObjectLayer::Ladder, (GameObject*)ladder01);
	//// 충돌 체크용 맵 }}

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
	//main->SetMode(Camera::Mode::Follow);
	//GameObject* player = (GameObject*)(OBJECTMANAGER->GetPlayer());
	//main->SetTarget(player);
	main->SetMode(Camera::Mode::Fix);
	main->SetFix(WINSIZEX / 2, WINSIZEY / 2);

	mIsBossDead = false;
}

void Scene03::Release()
{
}

void Scene03::Update()
{
	if (INPUT->GetKeyDown(VK_RETURN))
	{
		StarItem* star = new StarItem;
		star->Init();
		//star->SetX(OBJECTMANAGER->GetPlayer()->GetX());
		//star->SetY(OBJECTMANAGER->GetPlayer()->GetY());
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

	// 충돌 (상호작용 필요한 것만) {{
	// 풀레이어 공격 상태일 때 보스랑 충돌 확인
/*	if ((OBJECTMANAGER->GetPlayer()->GetState() == State::LeftAirAttack)
		|| (OBJECTMANAGER->GetPlayer()->GetState() == State::LeftAttack1)
		|| (OBJECTMANAGER->GetPlayer()->GetState() == State::LeftAttack2)
		|| (OBJECTMANAGER->GetPlayer()->GetState() == State::LeftAttack3)
		|| (OBJECTMANAGER->GetPlayer()->GetState() == State::RightAirAttack)
		|| (OBJECTMANAGER->GetPlayer()->GetState() == State::RightAttack1)
		|| (OBJECTMANAGER->GetPlayer()->GetState() == State::RightAttack2)
		|| (OBJECTMANAGER->GetPlayer()->GetState() == State::RightAttack3))
	{
		if (COLLISIONMANAGER->IsCollision(&OBJECTMANAGER->GetPlayer()->GetRect(), ObjectLayer::Boss))
		{
			if (!((Boss*)OBJECTMANAGER->FindObject("Boss"))->GetInvincibility())
			{
				((Boss*)OBJECTMANAGER->FindObject("Boss"))->Hit();
				((Boss*)OBJECTMANAGER->FindObject("Boss"))->SetHp(((Boss*)OBJECTMANAGER->FindObject("Boss"))->GetHP()
					- ((100 - ((Boss*)OBJECTMANAGER->FindObject("Boss"))->GetDef()) / 100.f * OBJECTMANAGER->GetPlayer()->GetAttackDamage()));
			}
		}
	}*/

	//if (COLLISIONMANAGER->IsCollision(&OBJECTMANAGER->GetPlayer()->GetRect(), ObjectLayer::EnemyProjectile))	// 플레이어 - 보스 패턴
	//{
	//	OBJECTMANAGER->GetPlayer()->SetHp(OBJECTMANAGER->GetPlayer()->GetHp() - 30);
	//	// 플레이어 무적되게 셋팅해야함
	//}
	// }}

	// 이벤트 추가
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
}

void Scene03::Render(HDC hdc)
{
	// 맵 이미지
	CAMERAMANAGER->GetMainCamera()->ScaleRender(hdc, mMapImage, 0, 0, mSceneSizeX, mSceneSizeY);

	// {{ 충돌 체크용 맵
	vector<GameObject*> platformList = OBJECTMANAGER->GetObjectList(ObjectLayer::Platform);
	vector<GameObject*>::iterator iter1 = platformList.begin();


	for (; iter1 != platformList.end(); ++iter1)
		CAMERAMANAGER->GetMainCamera()->RenderRectInCamera(hdc, (*iter1)->GetRect());

	// 충돌 체크용 맵 }}

	OBJECTMANAGER->Render(hdc);

	CAMERAMANAGER->GetMainCamera()->ScaleRender(hdc, mPlatformImage, 0, 604, mPlatformImage->GetWidth(), mPlatformImage->GetHeight());
	GAMEEVENTMANAGER->Render(hdc);
	//wstring str = L"씬3 페이지";
	//TextOut(hdc, WINSIZEX / 2, WINSIZEY / 2, str.c_str(), (int)str.length());
}
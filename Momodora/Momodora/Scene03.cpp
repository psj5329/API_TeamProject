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

void Scene03::Init()
{
	Boss* boss = new Boss;
	boss->Init();
	boss->SetObject();
	boss->SetAnimation();
	OBJECTMANAGER->AddObject(ObjectLayer::Boss, boss);


	// {{ 충돌 체크용 맵
	Platform* platform01 = new Platform();
	platform01->SetPlatform(0, 600, 800, 650, PlatformType::Normal);
	OBJECTMANAGER->AddObject(ObjectLayer::Platform, (GameObject*)platform01);

	Platform* platform02 = new Platform();
	platform02->SetPlatform(600, 400, 800, 450, PlatformType::DownJump);
	OBJECTMANAGER->AddObject(ObjectLayer::Platform, (GameObject*)platform02);

	Ladder* ladder01 = new Ladder();
	ladder01->SetLadder(675, 450, 725, 600);
	OBJECTMANAGER->AddObject(ObjectLayer::Platform, (GameObject*)ladder01);
	// 충돌 체크용 맵 }}

	BossHpUI* ui = new BossHpUI;
	ui->Init();
	ui->SetHp(((Enemy*)OBJECTMANAGER->FindObject(ObjectLayer::Boss, "Boss"))->GetHP());
	OBJECTMANAGER->AddObject(ObjectLayer::UI, ui);

	PlayerHpUI* playerui = new PlayerHpUI;
	playerui->Init();
	playerui->SetHp(((Enemy*)OBJECTMANAGER->FindObject(ObjectLayer::Boss, "Boss"))->GetHP());
	OBJECTMANAGER->AddObject(ObjectLayer::UI, playerui);

	ActiveItemUI* activeItemui = new ActiveItemUI;
	activeItemui->Init();
	OBJECTMANAGER->AddObject(ObjectLayer::UI, activeItemui);

	StarCountUI* starCountui = new StarCountUI;
	starCountui->Init();
	OBJECTMANAGER->AddObject(ObjectLayer::UI, starCountui);
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
		star->SetX(OBJECTMANAGER->GetPlayer()->GetX());
		star->SetY(OBJECTMANAGER->GetPlayer()->GetY());
		star->SetAngle((rand() % 180) * PI / 180.f);
		OBJECTMANAGER->AddObject(ObjectLayer::Item, star);
	}

	if (INPUT->GetKeyDown('I'))
	{
		if (((ActiveItemUI*)OBJECTMANAGER->FindObject("ActiveItemUI"))->GetItemCount() < 9)
			((ActiveItemUI*)OBJECTMANAGER->FindObject("ActiveItemUI"))->SetItemCount(
			((ActiveItemUI*)OBJECTMANAGER->FindObject("ActiveItemUI"))->GetItemCount() + 1);
	}

	if (INPUT->GetKeyDown('U'))
	{
		((StarCountUI*)OBJECTMANAGER->FindObject("StarCountUI"))->SetStarCount(
			((StarCountUI*)OBJECTMANAGER->FindObject("StarCountUI"))->GetStarCount() + 1);
	}

	//mBoss->Update();
	OBJECTMANAGER->Update();
}

void Scene03::Render(HDC hdc)
{
	// {{ 충돌 체크용 맵
	vector<GameObject*> platformList = OBJECTMANAGER->GetObjectList(ObjectLayer::Platform);
	vector<GameObject*>::iterator iter1 = platformList.begin();
	for (; iter1 != platformList.end(); ++iter1)
		CAMERAMANAGER->GetMainCamera()->RenderRectInCamera(hdc, (*iter1)->GetRect());

	vector<GameObject*> ladderList = OBJECTMANAGER->GetObjectList(ObjectLayer::Ladder);
	vector<GameObject*>::iterator iter2 = ladderList.begin();
	for (; iter2 != ladderList.end(); ++iter2)
		CAMERAMANAGER->GetMainCamera()->RenderRectInCamera(hdc, (*iter2)->GetRect());
	// 충돌 체크용 맵 }}

	OBJECTMANAGER->Render(hdc);
	//wstring str = L"씬3 페이지";
	//TextOut(hdc, WINSIZEX / 2, WINSIZEY / 2, str.c_str(), (int)str.length());
}
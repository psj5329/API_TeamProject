#include "pch.h"
#include "Scene05.h"
#include "Camera.h"

#include "Boss.h"
#include "Player.h"
#include "Platform.h"

#include "BossHpUI.h"
#include "PlayerHpUI.h"
#include "ActiveItemUI.h"
#include "StarCountUI.h"

#include "GameEvent.h"

void Scene05::Init()
{
	mMapImage = IMAGEMANAGER->FindImage(L"Background_Boss");
	mPlatformImage = IMAGEMANAGER->FindImage(L"platform1");
	mPlatformImage2 = IMAGEMANAGER->FindImage(L"platform3");
	mSceneSizeX = mMapImage->GetWidth();
	mSceneSizeY = mMapImage->GetHeight();

	SOUNDMANAGER->LoadFromFile(L"boss6", ResourcesSoundMp3(L"boss6"), true);
	SOUNDMANAGER->Play(L"boss6", 0.05f);

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

/*	PlayerHpUI* playerui = new PlayerHpUI;
	playerui->Init();
	playerui->SetHp(OBJECTMANAGER->GetPlayer()->GetHp());
	OBJECTMANAGER->AddObject(ObjectLayer::UI, playerui);

	ActiveItemUI* activeItemui = new ActiveItemUI;
	activeItemui->Init();
	OBJECTMANAGER->AddObject(ObjectLayer::UI, activeItemui);

	StarCountUI* starCountui = new StarCountUI;
	starCountui->Init();
	OBJECTMANAGER->AddObject(ObjectLayer::UI, starCountui);*/

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

	for (int i = 0; i < 20; ++i)
	{
		mImageDR[i] = 0;
		mImageAlpha[i] = 0.25f;
	}

	mOrder = 0;
	mImageCreateDelay = 0.5f;

	mFixDia = IMAGEMANAGER->FindImage(L"MapFixDia");
	mFixRect = IMAGEMANAGER->FindImage(L"MapFixRect");

	mBlockStart = 0;

	mCameraFix = true;

	mIsBossDead = false;
}

void Scene05::Release()
{
	SOUNDMANAGER->Stop(L"boss6");
}

void Scene05::Update()
{
	SOUNDMANAGER->Update();

	if (INPUT->GetKeyDown('P'))
		((Boss*)OBJECTMANAGER->FindObject("Boss"))->SetHp(0);

	if (mCameraFix) // 바닥 깨지는 이벤트 발생하는 내용에 이 if문 넣으면 될듯?
	{
		GameObject* player = (GameObject*)(OBJECTMANAGER->GetPlayer());
		if (player->GetX() >= mSceneSizeX / 2.f) // 지금은 맵 진입하면 고정카메라였다가 x축으로 중간 지나면 카메라 시점 플레이어로 바뀌도록 해놔서 이벤트 때 떨어지는 거 따라갈 수 있게 해둠
		{
			Camera* main = CAMERAMANAGER->GetMainCamera();
			main->SetMode(Camera::Mode::Follow);
			main->SetTarget(player);

			PlaceRect2();
		}
	}

	OBJECTMANAGER->Update();

	// 충돌
	AllCollision();

	// 이벤트 추가
	if (!mIsBossAppearanceEvent && OBJECTMANAGER->GetPlayer()->GetX() >= WINSIZEX / 2)
	{
		mIsBossAppearanceEvent = true;
		GAMEEVENTMANAGER->PushEvent(new IObjectStop(true));
		GAMEEVENTMANAGER->PushEvent(new IPlaySoundEffect(L"Attack1", L"Lubella/", 0.05f, 0.f));
		GAMEEVENTMANAGER->PushEvent(new IDelayEvent(3.f));
		GAMEEVENTMANAGER->PushEvent(new IPlaySoundEffect(L"Laugh1", L"Lubella/", 0.05f, 0.f));
		GAMEEVENTMANAGER->PushEvent(new IDelayEvent(1.f));
		GAMEEVENTMANAGER->PushEvent(new IMoveGameObject(OBJECTMANAGER->FindObject("Boss"), ((Boss*)OBJECTMANAGER->FindObject("Boss"))->GetX()
			, 1600 - ((Boss*)OBJECTMANAGER->FindObject("Boss"))->GetSizeY() / 3 - 50, 0.f, -500.f));
		GAMEEVENTMANAGER->PushEvent(new IPlaySoundEffect(L"Appear", L"Lubella/", 0.05f, 0.f));
		GAMEEVENTMANAGER->PushEvent(new IDelayEvent(0.5f));
		//GAMEEVENTMANAGER->PushEvent(new IPlaySoundEffect(L"Laugh1", L"Lubella/", 0.05f, 0.f));

		GAMEEVENTMANAGER->PushEvent(new IObjectStop(false));	// 보스 등장 이벤트 끝
	}

	if (!mIsBossDead && ((Boss*)OBJECTMANAGER->FindObject("Boss"))->GetHP() <= 0 && !((Boss*)OBJECTMANAGER->FindObject("Boss"))->GetEndEvent())
	{
		SOUNDMANAGER->Stop(L"boss6");
		((Boss*)OBJECTMANAGER->FindObject("Boss"))->SetEndEvent(true);

		GAMEEVENTMANAGER->PushEvent(new IDelayEvent(1.f));

		GAMEEVENTMANAGER->PushEvent(new IScriptEvent(L"Boss_Dialogue1"));
		GAMEEVENTMANAGER->PushEvent(new IDelayEvent(0.5f));
		GAMEEVENTMANAGER->PushEvent(new IScriptEvent(L"Boss_Dialogue2"));
		//GAMEEVENTMANAGER->PushEvent(new IDelayEvent(0.5f));

		GAMEEVENTMANAGER->PushEvent(new IEraseEvent(((Boss*)OBJECTMANAGER->FindObject("Boss"))->GetImage()
			, ((Boss*)OBJECTMANAGER->FindObject("Boss"))->GetBackImage(), 2.f, 0.07f));
	}

	GAMEEVENTMANAGER->Update();

	if (mIsBossAppearanceEvent )
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

	// {{ 맵 좌우 설치용
	mImageCreateDelay -= TIME->DeltaTime();

	if (mImageCreateDelay <= 0.f)
	{
		mImageCreateDelay = 0.5f;
		mImageDR[mOrder] = rand() % 2 + 1; // 1이면 다이아, 2면 렉트
		for (int i = 0; i < 24; ++i)
		{
			if (i / 12 == 0)
				mImageX[mOrder * 24 + i] = 5 + rand() % 61;
			else
				mImageX[mOrder * 24 + i] = WINSIZEX - 45 - rand() % 61;

			mImageY[mOrder * 24 + i] = 50 * (i % 12) + rand() % 31 + 830;

			mImageAlpha[mOrder] = 0.25f;
		}

		++mOrder;

		if (mOrder >= 20)
			mOrder = 0;
	}

	for (int i = 0; i < 20; ++i)
	{
		if (mImageDR[i])
			mImageAlpha[i] -= 0.05f * TIME->DeltaTime();

		if (mImageAlpha[i] < 0.f)
			mImageAlpha[i] = 0.f;
	}
	// 맵 좌우 설치용 }}

	// {{ 상황에 따른 맵 이동 제한
	GameObject* player = (GameObject*)(OBJECTMANAGER->GetPlayer());
	float x = player->GetX();
	if (mBlockStart == 0 && (int)x >= WINSIZEX / 2)
	{
		mBlockStart = 1;
		PlaceRect2();

		CAMERAMANAGER->GetMainCamera()->SetShakePower(10);
		CAMERAMANAGER->GetMainCamera()->SetShake(2.f);
	}
	// 상황에 따른 맵 이동 제한 }}
}

void Scene05::Render(HDC hdc)
{
	// 맵 이미지
	CAMERAMANAGER->GetMainCamera()->ScaleRender(hdc, mMapImage, 0, 0, mSceneSizeX, mSceneSizeY);

	// {{ 충돌 체크용 맵
//	vector<GameObject*> platformList = OBJECTMANAGER->GetObjectList(ObjectLayer::Platform);
//	vector<GameObject*>::iterator iter1 = platformList.begin();


//	for (; iter1 != platformList.end(); ++iter1)
//		CAMERAMANAGER->GetMainCamera()->RenderRectInCamera(hdc, (*iter1)->GetRect());
	// 충돌 체크용 맵 }}

	OBJECTMANAGER->Render(hdc);

	CAMERAMANAGER->GetMainCamera()->ScaleRender(hdc, mPlatformImage, 0, 604, mPlatformImage->GetWidth(), mPlatformImage->GetHeight());
	CAMERAMANAGER->GetMainCamera()->ScaleRender(hdc, mPlatformImage2, 0, 1460, mPlatformImage->GetWidth(), mPlatformImage->GetHeight());

	for (int i = 0; i < 20; ++i)
	{
		if (mImageDR[i])
		{
			for (int j = 0; j < 24; ++j)
			{
				if (mImageDR[i] == 1)
					CAMERAMANAGER->GetMainCamera()->AlphaRender(hdc, mFixDia, mImageX[i * 24 + j], mImageY[i * 24 + j], mImageAlpha[i]);
				else
					CAMERAMANAGER->GetMainCamera()->AlphaRender(hdc, mFixRect, mImageX[i * 24 + j], mImageY[i * 24 + j], mImageAlpha[i]);
			}
		}
	}

	OBJECTMANAGER->RenderUI(hdc);

	GAMEEVENTMANAGER->Render(hdc);
}

void Scene05::PlaceRect2()
{
	Platform* platform01 = new Platform();
	platform01->SetPlatform(-120, 0, 100, 1600, PlatformType::Normal);
	OBJECTMANAGER->AddObject(ObjectLayer::Platform, (GameObject*)platform01);

	Platform* platform02 = new Platform();
	platform02->SetPlatform(860, 0, 980, 1600, PlatformType::Normal);
	OBJECTMANAGER->AddObject(ObjectLayer::Platform, (GameObject*)platform02);
}
#include "pch.h"
#include "Scene04.h"
#include "Camera.h"
#include "Platform.h"
#include "Fennel.h"
#include "Player.h"
#include "BossHpUI.h"
#include "GameEvent.h"

void Scene04::Init()
{
	mMapImage = IMAGEMANAGER->FindImage(L"MapImage04");
	mSceneSizeX = mMapImage->GetWidth();
	mSceneSizeY = mMapImage->GetHeight();

	SOUNDMANAGER->Stop(L"cinder");
	SOUNDMANAGER->LoadFromFile(L"boss2", ResourcesSoundMp3(L"boss2"), true);
	SOUNDMANAGER->Play(L"boss2", 0.05f);

	PlaceRect();

	Camera* main = CAMERAMANAGER->GetMainCamera();
	main->SetMode(Camera::Mode::Follow);
	GameObject* player = (GameObject*)(OBJECTMANAGER->GetPlayer());
	main->SetTarget(player);

	if (mEntrance == 1)
	{
		player->SetX(50);
		player->SetY(732);
		main->SetX(480);
		main->SetY(540);
	}
	else if (mEntrance == 2)
	{
		player->SetX(1150);
		player->SetY(732);
		main->SetX(480);
		main->SetY(540);
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

	////페넬
	AddFennel(800, 775);
}

void Scene04::Release()
{
	SOUNDMANAGER->Stop(L"boss2");
}

void Scene04::Update()
{
	OBJECTMANAGER->Update();

	//충돌확인
	AllCollision();

	RECT temp1;
	vector<GameObject*> enemyList = OBJECTMANAGER->GetObjectList(ObjectLayer::Enemy);

	//페넬이 살아있으면
	if (enemyList.size() > 0)
	{
		//랙트 받아오고
		RECT thunder = ((Fennel*)enemyList[0])->GetThunderRect();
		RECT impact = ((Fennel*)enemyList[0])->GetImpactRect();
		RECT playerHitBox = (OBJECTMANAGER->GetPlayer()->GetHitBox());

		//페넬 번개, 플레이어 히트박스 충돌
		if (IntersectRect(&temp1, &playerHitBox, &thunder))
		{
			//플레이어 체력 깎기

			//방향알려줘야해
			Direction direction = COLLISIONMANAGER->CheckSide(&playerHitBox, &thunder);
			//플레이어 상태전환하고 무적시키는 함수
			OBJECTMANAGER->GetPlayer()->PlayerHurt(direction);
		}

		//페넬 임팩트, 플레이어 히트박스 충돌
		if (IntersectRect(&temp1, &playerHitBox, &impact))
		{
			//플레이어 체력 깎기

			//방향알려줘야해
			Direction direction = COLLISIONMANAGER->CheckSide(&playerHitBox, &impact);
			//플레이어 상태전환하고 무적시키는 함수
			OBJECTMANAGER->GetPlayer()->PlayerHurt(direction);
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
				mImageX[mOrder * 24 + i] = WINSIZEX - 45 + 240 - rand() % 61;

			mImageY[mOrder * 24 + i] = 50 * (i % 12) + rand() % 31 + 180;

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
	}

	vector<GameObject*> enemyList2 = OBJECTMANAGER->GetObjectList(ObjectLayer::Enemy);
	//vector<GameObject*>::iterator iter = enemyList2.begin();
	//int enemyHp = ((Enemy*)(*iter))->GetHP();
	if (mBlockStart == 1 && enemyList2.size() <= 0)//enemyHp <= 0)
	{
		mBlockStart = 2;
		RemoveRect3();
	}

	if (mBlockStart == 2)
	{
		if ((int)x >= mSceneSizeX)
			SCENEMANAGER->LoadScene(L"Scene05", 1);
	}
	// 상황에 따른 맵 이동 제한 }}

	//이벤트 추가
	//if (FennelIntro && OBJECTMANAGER->GetPlayer()->GetX() >= WINSIZEX / 2)
	//{
	//	FennelIntro = false;
	//	GAMEEVENTMANAGER->PushEvent(new IObjectStop(true));
	//	GAMEEVENTMANAGER->PushEvent(new IDelayEvent(3.f));
	//	Image* image = IMAGEMANAGER->FindImage(L"Fennelintro1");
	//	GAMEEVENTMANAGER->PushEvent(new IChangeImage(&image, L"Fennelintro1"));
	//	GAMEEVENTMANAGER->PushEvent(new IDelayEvent(1.f));
	//
	//	GAMEEVENTMANAGER->PushEvent(new IObjectStop(false));	// 보스 등장 이벤트 끝
	//}
	//
	//GAMEEVENTMANAGER->Update();
	//
	//if (FennelIntro)
	//{
	//	mChangeImageTime += TIME->DeltaTime();
	//
	//	if (mChangeImageTime >= 1.f)
	//	{
	//		mPlatformImage = IMAGEMANAGER->FindImage(L"platform2");
	//		OBJECTMANAGER->GetObjectList(ObjectLayer::Platform).front()->SetRect(WINSIZEX * 2, 604, WINSIZEX * 2 + 960, 643);
	//	}
	//
	//	if (OBJECTMANAGER->GetPlayer()->GetY() >= 1600 - WINSIZEY / 2)//1460 - OBJECTMANAGER->GetPlayer()->GetSizeY() / 2)
	//	{
	//		mCameraFix = false;
	//		CAMERAMANAGER->GetMainCamera()->SetMode(Camera::Mode::Fix);
	//		CAMERAMANAGER->GetMainCamera()->SetFix(WINSIZEX / 2, 1600 - WINSIZEY / 2 - 50);
	//
	//		if (!OBJECTMANAGER->FindObject("BossHpUI")->GetIsActive())
	//		{
	//			OBJECTMANAGER->FindObject("BossHpUI")->SetIsActive(true);
	//		}
	//	}
	//}

}

void Scene04::Render(HDC hdc)
{
	CAMERAMANAGER->GetMainCamera()->Render(hdc, mMapImage, 0, 0);

	OBJECTMANAGER->Render(hdc);

	for (int i = 0; i < 20; ++i)
	{
		if (mImageDR[i])
		{
			for (int j = 0; j < 24; ++j)
			{
				if (mImageDR[i] == 1)
				{
					if(mBlockStart == 2 && mImageX[i * 24 + j] > WINSIZEX / 2)
					{ }
					else if(mBlockStart >= 1)
						CAMERAMANAGER->GetMainCamera()->AlphaRender(hdc, mFixDia, mImageX[i * 24 + j], mImageY[i * 24 + j], mImageAlpha[i]);
				}
				else
				{
					if (mBlockStart == 2 && mImageX[i * 24 + j] > WINSIZEX / 2)
					{ }
					else if (mBlockStart >= 1)
						CAMERAMANAGER->GetMainCamera()->AlphaRender(hdc, mFixRect, mImageX[i * 24 + j], mImageY[i * 24 + j], mImageAlpha[i]);
				}
					
			}
		}
	}

	OBJECTMANAGER->RenderUI(hdc);

	//GAMEEVENTMANAGER->Render(hdc);

	//RECT rect;
	//vector<GameObject*> platformList = OBJECTMANAGER->GetObjectList(ObjectLayer::Platform);
	//vector<GameObject*>::iterator iter = platformList.begin();
	//for (; iter != platformList.end(); ++iter)
	//{
	//	rect = (*iter)->GetRect();
	//	CAMERAMANAGER->GetMainCamera()->RenderRectInCamera(hdc, rect);
	//}
}

void Scene04::PlaceRect()
{
	Platform* platform01 = new Platform();
	platform01->SetPlatform(-120, 780, 1320, 900, PlatformType::Normal);
	OBJECTMANAGER->AddObject(ObjectLayer::Platform, (GameObject*)platform01);
}

void Scene04::PlaceRect2()
{
	Platform* platform02 = new Platform();
	platform02->SetPlatform(-120, 0, 100, 900, PlatformType::Normal);
	OBJECTMANAGER->AddObject(ObjectLayer::Platform, (GameObject*)platform02);

	Platform* platform03 = new Platform();
	platform03->SetPlatform(1100, 0, 1320, 900, PlatformType::Normal);
	platform03->SetName("platform03");
	OBJECTMANAGER->AddObject(ObjectLayer::Platform, (GameObject*)platform03);
}

void Scene04::RemoveRect3()
{
	GameObject* platform03 = OBJECTMANAGER->FindObject("platform03");
	vector<GameObject*> platformList = OBJECTMANAGER->GetObjectList(ObjectLayer::Platform);

	for (int i = 0; i < platformList.size(); ++i)
	{
		if ((platformList[i] == platform03))
		{
			((Platform*)(platformList[i]))->Release();
			SafeDelete(platformList[i]);
			platformList.erase(platformList.begin() + i);
			--i;
		}
	}
	vector<GameObject*>* ListPtr = OBJECTMANAGER->GetObjectListPtr(ObjectLayer::Platform);
	ListPtr->resize(2);
	//OBJECTMANAGER->ShrinkToFitObjectList(ObjectLayer::Platform);
}
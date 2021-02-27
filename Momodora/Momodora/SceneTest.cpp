#include "pch.h"
#include "SceneTest.h"
#include "Camera.h"
#include "Platform.h"
#include "Ladder.h"

void SceneTest::Init()
{
	//IMAGEMANAGER->LoadFromFile(L"MapTest", Resources(L"Map/map2"), 1200, 900, false); // 메인으로 옮겨감

	// 맵 배경으로 깔고 그 사이즈 받아서 맵 사이즈 초기화 해야 함
	mMapTest = IMAGEMANAGER->FindImage(L"MapTest"); // 임시로 띄워놓은 것 // 씬 만들어지면 지울 것
	mSceneSizeX = 5000; // 좌우 100 정도 마진 주고 막아야 함
	mSceneSizeY = 3000;
	// 여기까지는 임시 데이터

	Platform* platform01 = new Platform();
	platform01->SetPlatform(0, 600, 5000, 650, PlatformType::Normal);
	OBJECTMANAGER->AddObject(ObjectLayer::Platform, (GameObject*)platform01);

	Platform* platform02 = new Platform();
	platform02->SetPlatform(600, 400, 800, 450, PlatformType::DownJump);
	OBJECTMANAGER->AddObject(ObjectLayer::Platform, (GameObject*)platform02);

	Ladder* ladder01 = new Ladder();
	ladder01->SetLadder(675, 450, 725, 600);
	OBJECTMANAGER->AddObject(ObjectLayer::Ladder, (GameObject*)ladder01);

	SOUNDMANAGER->Play(L"Boss", 0.5f); // BGM Play 세팅하면 Release에서 Stop도 세팅해야 함
	//SOUNDMANAGER->Play(L"boss1", 0.3f);

	for (int i = 0; i < 20; ++i)
	{
		mImageDR[i] = 0;
		mImageAlpha[i] = 0.25f;
	}

	mOrder = 0;
	mImageCreateDelay = 0.5f;

	// 보스 맵 좌우 설치용
	mFixDia = IMAGEMANAGER->FindImage(L"MapFixDia");
	mFixRect = IMAGEMANAGER->FindImage(L"MapFixRect");

	// 보스 맵 하단 설치용
	mCircle01 = IMAGEMANAGER->FindImage(L"FallCircle");
	mCircle02 = IMAGEMANAGER->FindImage(L"FallOneTwiceCircle");
	mCircle03 = IMAGEMANAGER->FindImage(L"FallTripleCircle");
	mCircle04 = IMAGEMANAGER->FindImage(L"FallFourCircle");
	mCircle05 = IMAGEMANAGER->FindImage(L"FallFiveCircle");

	for (int i = 0; i < 20; ++i)
	{
		mImageC[i] = 0;
		mImageCAlpha[i] = 0.25f;
	}

	mOrderC = 0;
	mImageCCreateDelay = 0.5f;

	mEarthQuakeDust = false;

	mAttacked = IMAGEMANAGER->FindImage(L"Attacked");
	mAttackedAlpha = 0.f;

	Camera* main = CAMERAMANAGER->GetMainCamera();
	//main->SetMode(Camera::Mode::Follow);
	//GameObject* player = (GameObject*)(OBJECTMANAGER->GetPlayer());
	//main->SetTarget(player);
	main->SetMode(Camera::Mode::Fix);
	main->SetFix(WINSIZEX / 2, WINSIZEY / 2);
}

void SceneTest::Release()
{
	SOUNDMANAGER->Stop(L"Boss"); // Bgm 반드시 Stop해야 함, 씬 전환 시에 Release 함수 호출하므로 Release 제일 상단에 기재할 것
}

void SceneTest::Update()
{
	if (INPUT->GetKeyDown('I'))
	{
		CAMERAMANAGER->GetMainCamera()->SetShakePower(10);
		CAMERAMANAGER->GetMainCamera()->SetShake(2.f);
	}

	if (INPUT->GetKeyDown('O'))
	{
		CAMERAMANAGER->GetMainCamera()->SetShakePower(5);
		CAMERAMANAGER->GetMainCamera()->SetShake(0.5f);
	}

	if (INPUT->GetKeyDown('P'))
	{
		CAMERAMANAGER->GetMainCamera()->SetShakePower(3);
		CAMERAMANAGER->GetMainCamera()->SetShake(0.2f);
	}

	// 피격
	if (INPUT->GetKeyDown('L'))
	{
		mAttackedAlpha = 0.5f;
	}

	if (INPUT->GetKeyDown('J'))
	{
		if (mEarthQuakeDust)
			mEarthQuakeDust = false;
		else
			mEarthQuakeDust = true;
	}

	// {{ 보스 맵 좌우 설치용
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

			mImageY[mOrder * 24 + i] = 50 * (i % 12) + rand() % 31;

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
	// 보스 맵 좌우 설치용 }}

	// {{ 보스 맵 하단 설치용
	if (mEarthQuakeDust)
	{
		mImageCCreateDelay -= TIME->DeltaTime();

		if (mImageCCreateDelay <= 0.f)
		{
			mImageCCreateDelay = 0.5f;
			mImageC[mOrderC] = rand() % 5 + 1; // 1부터 5까지
			for (int i = 0; i < 24; ++i)
			{
				mImageCX[mOrderC * 24 + i] = 30 + rand() % 856; // 901-45
				mImageCY[mOrderC * 24 + i] = 570 + rand() % 51;

				mImageCAlpha[mOrderC] = 0.25f;
			}

			++mOrderC;

			if (mOrderC >= 20)
				mOrderC = 0;
		}
	}

		for (int i = 0; i < 20; ++i)
		{
			if (mImageC[i])
				mImageCAlpha[i] -= 0.05f * TIME->DeltaTime();

			if (mImageCAlpha[i] < 0.f)
				mImageCAlpha[i] = 0.f;
		}
	//}
	// 보스 맵 하단 설치용 }}

	// 피격
	if (mAttackedAlpha)
	{
		mAttackedAlpha -= 4.f * TIME->DeltaTime();

		if (mAttackedAlpha <= 0.f)
			mAttackedAlpha = 0.f;
	}
}

void SceneTest::Render(HDC hdc)
{
	CAMERAMANAGER->GetMainCamera()->Render(hdc, mMapTest, 0, 0);

/*	vector<GameObject*> platformList = OBJECTMANAGER->GetObjectList(ObjectLayer::Platform);
	vector<GameObject*>::iterator iter1 = platformList.begin();
	for (; iter1 != platformList.end(); ++iter1)
		CAMERAMANAGER->GetMainCamera()->RenderRectInCamera(hdc, (*iter1)->GetRect());

	vector<GameObject*> ladderList = OBJECTMANAGER->GetObjectList(ObjectLayer::Ladder);
	vector<GameObject*>::iterator iter2 = ladderList.begin();
	for (; iter2 != ladderList.end(); ++iter2)
		CAMERAMANAGER->GetMainCamera()->RenderRectInCamera(hdc, (*iter2)->GetRect());*/

	// 보스 맵 좌우 설치용
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

	// 보스 맵 하단 설치용
	for (int i = 0; i < 20; ++i)
	{
		if (mImageC[i])
		{
			for (int j = 0; j < 24; ++j)
			{
				if (mImageC[i] == 1)
					CAMERAMANAGER->GetMainCamera()->AlphaRender(hdc, mCircle01, mImageCX[i * 24 + j], mImageCY[i * 24 + j], mImageCAlpha[i]);
				else if (mImageC[i] == 2)
					CAMERAMANAGER->GetMainCamera()->AlphaRender(hdc, mCircle02, mImageCX[i * 24 + j], mImageCY[i * 24 + j], mImageCAlpha[i]);
				else if (mImageC[i] == 3)
					CAMERAMANAGER->GetMainCamera()->AlphaRender(hdc, mCircle03, mImageCX[i * 24 + j], mImageCY[i * 24 + j], mImageCAlpha[i]);
				else if (mImageC[i] == 4)
					CAMERAMANAGER->GetMainCamera()->AlphaRender(hdc, mCircle04, mImageCX[i * 24 + j], mImageCY[i * 24 + j], mImageCAlpha[i]);
				else if (mImageC[i] == 5)
					CAMERAMANAGER->GetMainCamera()->AlphaRender(hdc, mCircle05, mImageCX[i * 24 + j], mImageCY[i * 24 + j], mImageCAlpha[i]);
			}
		}
	}

	if (mAttackedAlpha)
	{
		CAMERAMANAGER->GetMainCamera()->AlphaRender(hdc, mAttacked, 0, 0, mAttackedAlpha);
	}

	wstring str = L"Test씬 페이지";
	TextOut(hdc, WINSIZEX / 2, WINSIZEY / 2, str.c_str(), (int)str.length());
	wstring str2 = L"I: shakePower 10, shaketime 2.f";
	TextOut(hdc, WINSIZEX / 2, WINSIZEY / 2 + 25, str2.c_str(), (int)str2.length());
	wstring str3 = L"O: shakePower 5, shaketime 0.5f";
	TextOut(hdc, WINSIZEX / 2, WINSIZEY / 2 + 50, str3.c_str(), (int)str3.length());
	wstring str4 = L"P: shakePower 3, shaketime 0.2f";
	TextOut(hdc, WINSIZEX / 2, WINSIZEY / 2 + 75, str4.c_str(), (int)str4.length());
	wstring str5 = L"L: 피격 효과";
	TextOut(hdc, WINSIZEX / 2, WINSIZEY / 2 + 100, str5.c_str(), (int)str5.length());
	wstring str6 = L"J: 먼지 효과";
	TextOut(hdc, WINSIZEX / 2, WINSIZEY / 2 + 125, str6.c_str(), (int)str6.length());
}
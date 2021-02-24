#include "pch.h"
#include "SceneTest.h"
#include "Camera.h"
#include "Platform.h"
#include "Ladder.h"

void SceneTest::Init()
{
	//IMAGEMANAGER->LoadFromFile(L"MapTest", Resources(L"Map/map2"), 1200, 900, false); // 메인으로 옮겨감
	//IMAGEMANAGER->LoadFromFile(L"TempPlayer", Resources(L"tempPlayer"), 32, 32, true);

	mMapTest = IMAGEMANAGER->FindImage(L"MapTest"); // 임시로 띄워놓은 것 // 씬 만들어지면 지울 것

	Platform* platform01 = new Platform();
	platform01->SetPlatform(0, 600, 800, 650, PlatformType::Normal);
	OBJECTMANAGER->AddObject(ObjectLayer::Platform, (GameObject*)platform01);

	Platform* platform02 = new Platform();
	platform02->SetPlatform(600, 400, 800, 450, PlatformType::DownJump);
	OBJECTMANAGER->AddObject(ObjectLayer::Platform, (GameObject*)platform02);

	Ladder* ladder01 = new Ladder();
	ladder01->SetLadder(675, 450, 725, 600);
	OBJECTMANAGER->AddObject(ObjectLayer::Platform, (GameObject*)ladder01);

	SOUNDMANAGER->Play(L"Boss", 0.5f);
	//SOUNDMANAGER->Play(L"boss1", 0.3f);

	for (int i = 0; i < 100; ++i)
	{
		mRectEff[i] = IMAGEMANAGER->FindImage(L"FF");
		mAlpha[i] = 0.25f;
		mA[100] = false;
	}
	a = 0;
	createTime = 0.f;

	for (int i = 0; i < 10; ++i)
		crea.push_back(i);
}

void SceneTest::Release()
{
	//SafeDelete(mPlatform01);
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

	for (int i = 0; i < 100; ++i)
	{
		if (mA[i])
		{
			if (mAlpha[i] < 0.f)
				mAlpha[i] = 0.f;
			mAlpha[i] -= 0.1f * TIME->DeltaTime();
		}
	}

	createTime -= TIME->DeltaTime();

	int k = 0;
	//if (INPUT->GetKeyDown(VK_LBUTTON))
	if(createTime <= 0.f)
	{
		createTime = 0.5f;
		//createTime = 0.05f;

		if (a >= 100)
			return;
		//
		//while (true)
		//{
			k = rand() % 10;

			mA[a] = true;

			for(int i = 0; i < 10; ++i)
			mx[10 * a + i] = 300 + rand() % 40;
		//	my[10 * a + k] = 200 + 50 * k + rand() % 40;
		//
		//	vector<int>::iterator iter = crea.begin();
		//	for (; iter != crea.end(); ++iter)
		//		if ((*iter) == k)
		//		{
		//			crea.erase(iter);
		//			return;
		//		}
		//
		//	if (iter == crea.end())
		//		continue;
		//
		//	if (crea.begin() == crea.end())
		//	{
		//		++a;
		//
		//		for (int i = 0; i < 10; ++i)
		//			crea.push_back(i);
		//	}
		//}

		my[10 * a] = 200 + rand() % 40;
		my[10 * a + 1] = 250 + rand() % 40;
		my[10 * a + 2] = 300 + rand() % 40;
		my[10 * a + 3] = 350 + rand() % 40;
		my[10 * a + 4] = 400 + rand() % 40;
		my[10 * a + 5] = 450 + rand() % 40;
		my[10 * a + 6] = 500 + rand() % 40;
		my[10 * a + 7] = 550 + rand() % 40;
		my[10 * a + 8] = 600 + rand() % 40;
		my[10 * a + 9] = 650 + rand() % 40;
		++a;
		return;
	}
}

void SceneTest::Render(HDC hdc)
{
	CAMERAMANAGER->GetMainCamera()->Render(hdc, mMapTest, 0, 0);

	vector<GameObject*> platformList = OBJECTMANAGER->GetObjectList(ObjectLayer::Platform);
	vector<GameObject*>::iterator iter1 = platformList.begin();
	for (; iter1 != platformList.end(); ++iter1)
		CAMERAMANAGER->GetMainCamera()->RenderRectInCamera(hdc, (*iter1)->GetRect());

	vector<GameObject*> ladderList = OBJECTMANAGER->GetObjectList(ObjectLayer::Ladder);
	vector<GameObject*>::iterator iter2 = ladderList.begin();
	for (; iter2 != ladderList.end(); ++iter2)
		CAMERAMANAGER->GetMainCamera()->RenderRectInCamera(hdc, (*iter2)->GetRect());

	for(int i = 0; i < 100; ++i)
		if (mA[i])
		{
			CAMERAMANAGER->GetMainCamera()->AlphaRender(hdc, mRectEff[i], mx[10 * i], my[10 * i], mAlpha[i]);
			CAMERAMANAGER->GetMainCamera()->AlphaRender(hdc, mRectEff[i], mx[10 * i + 1], my[10 * i + 1], mAlpha[i]);
			CAMERAMANAGER->GetMainCamera()->AlphaRender(hdc, mRectEff[i], mx[10 * i + 2], my[10 * i + 2], mAlpha[i]);
			CAMERAMANAGER->GetMainCamera()->AlphaRender(hdc, mRectEff[i], mx[10 * i + 3], my[10 * i + 3], mAlpha[i]);
			CAMERAMANAGER->GetMainCamera()->AlphaRender(hdc, mRectEff[i], mx[10 * i + 4], my[10 * i + 4], mAlpha[i]);
			CAMERAMANAGER->GetMainCamera()->AlphaRender(hdc, mRectEff[i], mx[10 * i + 5], my[10 * i + 5], mAlpha[i]);
			CAMERAMANAGER->GetMainCamera()->AlphaRender(hdc, mRectEff[i], mx[10 * i + 6], my[10 * i + 6], mAlpha[i]);
			CAMERAMANAGER->GetMainCamera()->AlphaRender(hdc, mRectEff[i], mx[10 * i + 7], my[10 * i + 7], mAlpha[i]);
			CAMERAMANAGER->GetMainCamera()->AlphaRender(hdc, mRectEff[i], mx[10 * i + 8], my[10 * i + 8], mAlpha[i]);
			CAMERAMANAGER->GetMainCamera()->AlphaRender(hdc, mRectEff[i], mx[10 * i + 9], my[10 * i + 9], mAlpha[i]);
		}

	wstring str = L"Test씬 페이지";
	TextOut(hdc, WINSIZEX / 2, WINSIZEY / 2, str.c_str(), (int)str.length());
	wstring str2 = L"I: shakePower 10, shaketime 2.f";
	TextOut(hdc, WINSIZEX / 2, WINSIZEY / 2 + 25, str2.c_str(), (int)str2.length());
	wstring str3 = L"O: shakePower 5, shaketime 0.5f";
	TextOut(hdc, WINSIZEX / 2, WINSIZEY / 2 + 50, str3.c_str(), (int)str3.length());
	wstring str4 = L"P: shakePower 3, shaketime 0.2f";
	TextOut(hdc, WINSIZEX / 2, WINSIZEY / 2 + 75, str4.c_str(), (int)str4.length());
}
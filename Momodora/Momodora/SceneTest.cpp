#include "pch.h"
#include "SceneTest.h"
#include "Camera.h"
#include "Platform.h"
#include "Ladder.h"

void SceneTest::Init()
{
	//IMAGEMANAGER->LoadFromFile(L"MapTest", Resources(L"Map/map2"), 1200, 900, false); // �������� �Űܰ�
	//IMAGEMANAGER->LoadFromFile(L"TempPlayer", Resources(L"tempPlayer"), 32, 32, true);

	mMapTest = IMAGEMANAGER->FindImage(L"MapTest"); // �ӽ÷� ������� �� // �� ��������� ���� ��

	Platform* platform01 = new Platform();
	platform01->SetPlatform(0, 600, 800, 650, PlatformType::Normal);
	OBJECTMANAGER->AddObject(ObjectLayer::Platform, (GameObject*)platform01);

	Platform* platform02 = new Platform();
	platform02->SetPlatform(600, 400, 800, 450, PlatformType::DownJump);
	OBJECTMANAGER->AddObject(ObjectLayer::Platform, (GameObject*)platform02);

	Ladder* ladder01 = new Ladder();
	ladder01->SetLadder(675, 450, 725, 600);
	OBJECTMANAGER->AddObject(ObjectLayer::Platform, (GameObject*)ladder01);
}

void SceneTest::Release()
{
	//SafeDelete(mPlatform01);
}

void SceneTest::Update()
{
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

	wstring str = L"Test�� ������";
	TextOut(hdc, WINSIZEX / 2, WINSIZEY / 2, str.c_str(), (int)str.length());
}
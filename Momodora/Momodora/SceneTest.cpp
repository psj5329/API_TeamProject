#include "pch.h"
#include "SceneTest.h"
#include "Camera.h"
#include "Platform.h"

void SceneTest::Init()
{
	IMAGEMANAGER->LoadFromFile(L"MapTest", Resources(L"Map/map2"), 1200, 900, false);
	//IMAGEMANAGER->LoadFromFile(L"TempPlayer", Resources(L"tempPlayer"), 32, 32, true);

	mMapTest = IMAGEMANAGER->FindImage(L"MapTest"); // 임시로 띄워놓은 것 // 씬 만들어지면 지울 것

	mPlatform01 = new Platform();
	RECT rect01 = { 0, 600, 600, 650 };
	mPlatform01->SetRect(rect01);
	OBJECTMANAGER->AddObject(ObjectLayer::Platform, (GameObject*)mPlatform01);
}

void SceneTest::Release()
{
}

void SceneTest::Update()
{
}

void SceneTest::Render(HDC hdc)
{
	CAMERAMANAGER->GetMainCamera()->Render(hdc, mMapTest, 0, 0);

	CAMERAMANAGER->GetMainCamera()->RenderRectInCamera(hdc, mPlatform01->GetRect());

	wstring str = L"Test씬 페이지";
	TextOut(hdc, WINSIZEX / 2, WINSIZEY / 2, str.c_str(), (int)str.length());
}

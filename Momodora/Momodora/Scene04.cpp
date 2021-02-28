#include "pch.h"
#include "Scene04.h"
#include "Camera.h"
#include "Platform.h"

void Scene04::Init()
{
	mMapImage = IMAGEMANAGER->FindImage(L"MapImage04");
	mSceneSizeX = mMapImage->GetWidth();
	mSceneSizeY = mMapImage->GetHeight();

	PlaceRect();

	Camera* main = CAMERAMANAGER->GetMainCamera();
	main->SetMode(Camera::Mode::Follow);
	GameObject* player = (GameObject*)(OBJECTMANAGER->GetPlayer());
	main->SetTarget(player);

	// 플레이어가 서 있는 위치 고려해서 고정 카메라로 했다가 바꿔야 함
	if (mEntrance == 1)
	{
		player->SetX(200);
		player->SetY(400);
	}
	else if (mEntrance == 2)
	{
		player->SetX(700);
		player->SetY(400);
	}
}

void Scene04::Release()
{
}

void Scene04::Update()
{
	OBJECTMANAGER->Update();

	GameObject* player = (GameObject*)(OBJECTMANAGER->GetPlayer());
	float x = player->GetX();

	//if ((int)x <= 0)
	//	SCENEMANAGER->LoadScene(L"Scene03", 2); // 왼쪽으로 못 돌아가게 막을 예정?!
	if ((int)x >= mSceneSizeX)
		SCENEMANAGER->LoadScene(L"Scene05", 1);
}

void Scene04::Render(HDC hdc)
{
	CAMERAMANAGER->GetMainCamera()->Render(hdc, mMapImage, 0, 0);

	OBJECTMANAGER->Render(hdc);

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
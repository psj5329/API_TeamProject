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

	////페넬
	AddFennel(800, 775);
}

void Scene04::Release()
{
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


	GameObject* player = (GameObject*)(OBJECTMANAGER->GetPlayer());
	float x = player->GetX();

	//if ((int)x <= 0)
	//	SCENEMANAGER->LoadScene(L"Scene03", 2); // 왼쪽으로 못 돌아가게 막을 예정?!
	if ((int)x >= mSceneSizeX)
		//SCENEMANAGER->LoadScene(L"Scene05", 1);
		SCENEMANAGER->LoadScene(L"Scene09", 1);


}

void Scene04::Render(HDC hdc)
{
	CAMERAMANAGER->GetMainCamera()->Render(hdc, mMapImage, 0, 0);

	OBJECTMANAGER->Render(hdc);

	GAMEEVENTMANAGER->Render(hdc);

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
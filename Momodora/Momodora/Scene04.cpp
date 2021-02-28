#include "pch.h"
#include "Scene04.h"
#include "Camera.h"
#include "Platform.h"
#include "Fennel.h"
#include "Player.h"
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

	// �÷��̾ �� �ִ� ��ġ ����ؼ� ���� ī�޶�� �ߴٰ� �ٲ�� ��
	if (mEntrance == 1)
	{
		player->SetX(50);
		player->SetY(731);
		main->SetX(480);
		main->SetY(540);
	}
	else if (mEntrance == 2)
	{
		player->SetX(1150);
		player->SetY(731);
		main->SetX(480);
		main->SetY(540);
	}


	////���
	AddFennel(800, 775);
}

void Scene04::Release()
{
}

void Scene04::Update()
{
	OBJECTMANAGER->Update();

	//�浹Ȯ��
	AllCollision();
		
	RECT temp1;
	vector<GameObject*> enemyList = OBJECTMANAGER->GetObjectList(ObjectLayer::Enemy);
	//��Ʈ �޾ƿ���
	RECT thunder = ((Fennel*)enemyList[0])->GetThunderRect();
	RECT impact = ((Fennel*)enemyList[0])->GetImpactRect();
	RECT playerHitBox = (OBJECTMANAGER->GetPlayer()->GetHitBox());

	//��� ����, �÷��̾� ��Ʈ�ڽ� �浹
	if (IntersectRect(&temp1, &playerHitBox, &thunder))
	{
		//�÷��̾� ü�� ���

		//����˷������
		Direction direction = COLLISIONMANAGER->CheckSide(&playerHitBox, &thunder);
		//�÷��̾� ������ȯ�ϰ� ������Ű�� �Լ�
		OBJECTMANAGER->GetPlayer()->PlayerHurt(direction);
	}

	//��� ����Ʈ, �÷��̾� ��Ʈ�ڽ� �浹
	if (IntersectRect(&temp1, &playerHitBox, &impact))
	{
		//�÷��̾� ü�� ���

		//����˷������
		Direction direction = COLLISIONMANAGER->CheckSide(&playerHitBox, &impact);
		//�÷��̾� ������ȯ�ϰ� ������Ű�� �Լ�
		OBJECTMANAGER->GetPlayer()->PlayerHurt(direction);
	}


	GameObject* player = (GameObject*)(OBJECTMANAGER->GetPlayer());
	float x = player->GetX();

	//if ((int)x <= 0)
	//	SCENEMANAGER->LoadScene(L"Scene03", 2); // �������� �� ���ư��� ���� ����?!
	if ((int)x >= mSceneSizeX)
		//SCENEMANAGER->LoadScene(L"Scene05", 1);
		SCENEMANAGER->LoadScene(L"Scene09", 1);
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
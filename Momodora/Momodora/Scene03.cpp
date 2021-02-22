#include "pch.h"
#include "Scene03.h"
#include "Camera.h"

#include "Boss.h"

void Scene03::Init()
{
	// Boss
	IMAGEMANAGER->LoadFromFile(L"Boss_Head", Resources(L"Boss/Boss_Head"), 1020, 157, 5, 1, true);
	IMAGEMANAGER->LoadFromFile(L"Boss_Body", Resources(L"Boss/Boss_Body"), 115, 176, true);
	IMAGEMANAGER->LoadFromFile(L"Boss_BackHair", Resources(L"Boss/Boss_BackHair"), 200, 221, true);
	IMAGEMANAGER->LoadFromFile(L"Boss_Chest", Resources(L"Boss/Boss_Chest"), 101, 57, true);
	IMAGEMANAGER->LoadFromFile(L"Boss_Eyes", Resources(L"Boss/Boss_Eyes"), 61, 21, true);
	IMAGEMANAGER->LoadFromFile(L"Boss_Pupil", Resources(L"Boss/Boss_Pupil"), 49, 19, true);
	IMAGEMANAGER->LoadFromFile(L"Boss_LeftArm", Resources(L"Boss/Boss_LeftArm"), 41, 136, true);
	IMAGEMANAGER->LoadFromFile(L"Boss_RightArm", Resources(L"Boss/Boss_RightArm"), 41, 136, true);
	IMAGEMANAGER->LoadFromFile(L"Boss_LeftArm_Dead", Resources(L"Boss/Boss_LeftArm_Dead"), 108, 87, true);
	IMAGEMANAGER->LoadFromFile(L"Boss_LeftShoulder_Dead", Resources(L"Boss/Boss_LeftShoulder_Dead"), 39, 81, true);

	mBoss = new Boss;
	mBoss->Init();

}

void Scene03::Release()
{
}

void Scene03::Update()
{
	mBoss->Update();
}

void Scene03::Render(HDC hdc)
{
	mBoss->Render(hdc);
	//wstring str = L"æ¿3 ∆‰¿Ã¡ˆ";
	//TextOut(hdc, WINSIZEX / 2, WINSIZEY / 2, str.c_str(), (int)str.length());
}
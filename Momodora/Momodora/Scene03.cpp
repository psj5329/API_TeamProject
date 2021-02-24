#include "pch.h"
#include "Scene03.h"
#include "Camera.h"

#include "Boss.h"

void Scene03::Init()
{
	Boss* boss = new Boss;
	boss->Init();
	boss->SetObject();
	boss->SetAnimation();
	OBJECTMANAGER->AddObject(ObjectLayer::Boss, boss);
}

void Scene03::Release()
{
}

void Scene03::Update()
{
	//mBoss->Update();
	OBJECTMANAGER->Update();
}

void Scene03::Render(HDC hdc)
{
	OBJECTMANAGER->Render(hdc);
	//wstring str = L"æ¿3 ∆‰¿Ã¡ˆ";
	//TextOut(hdc, WINSIZEX / 2, WINSIZEY / 2, str.c_str(), (int)str.length());
}
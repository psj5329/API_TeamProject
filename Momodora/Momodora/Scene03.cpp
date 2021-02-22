#include "pch.h"
#include "Scene03.h"

void Scene03::Init()
{
}

void Scene03::Release()
{
}

void Scene03::Update()
{
}

void Scene03::Render(HDC hdc)
{
	wstring str = L"æ¿3 ∆‰¿Ã¡ˆ";
	TextOut(hdc, WINSIZEX / 2, WINSIZEY / 2, str.c_str(), (int)str.length());
}
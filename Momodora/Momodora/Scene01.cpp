#include "pch.h"
#include "Scene01.h"

void Scene01::Init()
{
}

void Scene01::Release()
{
}

void Scene01::Update()
{
}

void Scene01::Render(HDC hdc)
{
	wstring str = L"��1 ������";
	TextOut(hdc, WINSIZEX / 2, WINSIZEY / 2, str.c_str(), (int)str.length());
}
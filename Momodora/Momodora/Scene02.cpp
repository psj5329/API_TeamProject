#include "pch.h"
#include "Scene02.h"
#include "Camera.h"

void Scene02::Init()
{
}

void Scene02::Release()
{
}

void Scene02::Update()
{
}

void Scene02::Render(HDC hdc)
{
	wstring str = L"��2 ������";
	TextOut(hdc, WINSIZEX / 2, WINSIZEY / 2, str.c_str(), (int)str.length());
}
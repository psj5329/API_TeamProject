#include "pch.h"
#include "CameraManager.h"
#include "Camera.h"
_Singleton_NULL(CameraManager)

void CameraManager::Update()
{
	if (mMainCamera)
		mMainCamera->Update();
}
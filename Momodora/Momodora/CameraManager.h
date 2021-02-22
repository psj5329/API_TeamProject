#pragma once

class Camera;

class CameraManager
{
	_Singleton(CameraManager)

private:
	Camera* mMainCamera;

public:
	void Update();

	Camera* GetMainCamera()const { return mMainCamera; }
	inline void SetMainCamera(Camera* mainCamera) { mMainCamera = mainCamera; }
};

#define CAMERAMANAGER CameraManager::GetInstance()
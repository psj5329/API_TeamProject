#include "pch.h"
#include "MainGame.h"

//#include "SceneManager.h"
#include "Image.h"
#include "Camera.h"

#include "Scene01.h"
#include "Scene02.h"
#include "Scene03.h"

void MainGame::Init()
{
	SetTimer(_hWnd, 1, 10, NULL);

	//SceneManager::GetInstance()->ChangeScene(SceneManager::Scene_00);

	mBackBuffer = new Image();
	mBackBuffer->CreateEmpty(WINSIZEX, WINSIZEY);

	SCENEMANAGER->AddScene(L"Scene01", new Scene01());
	SCENEMANAGER->AddScene(L"Scene02", new Scene02());
	SCENEMANAGER->AddScene(L"Scene03", new Scene03());
	SCENEMANAGER->LoadScene(L"Scene01");

	IMAGEMANAGER->LoadFromFile(L"Background", Resources(L"temp"), 1501, 1000, false);
	IMAGEMANAGER->LoadFromFile(L"TempPlayer", Resources(L"tempPlayer"), 32, 32, true);

	mBackground = IMAGEMANAGER->FindImage(L"Background"); // �ӽ÷� ������� �� // �� ��������� ���� ��

	//mTempPlayer // ���� �÷��̾ ��� ���� ī�޶��

	Camera* main = new Camera();
	main->Init();
	main->SetMoveSpeed(5.f);
	//main->SetMode(Camera::Mode::Follow); // ���� �÷��̾ ��� ���� ī�޶��
	main->SetMode(Camera::Mode::Free);

	CAMERAMANAGER->SetMainCamera(main);
}

void MainGame::Release()
{
	KillTimer(_hWnd, 1);

	SafeDelete(mBackBuffer);

	D2DRenderer::ReleaseInstance();

	SoundManager::ReleaseInstance();
	SceneManager::ReleaseInstance();
	ObjectManager::ReleaseInstance();
	ImageManager::ReleaseInstance();

	Camera* camera = CAMERAMANAGER->GetMainCamera();
	SafeDelete(camera);
	CameraManager::ReleaseInstance();

	Input::ReleaseInstance();
	Random::ReleaseInstance();
	Time::ReleaseInstance();

	//SceneManager::ReleaseInstance();
}

void MainGame::Update()
{
	//SceneManager::GetInstance()->Update();
	CAMERAMANAGER->Update();
}

void MainGame::Render(HDC hdc)
{
	HDC backDC = mBackBuffer->GetHDC();
	PatBlt(backDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//D2DRENDERER->BeginRender(D2D1::ColorF::Black);

	// { �׸��� ����

	//ID2D1RenderTarget* renderTarget = D2DRENDERER->GetRenderTarget();

	//mBackground->Render(backDC, 0, 0, (mBackground->GetWidth() - WINSIZEX) / 2, (mBackground->GetHeight() - WINSIZEY) / 2, WINSIZEX, WINSIZEY); // �ӽ÷� ������� �� // �� ��������� ���� ��
	//mBackground->Render(backDC, 0, 0); // �ӽ÷� ������� �� // �� ��������� ���� ��
	CAMERAMANAGER->GetMainCamera()->Render(backDC, mBackground, 0, 0);
	//CAMERAMANAGER->GetMainCamera()->Render(hdc, mBackground, 0, 0);

	//mTempPlayer

	// Ÿ�� ���� ����
	float worldTime = TIME->GetWorldTime();
	float deltaTime = TIME->DeltaTime();
	ULONG fps = TIME->GetmFrameRate();
	wstring strWorldTime = L"WorldTime : " + to_wstring(worldTime);
	wstring strDeltaTime = L"DeltaTime : " + to_wstring(deltaTime);
	wstring strFPS = L"FPS : " + to_wstring(fps);

	TextOut(backDC, 10, 10, strWorldTime.c_str(), (int)strWorldTime.length());
	TextOut(backDC, 10, 25, strDeltaTime.c_str(), (int)strDeltaTime.length());
	TextOut(backDC, 10, 40, strFPS.c_str(), (int)strFPS.length());
	// Ÿ�� ���� ��

	//SceneManager::GetInstance()->Render(backDC);

	// �׸��� �� }

	mBackBuffer->Render(hdc, 0, 0);
	//D2DRENDERER->EndRender();
}
#include "pch.h"
#include "MainGame.h"

#include "Image.h"
#include "Camera.h"

#include "LoadingScene.h"
#include "Scene01.h"
#include "Scene02.h"
#include "Scene03.h"
#include "SceneTest.h"

void MainGame::Init()
{
	SetTimer(_hWnd, 1, 10, NULL);

	//SceneManager::GetInstance()->ChangeScene(SceneManager::Scene_00);

	mBackBuffer = new Image();
	mBackBuffer->CreateEmpty(WINSIZEX, WINSIZEY);

	LoadingScene* loadScene = new LoadingScene();
	SCENEMANAGER->AddScene(L"LoadingScene", loadScene);
	SCENEMANAGER->AddScene(L"Scene01", new Scene01());
	SCENEMANAGER->AddScene(L"Scene02", new Scene02());
	SCENEMANAGER->AddScene(L"Scene03", new Scene03());
	SCENEMANAGER->AddScene(L"SceneTest", new SceneTest());

	SCENEMANAGER->LoadScene(L"LoadingScene");

	IMAGEMANAGER->LoadFromFile(L"Background", Resources(L"temp"), 1501, 1000, false);
	IMAGEMANAGER->LoadFromFile(L"TempPlayer", Resources(L"tempPlayer"), 32, 32, true);

	loadScene->AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"MapTest", Resources(L"Map/map2"), 1200, 900, false); });

	mBackground = IMAGEMANAGER->FindImage(L"Background"); // 임시로 띄워놓은 것 // 씬 만들어지면 지울 것

	//mTempPlayer // 지금 플레이어가 없어서 프리 카메라로

	Camera* main = new Camera();
	main->Init();
	main->SetMoveSpeed(5.f);
	//main->SetMode(Camera::Mode::Follow); // 지금 플레이어가 없어서 프리 카메라로
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
	CollisionManager::ReleaseInstance();

	Camera* camera = CAMERAMANAGER->GetMainCamera();
	SafeDelete(camera);
	CameraManager::ReleaseInstance();

	Input::ReleaseInstance();
	Random::ReleaseInstance();
	Time::ReleaseInstance();
}

void MainGame::Update()
{
	SCENEMANAGER->Update();

	CAMERAMANAGER->Update();

	if (INPUT->GetKeyDown('1'))
	{
		if (SCENEMANAGER->GetCurrentSceneName() != L"Scene01")
			SCENEMANAGER->LoadScene(L"Scene01");
	}
	else if (INPUT->GetKeyDown('2'))
	{
		if (SCENEMANAGER->GetCurrentSceneName() != L"Scene02")
			SCENEMANAGER->LoadScene(L"Scene02");
	}
	else if (INPUT->GetKeyDown('3'))
	{
		if (SCENEMANAGER->GetCurrentSceneName() != L"Scene03")
			SCENEMANAGER->LoadScene(L"Scene03");
	}
	else if (INPUT->GetKeyDown('0')) // 테스트 끝나면 지우기
	{
		if (SCENEMANAGER->GetCurrentSceneName() != L"SceneTest")
			SCENEMANAGER->LoadScene(L"SceneTest");
	}
}

void MainGame::Render(HDC hdc)
{
	HDC backDC = mBackBuffer->GetHDC();
	PatBlt(backDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//D2DRENDERER->BeginRender(D2D1::ColorF::Black);

	// { 그리기 시작

	//ID2D1RenderTarget* renderTarget = D2DRENDERER->GetRenderTarget();

	//mBackground->Render(backDC, 0, 0, (mBackground->GetWidth() - WINSIZEX) / 2, (mBackground->GetHeight() - WINSIZEY) / 2, WINSIZEX, WINSIZEY); // 임시로 띄워놓은 것 // 씬 만들어지면 지울 것
	//mBackground->Render(backDC, 0, 0); // 임시로 띄워놓은 것 // 씬 만들어지면 지울 것
	CAMERAMANAGER->GetMainCamera()->Render(backDC, mBackground, 0, 0);
	//CAMERAMANAGER->GetMainCamera()->Render(hdc, mBackground, 0, 0);
	//mTempPlayer

	//SceneManager::GetInstance()->Render(backDC);

	SCENEMANAGER->Render(backDC);


	wstring str = SCENEMANAGER->GetCurrentSceneName();
	if (str == L"LoadingScene" && ((LoadingScene*)(SCENEMANAGER->GetCurrentScene()))->GetIsEndLoading())
	{
		wstring strLoad = L"로딩 끝";
		TextOut(backDC, 300, 300, strLoad.c_str(), (int)strLoad.length());
	}

	RenderTimeText(backDC);

	// 그리기 끝 }

	mBackBuffer->Render(hdc, 0, 0);
	//D2DRENDERER->EndRender();
}

void MainGame::RenderTimeText(HDC hdc)
{
	// 타임 복붙 시작
	float worldTime = TIME->GetWorldTime();
	float deltaTime = TIME->DeltaTime();
	ULONG fps = TIME->GetmFrameRate();
	wstring strWorldTime = L"WorldTime : " + to_wstring(worldTime);
	wstring strDeltaTime = L"DeltaTime : " + to_wstring(deltaTime);
	wstring strFPS = L"FPS : " + to_wstring(fps);

	TextOut(hdc, 10, 10, strWorldTime.c_str(), (int)strWorldTime.length());
	TextOut(hdc, 10, 25, strDeltaTime.c_str(), (int)strDeltaTime.length());
	TextOut(hdc, 10, 40, strFPS.c_str(), (int)strFPS.length());
	// 타임 복붙 끝
}
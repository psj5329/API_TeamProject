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

	mBackBuffer = new Image();
	mBackBuffer->CreateEmpty(WINSIZEX, WINSIZEY);

	MakeScene();

	IMAGEMANAGER->LoadFromFile(L"Background", Resources(L"temp"), 1501, 1000, false);
	IMAGEMANAGER->LoadFromFile(L"TempPlayer", Resources(L"tempPlayer"), 32, 32, true);

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

	if (SCENEMANAGER->GetCurrentSceneName() == L"LoadingScene")
	{
		LoadingScene* currentScene = (LoadingScene*)SCENEMANAGER->GetCurrentScene();
		if (!(currentScene->GetIsEndLoading()))
			return;
	}

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

void MainGame::MakeScene()
{
	LoadingScene* loadScene = new LoadingScene();

	LoadImageResource(loadScene);
	LoadSoundResource(loadScene);

	SCENEMANAGER->AddScene(L"LoadingScene", loadScene);
	SCENEMANAGER->AddScene(L"Scene01", new Scene01());
	SCENEMANAGER->AddScene(L"Scene02", new Scene02());
	SCENEMANAGER->AddScene(L"Scene03", new Scene03());
	SCENEMANAGER->AddScene(L"SceneTest", new SceneTest());

	SCENEMANAGER->LoadScene(L"LoadingScene");
}

void MainGame::LoadImageResource(LoadingScene* scene)
{
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"MapTest", Resources(L"Map/map2"), 1200, 900, false); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"FF", Resources(L"ffffff"), 16, 16, false); });

	// Player
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"Idle", Resources(L"Player/idle"), 294, 96, 6, 2, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"Run", Resources(L"Player/run"), 490, 96, 10, 2, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"Turn", Resources(L"/Player/turn"), 147, 96, 3, 2, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"Jump", Resources(L"/Player/jump"), 147, 96, 3, 2, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"Fall", Resources(L"/Player/fall"), 245, 96, 5, 2, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"Crouch", Resources(L"/Player/crouch"), 196, 96, 4, 2, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"Rise", Resources(L"/Player/rise"), 98, 96, 2, 2, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"Roll", Resources(L"/Player/roll"), 392, 96, 8, 2, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"LadderUp", Resources(L"/Player/ladderup"), 204, 48, 6, 1, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"LadderDown", Resources(L"/Player/ladderdown"), 105, 43, 3, 1, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"LadderEnter", Resources(L"/Player/ladderenter"), 390, 128, 6, 2, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"LadderLeave", Resources(L"/Player/ladderleave"), 294, 160, 6, 2, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"Bow", Resources(L"/Player/bow"), 294, 96, 6, 2, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"AirBow", Resources(L"/Player/airbow"), 294, 96, 6, 2, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"CrouchBow", Resources(L"/Player/crouchbow"), 294, 104, 6, 2, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"Arrow", Resources(L"/Player/arrow"), 32, 64, 1, 2, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"Attack1", Resources(L"/Player/attack1"), 343, 96, 7, 2, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"Attack2", Resources(L"/Player/attack2"), 343, 96, 7, 2, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"Attack3", Resources(L"/Player/attack3"), 539, 96, 11, 2, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"AirAttack", Resources(L"/Player/airattack"), 343, 96, 7, 2, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"Leaf1", Resources(L"/Player/leaf1"), 679, 96, 7, 2, true); }); //이펙트 이미지 아직 안씀
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"Leaf2", Resources(L"/Player/leaf2"), 679, 96, 7, 2, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"Leaf3", Resources(L"/Player/leaf3"), 1066, 96, 11, 2, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"AirLeaf", Resources(L"/Player/airleaf"), 582, 112, 6, 2, true); });

	// Enemy
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"Imp", Resources(L"Imp"), 320, 384, 10, 12, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"Monkey", Resources(L"Monkey"), 720, 288, 9, 6, true); });

	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"Witchcatch", Resources(L"Enemy/Witchcatch"), 490, 192, 5, 2, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"Witchdeath", Resources(L"Enemy/Witchdeath"), 528, 128, 8, 2, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"Witchdeath2", Resources(L"Enemy/Witchdeath2"), 528, 128, 8, 2, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"Witchhurt", Resources(L"Enemy/Witchhurt"), 66, 128, 1, 2, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"Witchhurt2", Resources(L"Enemy/Witchhurt2"), 66, 128, 1, 2, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"Witchidle", Resources(L"Enemy/Witchidle"), 330, 128, 5, 2, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"Witchidle2", Resources(L"Enemy/Witchidle2"), 330, 128, 5, 2, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"Witchthrow", Resources(L"Enemy/Witchthrow"), 594, 128, 9, 2, true); });

	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"Fennelatk1", Resources(L"Fennel/Fennelatk1"), 2714, 156, 23, 2, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"Fennelatk2", Resources(L"Fennel/Fennelatk2"), 1416, 156, 12, 2, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"Fennelbackflip", Resources(L"Fennel/Fennelbackflip"), 1534, 156, 13, 2, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"Fennelbuff", Resources(L"Fennel/Fennelbuff"), 1770, 156, 15, 2, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"Fenneldash", Resources(L"Fennel/Fenneldash"), 118, 156, 1, 2, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"Fenneldeath", Resources(L"Fennel/Fenneldeath"), 1652, 156, 14, 2, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"Fennelhurt", Resources(L"Fennel/Fennelhurt"), 236, 156, 2, 2, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"Fennelidle", Resources(L"Fennel/Fennelidle"), 590, 156, 5, 2, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"Fennelimpact", Resources(L"Fennel/Fennelimpact"), 2064, 255, 8, 1, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"Fennelintro1", Resources(L"Fennel/Fennelintro1"), 2280, 78, 19, 1, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"Fennelintro2", Resources(L"Fennel/Fennelintro2"), 960, 78, 8, 1, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"Fennelintro3", Resources(L"Fennel/Fennelintro3"), 1680, 78, 14, 1, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"Fennelintro4", Resources(L"Fennel/Fennelintro4"), 360, 78, 3, 1, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"Fenneljump", Resources(L"Fennel/Fenneljump"), 826, 156, 7, 2, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"Fenneljumpready", Resources(L"Fennel/Fenneljumpready"), 590, 156, 5, 2, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"Fennelplunge", Resources(L"Fennel/Fennelplunge"), 1534, 156, 13, 2, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"Fennelthunder", Resources(L"Fennel/Fennelthunder"), 2596, 156, 22, 2, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"Thunder", Resources(L"Fennel/thunder"), 210, 175, 3, 1, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"Fenneleffect", Resources(L"Fennel/Fenneleffect"), 40, 8, 4, 1, true); });

	// Enemy Projectile

	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"Bomb", Resources(L"Bomb"), 64, 32, 4, 2, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"Fire", Resources(L"Explosion"), 560, 62, 8, 1, true); });

	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"Dagger", Resources(L"Dagger"), 16, 32, 1, 2, true); });

	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"Staff", Resources(L"Enemy/Witchstaff"), 256, 64, 4, 1, true); });

	// Boss
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"Boss_Head", Resources(L"Boss/Boss_Head"), 1020, 157, 5, 1, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"Boss_Body", Resources(L"Boss/Boss_Body"), 115, 176, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"Boss_BackHair", Resources(L"Boss/Boss_BackHair"), 200, 221, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"Boss_Chest", Resources(L"Boss/Boss_Chest"), 101, 57, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"Boss_Eyes", Resources(L"Boss/Boss_Eyes"), 61, 21, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"Boss_Pupil", Resources(L"Boss/Boss_Pupil"), 49, 19, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"Boss_LeftArm", Resources(L"Boss/Boss_LeftArm"), 41, 136, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"Boss_RightArm", Resources(L"Boss/Boss_RightArm"), 41, 136, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"Boss_LeftArm_Dead", Resources(L"Boss/Boss_LeftArm_Dead"), 108, 87, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"Boss_LeftShoulder_Dead", Resources(L"Boss/Boss_LeftShoulder_Dead"), 39, 81, true); });

	// Boss Bullet
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"BossBullet1", Resources(L"Boss/BossBullet1"), 32, 32, true); });
}

void MainGame::LoadSoundResource(LoadingScene * scene)
{
	scene->AddLoadFunc([]() { SOUNDMANAGER->LoadFromFile(L"Boss", ResourcesSoundOggx(L"boss"), false); });
	scene->AddLoadFunc([]() { SOUNDMANAGER->LoadFromFile(L"Boss1", ResourcesSoundMp3(L"boss"), false); });
}
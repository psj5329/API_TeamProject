﻿#include "pch.h"
#include "MainGame.h"
#include "Image.h"
#include "Camera.h"
#include "LoadingScene.h"
#include "Scene01.h"
#include "Scene02.h"
#include "Scene03.h"
#include "Scene04.h"
#include "Scene05.h"

void MainGame::Init()
{
	SetTimer(_hWnd, 1, 10, NULL);

	mBackBuffer = new Image();
	mBackBuffer->CreateEmpty(WINSIZEX, WINSIZEY);

	MakeScene();

	Camera* main = new Camera();
	main->Init();
	main->SetMoveSpeed(5.f);
	main->SetMode(Camera::Mode::Fix);
	main->SetFixX(480);
	main->SetFixY(360);

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
	INPUT->Update();

	SCENEMANAGER->Update();

	CAMERAMANAGER->Update();

	if (SCENEMANAGER->GetCurrentSceneName() == L"LoadingScene")
	{
		LoadingScene* currentScene = (LoadingScene*)SCENEMANAGER->GetCurrentScene();
		if (!(currentScene->GetIsEndLoading()))
			return;
	}

	if (INPUT->GetKeyDown('2'))
	{
		if (SCENEMANAGER->GetCurrentSceneName() != L"Scene02")
			SCENEMANAGER->LoadScene(L"Scene02");
	}
	else if (INPUT->GetKeyDown('3'))
	{
		if (SCENEMANAGER->GetCurrentSceneName() != L"Scene03")
			SCENEMANAGER->LoadScene(L"Scene03");
	}
	else if (INPUT->GetKeyDown('4'))
	{
		if (SCENEMANAGER->GetCurrentSceneName() != L"Scene04")
			SCENEMANAGER->LoadScene(L"Scene04");
	}
	else if (INPUT->GetKeyDown('5'))
	{
		if (SCENEMANAGER->GetCurrentSceneName() != L"Scene05")
			SCENEMANAGER->LoadScene(L"Scene05");
	}

	if (INPUT->GetKeyDown('6'))
	{
		Camera* main = CAMERAMANAGER->GetMainCamera();
		if (main->GetMode() == Camera::Mode::Follow)
			main->SetMode(Camera::Mode::Fix);
		else if (main->GetMode() == Camera::Mode::Fix)
			main->SetMode(Camera::Mode::Free);
		else
		{
			main->SetMode(Camera::Mode::Follow);
			GameObject* player99 = (GameObject*)(OBJECTMANAGER->GetPlayer());
			main->SetTarget(player99);
		}
	}
}

void MainGame::Render(HDC hdc)
{
	HDC backDC = mBackBuffer->GetHDC();
	PatBlt(backDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);

	HBRUSH newBrush = CreateSolidBrush(RGB(0, 0, 0));
	HBRUSH oldBrush = (HBRUSH)SelectObject(backDC, newBrush);
	Rectangle(backDC, 0, 0, 960, 720);
	SelectObject(backDC, oldBrush);
	DeleteObject(newBrush);

	SCENEMANAGER->Render(backDC);

	//RenderDebugText(backDC);

	mBackBuffer->Render(hdc, 0, 0);
}

void MainGame::RenderDebugText(HDC hdc)
{
	float worldTime = TIME->GetWorldTime();
	float deltaTime = TIME->DeltaTime();
	ULONG fps = TIME->GetmFrameRate();
	wstring strWorldTime = L"WorldTime : " + to_wstring(worldTime);
	wstring strDeltaTime = L"DeltaTime : " + to_wstring(deltaTime);
	wstring strFPS = L"FPS : " + to_wstring(fps);

	TextOut(hdc, 700, 10, strWorldTime.c_str(), (int)strWorldTime.length());
	TextOut(hdc, 700, 25, strDeltaTime.c_str(), (int)strDeltaTime.length());
	TextOut(hdc, 700, 40, strFPS.c_str(), (int)strFPS.length());

	Camera* main = CAMERAMANAGER->GetMainCamera();
	wstring strCam = L"";
	if (main->GetMode() == Camera::Mode::Follow)
		strCam = L"팔로우 카메라(모드변경:6)";
	else if (main->GetMode() == Camera::Mode::Fix)
		strCam = L"고정 카메라(모드변경:6)";
	else
		strCam = L"프리 카메라(모드변경:6)";
	TextOut(hdc, 700, 55, strCam.c_str(), (int)strCam.length());

	bool tempRight = CAMERAMANAGER->GetMainCamera()->GetRight();
	wstring strRight = L"";
	if (tempRight)
		strRight = L"오른쪽";
	else
		strRight = L"왼쪽";
	TextOut(hdc, 700, 70, strRight.c_str(), (int)strRight.length());

	int x = CAMERAMANAGER->GetMainCamera()->GetX();
	int y = CAMERAMANAGER->GetMainCamera()->GetY();
	wstring strLoad5 = L"카메라x,y: " + to_wstring(x) + L", " + to_wstring(y);
	TextOut(hdc, 700, 100, strLoad5.c_str(), (int)strLoad5.length());
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
	SCENEMANAGER->AddScene(L"Scene04", new Scene04());
	SCENEMANAGER->AddScene(L"Scene05", new Scene05());

	SCENEMANAGER->LoadScene(L"LoadingScene");
}

void MainGame::LoadImageResource(LoadingScene* scene)
{
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"MapFixRect", Resources(L"MapFixRect"), 32, 32, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"MapFixDia", Resources(L"MapFixDia"), 45, 45, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"FallCircle", Resources(L"FallCircle"), 45, 45, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"FallOneTwiceCircle", Resources(L"FallOneTwiceCircle"), 45, 45, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"FallTripleCircle", Resources(L"FallTripleCircle"), 45, 45, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"FallFourCircle", Resources(L"FallFourCircle"), 45, 45, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"FallFiveCircle", Resources(L"FallFiveCircle"), 45, 45, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"Attacked", Resources(L"Attacked"), 960, 720, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"Background_Boss", Resources(L"map/Background_Boss"), 960, 1600, true); }); // 3번신
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"platform1", Resources(L"map/platform1"), 960, 39, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"platform2", Resources(L"map/platform2"), 960, 93, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"platform3", Resources(L"map/platform3"), 960, 140, true); });

	// Scene
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"MapImage01", ResourcesBackground(L"Background1"), 1200, 900, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"MapImage02", ResourcesBackground(L"Background2"), 2400, 900, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"MapImage03", ResourcesBackground(L"Background3"), 2400, 900, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"MapImage04", ResourcesBackground(L"Background4"), 1200, 900, true); });

	// Player
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"Idle", Resources(L"Player/idle"), 294, 96, 6, 2, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"Run", Resources(L"Player/run"), 490, 96, 10, 2, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"Brake", Resources(L"Player/brake"), 343, 96, 7, 2, true); });
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

	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"LandSoft", Resources(L"/Player/landsoft"), 196, 96, 4, 2, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"LandHard", Resources(L"/Player/landhard"), 539, 96, 11, 2, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"Hurt", Resources(L"/Player/hurt"), 49, 96, 1, 2, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"Death", Resources(L"/Player/death"), 1200, 88, 24, 2, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"UseItem", Resources(L"/Player/useitem"), 539, 96, 11, 2, true); });

	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"Attack1", ResourcesPlayer(L"Attack01"), 336, 96, 7, 2, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"Attack2", ResourcesPlayer(L"Attack02"), 336, 96, 7, 2, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"Attack3", ResourcesPlayer(L"Attack03"), 528, 96, 11, 2, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"AirAttack", ResourcesPlayer(L"AirAttack"), 336, 96, 7, 2, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"Leaf1", ResourcesPlayer(L"Leaf01"), 672, 96, 7, 2, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"Leaf2", ResourcesPlayer(L"Leaf02"), 672, 96, 7, 2, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"Leaf3", ResourcesPlayer(L"Leaf03"), 864, 96, 9, 2, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"AirLeaf", ResourcesPlayer(L"AirLeaf"), 576, 112, 6, 2, true); });

	// Enemy
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"Imp", Resources(L"Imp"), 320, 384, 10, 12, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"ShieldImp", Resources(L"ShieldImp"), 256, 256, 8, 8, true); });
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
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"FloorEffect", Resources(L"FloorEffect"), 569, 59, 7, 1, true); });

	// Enemy Projectile
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"Bomb", Resources(L"Bomb"), 64, 32, 4, 2, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"Fire", Resources(L"Explosion"), 560, 62, 8, 1, true); });

	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"Dagger", Resources(L"Dagger"), 16, 32, 1, 2, true); });

	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"Staff", Resources(L"Enemy/Witchstaff"), 256, 64, 4, 1, true); });

	// Boss
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"Boss", Resources(L"Boss/Boss"), 210, 320, 5, 1, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"Boss_back", Resources(L"Boss/Boss_back"), 210, 320, 5, 1, true); });

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

	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"Boss_Head_back", Resources(L"Boss/Boss_Head_back"), 1020, 157, 5, 1, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"Boss_Body_back", Resources(L"Boss/Boss_Body_back"), 115, 176, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"Boss_BackHair_back", Resources(L"Boss/Boss_BackHair_back"), 200, 221, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"Boss_Chest_back", Resources(L"Boss/Boss_Chest_back"), 101, 57, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"Boss_Eyes_back", Resources(L"Boss/Boss_Eyes_back"), 61, 21, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"Boss_Pupil_back", Resources(L"Boss/Boss_Pupil_back"), 49, 19, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"Boss_LeftArm_back", Resources(L"Boss/Boss_LeftArm_back"), 41, 136, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"Boss_RightArm_back", Resources(L"Boss/Boss_RightArm_back"), 41, 136, true); });

	// Boss Bullet
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"BossBullet1", Resources(L"Boss/BossBullet1"), 32, 32, true); });

	// Item
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"Star", Resources(L"Star"), 22, 22, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"Potion", Resources(L"Potion"), 36, 18, 2, 1, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"Magnet", Resources(L"Magnet"), 128, 128, 1, 1, true); });

	// Script
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"Boss_Dialogue1", Resources(L"Boss/Boss_Dialogue1"), 210, 50, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"Boss_Dialogue2", Resources(L"Boss/Boss_Dialogue2"), 210, 100, true); });

	// UI
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"Boss_Name", Resources(L"UI/Boss_Name"), 280, 40, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"Boss_Hp", Resources(L"UI/Boss_Hp"), 970, 65, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"Boss_HpBar", Resources(L"UI/Boss_HpBar"), 960, 45, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"Boss_HpLess", Resources(L"UI/Boss_HpLess"), 10, 45, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"Player_Hp", Resources(L"UI/Player_Hp"), 290, 40, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"Player_HpBar", Resources(L"UI/Player_HpBar"), 275, 30, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"Player_HpLess", Resources(L"UI/Player_HpLess"), 10, 30, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"Item_UI", Resources(L"UI/Item_UI"), 100, 100, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"Flower_UI", Resources(L"UI/Flower_UI"), 78, 78, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"Star_UI", Resources(L"UI/Star_UI"), 46, 46, true); });
	scene->AddLoadFunc([]() { IMAGEMANAGER->LoadFromFile(L"Hit", Resources(L"Hit"), 360, 110, 4, 1, true); });

	for (int i = 0; i < 10; ++i)
	{
		wstring num = L"Number" + to_wstring(i);
		scene->AddLoadFunc([num]() { IMAGEMANAGER->LoadFromFile(num, Resources(L"Number/" + num), 23, 30, true); });
	}
}

void MainGame::LoadSoundResource(LoadingScene * scene)
{
	scene->AddLoadFunc([]() { SOUNDMANAGER->LoadFromFile(L"Boss", ResourcesSoundOggx(L"boss"), false); });
	scene->AddLoadFunc([]() { SOUNDMANAGER->LoadFromFile(L"Boss1", ResourcesSoundMp3(L"boss"), false); });

	// 플레이어
	scene->AddLoadFunc([]() { SOUNDMANAGER->LoadFromFile(L"PAttack1", ResourcesSoundWav(L"Player/Attack1"), false); });
	scene->AddLoadFunc([]() { SOUNDMANAGER->LoadFromFile(L"PAttack2", ResourcesSoundWav(L"Player/Attack2"), false); });
	scene->AddLoadFunc([]() { SOUNDMANAGER->LoadFromFile(L"PAttack3", ResourcesSoundWav(L"Player/Attack3"), false); });
	scene->AddLoadFunc([]() { SOUNDMANAGER->LoadFromFile(L"Arrow", ResourcesSoundWav(L"Player/Arrow"), false); });
	scene->AddLoadFunc([]() { SOUNDMANAGER->LoadFromFile(L"Death", ResourcesSoundWav(L"Player/Death"), false); });
	scene->AddLoadFunc([]() { SOUNDMANAGER->LoadFromFile(L"Hurt", ResourcesSoundWav(L"Player/Hurt"), false); });
	
	// 루벨라
	scene->AddLoadFunc([]() { SOUNDMANAGER->LoadFromFile(L"Appear", ResourcesSoundMp3(L"Lubella/Appear"), false); });
	scene->AddLoadFunc([]() { SOUNDMANAGER->LoadFromFile(L"Attack1", ResourcesSoundMp3(L"Lubella/Attack1"), false); });
	scene->AddLoadFunc([]() { SOUNDMANAGER->LoadFromFile(L"Attack2", ResourcesSoundMp3(L"Lubella/Attack2"), false); });
	scene->AddLoadFunc([]() { SOUNDMANAGER->LoadFromFile(L"Dive", ResourcesSoundMp3(L"Lubella/Dive"), false); });
	scene->AddLoadFunc([]() { SOUNDMANAGER->LoadFromFile(L"Explosion", ResourcesSoundMp3(L"Lubella/Explosion"), false); });
	scene->AddLoadFunc([]() { SOUNDMANAGER->LoadFromFile(L"Explosion_loop", ResourcesSoundMp3(L"Lubella/Explosion"), true); });
	scene->AddLoadFunc([]() { SOUNDMANAGER->LoadFromFile(L"Laugh1", ResourcesSoundMp3(L"Lubella/Laugh1"), false); });
	scene->AddLoadFunc([]() { SOUNDMANAGER->LoadFromFile(L"Laugh2", ResourcesSoundMp3(L"Lubella/Laugh2"), false); });

	// 펜넬
	scene->AddLoadFunc([]() { SOUNDMANAGER->LoadFromFile(L"FennelAtk", ResourcesSoundMp3(L"FennelAttack"), false); });
	scene->AddLoadFunc([]() { SOUNDMANAGER->LoadFromFile(L"FennelAtk2", ResourcesSoundMp3(L"FennelAttack2"), false); });
	scene->AddLoadFunc([]() { SOUNDMANAGER->LoadFromFile(L"FennelAtk3", ResourcesSoundMp3(L"FennelAttack3"), false); });
	scene->AddLoadFunc([]() { SOUNDMANAGER->LoadFromFile(L"FennelThunder", ResourcesSoundMp3(L"FennelThunder2"), false); });

	// 에너미
	scene->AddLoadFunc([]() { SOUNDMANAGER->LoadFromFile(L"BombExplosion", ResourcesSoundMp3(L"Explosion"), false); });
	scene->AddLoadFunc([]() { SOUNDMANAGER->LoadFromFile(L"Imp2", ResourcesSoundMp3(L"Imp2"), false); });
	scene->AddLoadFunc([]() { SOUNDMANAGER->LoadFromFile(L"ImpDeath", ResourcesSoundMp3(L"ImpDeath"), false); });
	scene->AddLoadFunc([]() { SOUNDMANAGER->LoadFromFile(L"MonkeyAttack", ResourcesSoundMp3(L"MonkeyAttack"), false); });
	scene->AddLoadFunc([]() { SOUNDMANAGER->LoadFromFile(L"Leaf", ResourcesSoundMp3(L"Leaf"), false); });
	scene->AddLoadFunc([]() { SOUNDMANAGER->LoadFromFile(L"Leaf2", ResourcesSoundMp3(L"Leaf2"), false); });
	scene->AddLoadFunc([]() { SOUNDMANAGER->LoadFromFile(L"Leaf3", ResourcesSoundMp3(L"Leaf3"), false); });
}
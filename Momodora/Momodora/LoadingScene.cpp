#include "pch.h"
#include "LoadingScene.h"
#include "Player.h"
#include "Camera.h"

void LoadingScene::AddLoadFunc(const function<void(void)>& func)
{
	mLoadList.push_back(func);
}

void LoadingScene::Init()
{
	mLoadIndex = 0;
	mIsEndLoading = false;

	IMAGEMANAGER->LoadFromFile(L"Outer", ResourcesLoading(L"OuterBox"), 954, 78, false);
	IMAGEMANAGER->LoadFromFile(L"Inner", ResourcesLoading(L"InnerFilter"), 948, 72, true);
	IMAGEMANAGER->LoadFromFile(L"LoadingBackground", ResourcesLoading(L"Background"), 960, 720, false);

	mOuter = IMAGEMANAGER->FindImage(L"Outer");
	mInner = IMAGEMANAGER->FindImage(L"Inner");
	mMapImage = IMAGEMANAGER->FindImage(L"LoadingBackground");

	mBoxAlpha = 0.1f;
	mAlphaUp = true;
}

void LoadingScene::Release()
{
}

void LoadingScene::Update()
{
	if (mIsEndLoading)
	{
		if (INPUT->GetKeyDown(VK_SPACE))
		{
			if (SCENEMANAGER->GetCurrentSceneName() != L"Scene01")
				SCENEMANAGER->LoadScene(L"Scene01", 0);
		}
	}

	if (mAlphaUp)
	{
		mBoxAlpha += 0.2f * TIME->DeltaTime();
		if (mBoxAlpha >= 0.3f)
		{
			mBoxAlpha = 0.3f;
			mAlphaUp = false;
		}
	}
	else
	{
		mBoxAlpha -= 0.2f * TIME->DeltaTime();
		if (mBoxAlpha <= 0.1f)
		{
			mBoxAlpha = 0.1f;
			mAlphaUp = true;
		}
	}

	if (mLoadIndex >= mLoadList.size())
	{
		mIsEndLoading = true;

		if (mIsEndLoading)
		{
			vector<GameObject*> playerLayer = OBJECTMANAGER->GetObjectList(ObjectLayer::Player);
			if (playerLayer.size() == 0)
			{
				Player* player = new Player();
				player->Init();
				OBJECTMANAGER->AddObject(ObjectLayer::Player, player);
			}
		}

		return;
	}

	function<void(void)> func = mLoadList[mLoadIndex];
	func();
	++mLoadIndex;
}

void LoadingScene::Render(HDC hdc)
{
	//CAMERAMANAGER->GetMainCamera()->ScaleRender(hdc, mMapImage, 0, 0, WINSIZEX, WINSIZEY);
	CAMERAMANAGER->GetMainCamera()->Render(hdc, mMapImage, 0, 0);// , WINSIZEX, WINSIZEY);
	CAMERAMANAGER->GetMainCamera()->Render(hdc, mOuter, 3, 639);//321
	CAMERAMANAGER->GetMainCamera()->AlphaRender(hdc, mInner, 6, 642, 0, 0, (mInner->GetWidth()) * mLoadIndex / (int)mLoadList.size(), mInner->GetHeight(), mBoxAlpha);
	if (mIsEndLoading)
	{
		wstring str = L"로딩이 완료되었습니다. Space Bar를 누르십시오.";
		TextOut(hdc, 300, 670, str.c_str(), (int)str.length());
	}
}
#include "pch.h"
#include "LoadingScene.h"
#include "Player.h"

void LoadingScene::AddLoadFunc(const function<void(void)>& func)
{
	mLoadList.push_back(func);
}

void LoadingScene::Init()
{
	mLoadIndex = 0;
	mIsEndLoading = false;
}

void LoadingScene::Release()
{
}

void LoadingScene::Update()
{
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
}
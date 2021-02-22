#include "pch.h"
#include "SceneManager.h"
#include "Scene.h"
_Singleton_NULL(SceneManager)

SceneManager::SceneManager()
	: mCurrentScene(nullptr)
{
}

SceneManager::~SceneManager()
{
	SceneIter iter = mSceneList.begin();
	for (; iter != mSceneList.end(); ++iter)
	{
		iter->second->Release();
		SafeDelete(iter->second);
	}
}

void SceneManager::Update()
{
	if (mCurrentScene != nullptr)
		mCurrentScene->Update();
}

void SceneManager::Render(HDC hdc)
{
	if (mCurrentScene != nullptr)
		mCurrentScene->Render(hdc);
}

void SceneManager::AddScene(const wstring& sceneName, Scene* scene)
{
	SceneIter iter = mSceneList.find(sceneName);
	if (iter != mSceneList.end())
		return;

	mSceneList.insert(make_pair(sceneName, scene));
}

void SceneManager::LoadScene(const wstring& sceneName)
{
	SceneIter iter = mSceneList.find(sceneName);
	if (iter == mSceneList.end())
		return;

	if (mCurrentScene == iter->second)
		return;

	Scene* targetScene = iter->second;

	if (mCurrentScene)
		mCurrentScene->Release();

	targetScene->Init();

	mCurrentScene = targetScene;
}

wstring SceneManager::GetCurrentSceneName()
{
	wstring result = L"";

	SceneIter iter = mSceneList.begin();
	for (; iter != mSceneList.end(); ++iter)
		if (mCurrentScene == iter->second)
			result = iter->first;

	return result;
}
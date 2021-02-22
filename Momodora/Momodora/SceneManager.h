#pragma once

class Scene;

class SceneManager
{
	_Singleton(SceneManager)

private:
	map<wstring, Scene*> mSceneList;
	Scene* mCurrentScene;
	typedef map<wstring, Scene*>::iterator SceneIter;

public:
	SceneManager();
	~SceneManager();

	void Update();
	void Render(HDC hdc);

	void AddScene(const wstring& sceneName, Scene* scene);
	void LoadScene(const wstring& sceneName);
};

#define SCENEMANAGER SceneManager::GetInstance()
#pragma once

class Image;
class LoadingScene;
class Boss;

class MainGame
{
private:
	Image* mBackBuffer;

public:
	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);

public:
	void RenderDebugText(HDC hdc);

	void MakeScene();
	void LoadImageResource(LoadingScene* scene);
	void LoadSoundResource(LoadingScene* scene);

public:
	LRESULT MainProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};
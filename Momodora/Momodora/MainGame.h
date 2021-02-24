#pragma once

class Image;
class LoadingScene;
class Boss;

class MainGame
{
	Image* mBackBuffer;

	Boss* mBoss;

private:
	Image* mBackground; // 임시로 띄워놓은 것 // 씬 만들어지면 지울 것

	Image* mTempPlayer; // 임시로 띄워놓은 것

public:
	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);

public:
	void RenderTimeText(HDC hdc);

	void MakeScene();
	void LoadImageResource(LoadingScene* scene);
	void LoadSoundResource(LoadingScene* scene);

public:
	LRESULT MainProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};
#pragma once

class Image;
class LoadingScene;
class Boss;

class MainGame
{
	Image* mBackBuffer;

	Boss* mBoss;

private:
	Image* mBackground; // �ӽ÷� ������� �� // �� ��������� ���� ��

	Image* mTempPlayer; // �ӽ÷� ������� ��

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
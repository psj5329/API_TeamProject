#pragma once

class Image;

class MainGame
{
	Image* mBackBuffer;

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

public:
	LRESULT MainProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};
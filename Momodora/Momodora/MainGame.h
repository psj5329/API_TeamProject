#pragma once

class Image;

class MainGame
{
	Image* mBackBuffer;

private:
	Image* mBackground; // 임시로 띄워놓은 것 // 씬 만들어지면 지울 것

	Image* mTempPlayer; // 임시로 띄워놓은 것

public:
	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	LRESULT MainProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};
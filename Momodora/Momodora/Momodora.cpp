#include "pch.h"
#include "Momodora.h"
#include "MainGame.h"

HINSTANCE _hInstance;
HWND _hWnd;

POINT _mousePosition;

MainGame* _mainGame = NULL;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	_hInstance = hInstance;

	wstring* _className = new wstring();
	*_className = L"Momodora";

	WNDCLASSEXW wndClass;

	wndClass.cbSize = sizeof(WNDCLASSEX);

	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = (WNDPROC)WndProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = hInstance;
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = (*_className).c_str();
	wndClass.hIconSm = LoadIcon(wndClass.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	RegisterClassExW(&wndClass);

	_hWnd = CreateWindowW((*_className).c_str(), (*_className).c_str(), WS_OVERLAPPEDWINDOW,
		WINSTARTX, WINSTARTY, WINSIZEX, WINSIZEY, nullptr, nullptr, hInstance, nullptr);

	RECT windowRect;
	windowRect.left = 0;
	windowRect.top = 0;
	windowRect.right = WINSIZEX;
	windowRect.bottom = WINSIZEY;

	AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, false);

	SetWindowPos(_hWnd, NULL, WINSTARTX, WINSTARTY, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top,
		SWP_NOZORDER | SWP_NOMOVE);

	ShowWindow(_hWnd, nCmdShow);

	MSG msg;

#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc();
#endif

	//복붙 한 줄 추가
	HDC hdc = GetDC(_hWnd);

	_mainGame = new MainGame();
	_mainGame->Init();

	//복붙 한 줄 추가
	TIME->Start();

	// 여기부터 유찬 내용 주석 시작
/*	// 기본 메시지 루프입니다:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}*/  // 여기부터 유찬 내용 주석 끝
	// 여기부터 복붙시작
	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			TIME->Update();
			SOUNDMANAGER->Update();
			_mainGame->Update();
			_mainGame->Render(hdc);
		}
	} // 여기부터 복붙끝

	_mainGame->Release();
	delete _mainGame;
	_mainGame = NULL;

	delete _className;
	_className = NULL;

#ifdef _DEBUG
	_CrtDumpMemoryLeaks();
#endif

	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (_mainGame != NULL)
		return _mainGame->MainProc(hWnd, message, wParam, lParam);

	return DefWindowProc(hWnd, message, wParam, lParam);
}
#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <string>
#include <vector>
#include <map>
#include <queue> // 뀨

using namespace std;

#ifdef _WIN64
#pragma comment(lib, "../Libraries/lib/fmodex64_vc")
#else
#pragma comment(lib, "../Libraries/lib/fmodex_vc")
#endif

#include "../Libraries/inc/fmod.hpp"

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "WindowsCodecs.lib")

#include <D2D1.h>
#include <d2d1helper.h>
#include <d2d1.h>
#include <dwrite.h>
#include <wincodec.h>

#include <functional>

#include "DefineHeader.h"
#include "Figure.h"
#include "Input.h"
#include "Random.h"
#include "Time.h"
#include "Math.h"
#include "Vector2.h"

#include "CameraManager.h"
#include "CollisionManager.h"
#include "ImageManager.h"
#include "ObjectManager.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "D2DRenderer.h"
#include "GameEventManager.h"

extern HINSTANCE _hInstance;
extern HWND _hWnd;
extern POINT _mousePosition;
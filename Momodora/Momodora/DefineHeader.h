#pragma once
#define WINSTARTX 50
#define WINSTARTY 50
#define WINSIZEX 960
#define WINSIZEY 720

//#define DEBUG

#define SafeDelete(p)\
{\
	if (p)\
	{\
		delete (p);\
		(p) = NULL;\
	}\
}

#define Singleton(ClassName)\
public:\
	static ClassName* GetInstance()\
	{\
		static ClassName instance;\
		return &instance;\
	}

#define _Singleton(ClassName)\
static ClassName* _instance;\
public:\
	static ClassName* GetInstance()\
	{\
		if (_instance == NULL)\
			_instance = new ClassName();\
		return _instance;\
	}\
	static void ReleaseInstance()\
	{\
		if (_instance != NULL)\
		{\
			delete _instance;\
			_instance = NULL;\
		}\
	}

#define _Singleton_NULL(ClassName)\
ClassName* ClassName::_instance = NULL;

#define Resources(Path) (wstring(L"../Resources/").append(Path).append(L".bmp"))
#define ResourcesLoading(Path) (wstring(L"../Resources/Loading/").append(Path).append(L".bmp"))
#define ResourcesBackground(Path) (wstring(L"../Resources/SceneBackground/").append(Path).append(L".bmp"))
#define ResourcesUI(Path) (wstring(L"../Resources/UI/").append(Path).append(L".bmp"))
#define ResourcesPlayer(Path) (wstring(L"../Resources/Player/").append(Path).append(L".bmp"))

#define ResourcesSoundMp3(Path) (wstring(L"../Resources/Sound/").append(Path).append(L".mp3"))
#define ResourcesSoundOggx(Path) (wstring(L"../Resources/Sound/").append(Path).append(L".oggx"))
#include "pch.h"
#include "Input.h"
_Singleton_NULL(Input)

Input::Input()
{
	ZeroMemory(mKeyDownList, sizeof(bool) * KEYMAX);
	ZeroMemory(mKeyUpList, sizeof(bool) * KEYMAX);
}

bool Input::GetKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		if (mKeyDownList[key] == false)
		{
			mKeyDownList[key] = true;
			return true;
		}
	}
	else
		mKeyDownList[key] = false;

	return false;
}

bool Input::GetKeyUp(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
		mKeyUpList[key] = true;
	else
	{
		if (mKeyUpList[key] == true)
		{
			mKeyUpList[key] = false;
			return true;
		}
	}

	return false;
}

bool Input::GetKey(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
		return true;
	return false;
}

bool Input::GetToggleKey(int key)
{
	if (GetAsyncKeyState(key) & 0x0001)
		return true;
	return false;
}
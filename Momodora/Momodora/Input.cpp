#include "pch.h"
#include "Input.h"
_Singleton_NULL(Input)

Input::Input()
{
	mPrevKey.reset();
	mCurrentKey.reset();
	//ZeroMemory(mKeyDownList, sizeof(bool) * KEYMAX);
	//ZeroMemory(mKeyUpList, sizeof(bool) * KEYMAX);
}

void Input::Update()
{
}

bool Input::GetKeyDown(const int& key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		if (!mPrevKey[key])
		{
			mCurrentKey.set(key, true);
			return true;
		}
	}
	else
		mCurrentKey.set(key, false);

	return false;
}

bool Input::GetKeyUp(const int& key)
{
	if (GetAsyncKeyState(key) & 0x8000)
		mCurrentKey.set(key, true);
	else
	{
		if (mPrevKey[key])
		{
			mCurrentKey.set(key,false);
			return true;
		}
	}

	return false;
}

bool Input::GetKey(const int& key)
{
	if (GetAsyncKeyState(key) & 0x8000)
		return true;
	return false;
}

bool Input::GetToggleKey(const int& key)
{
	if (GetAsyncKeyState(key) & 0x0001)
		return true;
	return false;
}
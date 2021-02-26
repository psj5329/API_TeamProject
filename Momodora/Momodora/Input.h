#pragma once
#define KEYMAX 256
#include <bitset>

class Input
{
	_Singleton(Input)

private:
	//bool mKeyDownList[KEYMAX];
	//bool mKeyUpList[KEYMAX];
	bitset<KEYMAX> mPrevKey;
	bitset<KEYMAX> mCurrentKey;

public:
	Input();

	void Update();

	bool GetKeyDown(const int& key);
	bool GetKeyUp(const int& key);
	bool GetKey(const int& key);
	bool GetToggleKey(const int& key);
};

#define INPUT Input::GetInstance()
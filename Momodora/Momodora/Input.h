#pragma once
#define KEYMAX 256
//#include <bitset>

class Input
{
	_Singleton(Input)

private:
	bool mKeyDownList[KEYMAX];
	bool mKeyUpList[KEYMAX];
	//bitset<KEYMAX> mPrevKey;
	//bitset<KEYMAX> mCurrentKey;

public:
	Input();

	bool GetKeyDown(int key);
	bool GetKeyUp(int key);
	bool GetKey(int key);
	bool GetToggleKey(int key);
};

#define INPUT Input::GetInstance()
#include "pch.h"
#include "GameEventManager.h"

#include "GameEvent.h"
#include <queue>
_Singleton_NULL(GameEventManager)

GameEventManager::GameEventManager()
{
}

GameEventManager::~GameEventManager()
{
	RemoveAllEvent();
}

void GameEventManager::RemoveAllEvent()
{
	for (int i = 0; i < mEventQueue.size(); ++i)
		SafeDelete(mEventQueue.front());
		//mEventQueue.pop();
}

void GameEventManager::Update()
{
	if (mEventQueue.size() == 0)
		return;

	bool isEnd = mEventQueue.front()->Update();
	if (isEnd == true)
	{
		//SafeDelete(mEventQueue[0]);
		//mEventQueue.erase(mEventQueue.begin());
		mEventQueue.pop();

		if (mEventQueue.size() != 0)
		{
			mEventQueue.front()->Start();
		}
	}
}

void GameEventManager::Render(HDC hdc)
{
	if (mEventQueue.size() == 0)
		return;

	mEventQueue.front()->Render(hdc);
}

void GameEventManager::PushEvent(IEvent * event)
{
	if (mEventQueue.size() == 0)
	{
		event->Start();
	}
	mEventQueue.push(event);
}
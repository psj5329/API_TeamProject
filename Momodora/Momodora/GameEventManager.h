#pragma once

class IEvent;
class GameEventManager
{
	_Singleton(GameEventManager)
private:
	//얘 queue라는 자료구조 공부해서 queue로 바꿔오기
	queue<IEvent*> mEventQueue;
public:
	GameEventManager();
	~GameEventManager();

	void RemoveAllEvent();
	void Update();
	void Render(HDC hdc);

	void PushEvent(class IEvent* event);
};

#define GAMEEVENTMANAGER GameEventManager::GetInstance()
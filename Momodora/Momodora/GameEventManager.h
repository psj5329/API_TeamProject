#pragma once

class IEvent;
class GameEventManager
{
	_Singleton(GameEventManager)
private:
	//�� queue��� �ڷᱸ�� �����ؼ� queue�� �ٲ����
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
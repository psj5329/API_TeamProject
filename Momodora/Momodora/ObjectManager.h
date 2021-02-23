#pragma once

enum class ObjectLayer : int
{
	Background = 0,
	Boss,
	Frontground, // 보스를 가릴 수 있는 오브젝트
	Platform,
	Ladder,
	Player,
	Enemy,
	PlayerProjectile, // 플레이어 투사체
	EnemyProjectile, // 적 투사체, 지팡이, 중보 번개
	Effect,
	UI,
	End
};

class GameObject;
class Player;

class ObjectManager
{
	_Singleton(ObjectManager)

private:
	map<ObjectLayer, vector<GameObject*>> mObjectList;
	typedef map<ObjectLayer, vector<GameObject*>>::iterator ObjectIter;

public:
	ObjectManager();

	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	void AddObject(ObjectLayer layer, GameObject* object);
	GameObject* FindObject(const string& name);
	GameObject* FindObject(ObjectLayer layer, const string& name);
	vector<GameObject*> FindObjects(const string& name);
	vector<GameObject*> FindObjects(ObjectLayer layer, const string& name);

	void RemoveObjects(ObjectLayer layer);
	void RemoveObjectsInScene();

	vector<GameObject*> GetObjectList(ObjectLayer layer) { return mObjectList[layer]; }
	Player* GetPlayer();
};

#define OBJECTMANAGER ObjectManager::GetInstance()
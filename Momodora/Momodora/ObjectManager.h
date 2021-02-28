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
	PlayerArrow,
	PlayerLeaf,
	EnemyDagger,
	EnemyBomb,
	EnemyStaff,
	BossBullet,
	//EnemyProjectile, // 중보 번개???는 어디에?
	Item, // 맵에서 획득 가능한 아이템
	Effect,
	BossUI,
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

	void RenderUI(HDC hdc);

	void AddObject(ObjectLayer layer, GameObject* object);
	GameObject* FindObject(const string& name);
	GameObject* FindObject(ObjectLayer layer, const string& name);
	vector<GameObject*> FindObjects(const string& name);
	vector<GameObject*> FindObjects(ObjectLayer layer, const string& name);

	void RemoveObjects(ObjectLayer layer);
	void RemoveObjectsInScene();

	vector<GameObject*> GetObjectList(ObjectLayer layer) { return mObjectList[layer]; }
	vector<GameObject*>* GetObjectListPtr(ObjectLayer layer) { return &mObjectList[layer]; }
	void ShrinkToFitObjectList(ObjectLayer layer);
	Player* GetPlayer();
};

#define OBJECTMANAGER ObjectManager::GetInstance()
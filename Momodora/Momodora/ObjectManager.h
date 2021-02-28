#pragma once

enum class ObjectLayer : int
{
	Background = 0,
	Boss,
	Frontground, // ������ ���� �� �ִ� ������Ʈ
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
	//EnemyProjectile, // �ߺ� ����???�� ���?
	Item, // �ʿ��� ȹ�� ������ ������
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
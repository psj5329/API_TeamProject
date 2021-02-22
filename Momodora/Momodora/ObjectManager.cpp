#include "pch.h"
#include "ObjectManager.h"
#include "GameObject.h"
_Singleton_NULL(ObjectManager)

ObjectManager::ObjectManager()
{
	for (int i = 0; i < (int)ObjectLayer::End; ++i)
	{
		vector<GameObject*> emptyVector;
		mObjectList.insert(make_pair((ObjectLayer)i, emptyVector));
	}
}

void ObjectManager::Init()
{
	ObjectIter iter = mObjectList.begin();
	for (; iter != mObjectList.end(); ++iter)
		for (int i = 0; i < iter->second.size(); ++i)
			iter->second[i]->Init();
}

void ObjectManager::Release()
{
	ObjectIter iter = mObjectList.begin();
	for (; iter != mObjectList.end(); ++iter)
		for (int i = 0; i < iter->second.size(); ++i)
		{
			iter->second[i]->Release();
			SafeDelete(iter->second[i]);
		}
}

void ObjectManager::Update()
{
	ObjectIter iter = mObjectList.begin();
	for (; iter != mObjectList.end(); ++iter)
		for (int i = 0; i < iter->second.size(); ++i)
		{
			if (iter->second[i]->GetIsDestroy())
			{
				iter->second[i]->Release();
				SafeDelete(iter->second[i]);
				iter->second.erase(iter->second.begin() + i);
				--i;
				continue;
			}

			if (iter->second[i]->GetIsActive())
				iter->second[i]->Update();
		}
}

void ObjectManager::Render(HDC hdc)
{
	ObjectIter iter = mObjectList.begin();
	for (; iter != mObjectList.end(); ++iter)
		for (int i = 0; i < iter->second.size(); ++i)
			if (iter->second[i]->GetIsActive())
				iter->second[i]->Render(hdc);
}

void ObjectManager::AddObject(ObjectLayer layer, GameObject* object)
{
	mObjectList[layer].push_back(object);
}

GameObject* ObjectManager::FindObject(const string& name)
{
	ObjectIter iter = mObjectList.begin();
	for (; iter != mObjectList.end(); ++iter)
		for (int i = 0; i < iter->second.size(); ++i)
			if (iter->second[i]->GetName() == name)
				return iter->second[i];

	return nullptr;
}

GameObject* ObjectManager::FindObject(ObjectLayer layer, const string& name)
{
	ObjectIter iter = mObjectList.find(layer);
	for (int i = 0; i < iter->second.size(); ++i)
		if (iter->second[i]->GetName() == name)
			return iter->second[i];

	return nullptr;
}

vector<GameObject*> ObjectManager::FindObjects(const string& name)
{
	vector<GameObject*> result;

	ObjectIter iter = mObjectList.begin();
	for (; iter != mObjectList.end(); ++iter)
		for (int i = 0; i < iter->second.size(); ++i)
			if (iter->second[i]->GetName() == name)
				result.push_back(iter->second[i]);

	return result;
}

vector<GameObject*> ObjectManager::FindObjects(ObjectLayer layer, const string& name)
{
	vector<GameObject*> result;

	ObjectIter iter = mObjectList.find(layer);
	for (int i = 0; i < iter->second.size(); ++i)
		if (iter->second[i]->GetName() == name)
			result.push_back(iter->second[i]);

	return result;
}
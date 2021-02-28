#pragma once
#include "Scene.h"

class Enemy;
class Player;
class Monkey;
class Image;
class Platform;
class Scene08 final : public Scene
{
	Player* mPlayer;
	Monkey* mMonkey;
	Image* mMap;
	RECT mGround;
	Platform* mPlatform01;

public:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

	//������
	void AddMonkey(float x, float y); //y�� �÷����� ��Ʈ�� ž
	void AddWitch(float x, float y); //y�� �÷����� ��Ʈ�� ž
	void AddBombImp(float x, float y); //y�� �÷����� ��Ʈ�� ž
	void AddShieldImp(float x, float y); //y�� �÷����� ��Ʈ�� ž
	void AddDaggerImp(float x, float y); //y�� �÷����� ��Ʈ�� ž
	void AddPotion(float x, float y);
};
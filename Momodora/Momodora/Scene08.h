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

	//적생성
	void AddMonkey(float x, float y); //y에 플랫폼의 랙트의 탑
	void AddWitch(float x, float y); //y에 플랫폼의 랙트의 탑
	void AddBombImp(float x, float y); //y에 플랫폼의 랙트의 탑
	void AddShieldImp(float x, float y); //y에 플랫폼의 랙트의 탑
	void AddDaggerImp(float x, float y); //y에 플랫폼의 랙트의 탑
	void AddPotion(float x, float y);
};
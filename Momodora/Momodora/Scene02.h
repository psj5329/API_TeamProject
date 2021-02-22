#pragma once
#include "Scene.h"

class Enemy;
class Player;
class Monkey;
class Image;
class Platform;
class Scene02 final : public Scene
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
};
#pragma once
#include "Scene.h"

class Enemy;
class Player;
class Monkey;
class Image;
class Scene02 final : public Scene
{
	Player* mPlayer;
	Monkey* mMonkey;
	Image* mMap;

public:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
};
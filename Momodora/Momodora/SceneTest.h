#pragma once
#include "Scene.h"

class Image;
class Platform;

class SceneTest final : public Scene
{
	Image* mMapTest;

public:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
};
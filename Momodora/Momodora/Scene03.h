#pragma once
#include "Scene.h"

class Boss;
class Scene03 final : public Scene
{
	Boss* mBoss;

public:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
};
#pragma once
#include "Scene.h"

class Scene05 : public Scene
{
public:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
};
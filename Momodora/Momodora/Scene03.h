#pragma once
#include "Scene.h"

class Scene03 final : public Scene
{
public:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
};
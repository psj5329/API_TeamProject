#pragma once
#include "Scene.h"
#include "Image.h"

class Scene07 final : public Scene
{
public:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
};
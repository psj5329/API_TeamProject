#pragma once
#include "Scene.h"

class Scene01 : public Scene
{
public:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

public:
	void PlaceRect();
};
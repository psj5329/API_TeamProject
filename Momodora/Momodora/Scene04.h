#pragma once
#include "Scene.h"

class Scene04 : public Scene
{
	bool FennelIntro;

public:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

public:
	void PlaceRect();
};
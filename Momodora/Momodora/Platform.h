#pragma once
#include "GameObject.h"

enum class PlatformType : int
{
	Normal = 0,
	Jump,
	End
};

class Platform : public GameObject
{
	PlatformType mPlatformType;

public:
	Platform();
	Platform(float x, float y);

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
};
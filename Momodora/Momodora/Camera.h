#pragma once
#include "GameObject.h"

class Image;

class Camera : public GameObject
{
public:
	enum class Mode : int
	{
		Follow,
		Free
	};

protected:
	Mode mMode;
	GameObject* mTarget;
	float mMoveSpeed;
	bool mShakeStart;
	float mShakeTime;
	float mShakeX;
	float mShakeY;
	float mShakePower;

public:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

public:
	void Render(HDC hdc, Image* image, int x, int y);
	void Render(HDC hdc, Image* image, int x, int y, int tempX, int tempY, int tempWidth, int tempHeight);
	void FrameRender(HDC hdc, Image* image, int x, int y, int frameX, int frameY);
	void AlphaRender(HDC hdc, Image* image, int x, int y, float alpha);
	void AlphaFrameRender(HDC hdc, Image* image, int x, int y, int frameX, int frameY, float alpha);
	void ScaleRender(HDC hdc, Image* image, int x, int y, int width, int height);
	void ScaleFrameRender(HDC hdc, Image* image, int x, int y, int frameX, int frameY, int width, int height);
	void AlphaScaleRender(HDC hdc, Image* image, int x, int y, int width, int height, float alpha);
	void AlphaScaleFrameRender(HDC hdc, Image* image, int x, int y, int frameX, int frameY, int width, int height, float alpha);

	void RenderRectInCamera(HDC hdc, RECT rect);
	void RenderEllipseInCamera(HDC hdc, float x, float y, float radius);

public:
	bool IsInCameraArea(float x, float y, float width, float height);
	bool IsInCameraArea(RECT rect);

public:
	inline void SetMode(Mode mode) { mMode = mode; }
	inline void SetTarget(GameObject* target) { mTarget = target; }
	inline float GetMoveSpeed() const { return mMoveSpeed; }
	inline void SetMoveSpeed(float moveSpeed) { mMoveSpeed = moveSpeed; }
	inline void SetShake(float shakeTime) { mShakeStart = true; mShakeTime = shakeTime; }
	inline void SetShakePower(float shakePower) { mShakePower = shakePower; }
};
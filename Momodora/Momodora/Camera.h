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
	float mShakeTime;
	int mShakeX;
	int mShakeY;
	int mShakePower;

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
	inline void SetShake(float shakeTime) { mShakeTime = shakeTime; } // 2. 실제로 shaking
	inline void SetShakePower(int shakePower) { mShakePower = shakePower; } // 1. 떨리는 정도 세팅(누군가 한 번 세팅해놓으면, 바꾸고 싶지 않을 경우 안 써도 되긴 함)
};
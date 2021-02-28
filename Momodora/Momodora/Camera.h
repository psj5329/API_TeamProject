#pragma once
#include "GameObject.h"

class Image;

class Camera : public GameObject
{
public:
	enum class Mode : int
	{
		Follow,
		Fix,
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

	int mMarginX;
	int mMarginY;

	int tempRight; // getDirection 대신 임시로

	int mFixX;
	int mFixY;

public:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

public:
	void Render(HDC hdc, Image* image, int x, int y, bool ui = false);
	void Render(HDC hdc, Image* image, int x, int y, int tempX, int tempY, int tempWidth, int tempHeight, bool ui = false);
	void FrameRender(HDC hdc, Image* image, int x, int y, int frameX, int frameY, bool ui = false);
	void AlphaRender(HDC hdc, Image* image, int x, int y, float alpha, bool ui = false);
	void AlphaRender(HDC hdc, Image* image, int x, int y, int tempX, int tempY, int tempWidth, int tempHeight, float alpha, bool ui = false);
	void AlphaFrameRender(HDC hdc, Image* image, int x, int y, int frameX, int frameY, float alpha, bool ui = false);
	void ScaleRender(HDC hdc, Image* image, int x, int y, int width, int height, bool ui = false);
	void ScaleFrameRender(HDC hdc, Image* image, int x, int y, int frameX, int frameY, int width, int height, bool ui = false);
	void AlphaScaleRender(HDC hdc, Image* image, int x, int y, int width, int height, float alpha, bool ui = false);
	void AlphaScaleFrameRender(HDC hdc, Image* image, int x, int y, int frameX, int frameY, int width, int height, float alpha, bool ui = false);

	void RenderRectInCamera(HDC hdc, RECT rect, bool ui = false);
	void RenderEllipseInCamera(HDC hdc, float x, float y, float radius, bool ui = false);

public:
	bool IsInCameraArea(float x, float y, float width, float height);
	bool IsInCameraArea(RECT rect);

public:
	Mode GetMode()const { return mMode; }
	inline void SetMode(Mode mode) { mMode = mode; }
	inline void SetTarget(GameObject* target) { mTarget = target; }
	inline float GetMoveSpeed()const { return mMoveSpeed; }
	inline void SetMoveSpeed(float moveSpeed) { mMoveSpeed = moveSpeed; }
	inline void SetShake(float shakeTime) { mShakeTime = shakeTime; } // 2. 실제로 shaking
	inline void SetShakePower(int shakePower) { mShakePower = shakePower; } // 1. 떨리는 정도 세팅(누군가 한 번 세팅해놓으면, 바꾸고 싶지 않을 경우 안 써도 되긴 함)

	inline bool GetRight()const { return tempRight; }
	inline void SetRight(bool temp) { tempRight = temp; }

	inline int GetFixX()const { return mFixX; }
	inline void SetFixX(int x) { mFixX = x; }
	inline int GetFixY()const { return mFixY; }
	inline void SetFixY(int y) { mFixY = y; }
	inline void SetFix(int x, int y) { mFixX = x, mFixY = y; }
};
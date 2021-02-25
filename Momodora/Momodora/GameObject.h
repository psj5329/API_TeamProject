#pragma once

enum class Direction : int
{
	Left,
	Right
};

class GameObject
{
protected:
	string mName;
	float mX;
	float mY;
	float mSizeX;
	float mSizeY;
	Direction mDirection;
	RECT mRect;
	RECT mHitBox; // 히트박스(피격)
	RECT mAttackBox; // 어택박스(공격)

	bool mIsActive;
	bool mIsDestroy;

public:
	GameObject();
	GameObject(float x, float y);

	virtual void Init() = 0;
	virtual void Release() = 0;
	virtual void Update() = 0;
	virtual void Render(HDC hdc) = 0;

public:
	inline string GetName()const { return mName; }
	inline void SetName(const string& name) { mName = name; }
	inline float GetX()const { return mX; }
	inline void SetX(float x) { mX = x; }
	inline float GetY()const { return mY; }
	inline void SetY(float y) { mY = y; }
	inline float GetSizeX()const { return mSizeX; }
	inline void SetSizeX(float sizeX) { mSizeX = sizeX; }
	inline float GetSizeY()const { return mSizeY; }
	inline void SetSizeY(float sizeY) { mSizeY = sizeY; }

	inline Direction GetDirection()const { return mDirection; }
	inline void SetDirection(Direction direction) { mDirection = direction; }

	inline RECT GetRect()const { return mRect; }
	inline void SetRect(RECT rect) { mRect = rect; }
	inline void SetRect(int left, int top, int right, int bottom) { mRect.left = left; mRect.top = top; mRect.right = right; mRect.bottom = bottom; }
	inline RECT GetHitBox()const { return mHitBox; }
	inline void SetHitBox(RECT rect) { mHitBox = rect; }
	inline void SetHitBox(int left, int top, int right, int bottom) { mHitBox.left = left; mHitBox.top = top; mHitBox.right = right; mHitBox.bottom = bottom; }
	inline RECT GetAttackBox()const { return mAttackBox; }
	inline void SetAttackBox(RECT rect) { mAttackBox = rect; }
	inline void SetAttackBox(int left, int top, int right, int bottom) { mAttackBox.left = left; mAttackBox.top = top; mAttackBox.right = right; mAttackBox.bottom = bottom; }

	inline bool GetIsActive()const { return mIsActive; }
	inline void SetIsActive(bool isActive) { mIsActive = isActive; }
	inline bool GetIsDestroy()const { return mIsDestroy; }
	inline void SetIsDestroy(bool isDestroy) { mIsDestroy = isDestroy; }

	inline void SetObject(bool isActive = true, bool isDestroy = false) { mIsActive = isActive; mIsDestroy = isDestroy; }
	inline void SetObject(const string& name, bool isActive = true, bool isDestroy = false) { mName = name; mIsActive = isActive; mIsDestroy = isDestroy; }
};
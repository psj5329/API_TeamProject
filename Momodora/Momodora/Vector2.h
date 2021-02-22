#pragma once

class Vector2 final
{
private:
	float mX;
	float mY;

public:
	Vector2();
	Vector2(float x, float y);
	Vector2(int x, int y);
	Vector2(POINT pt);

	Vector2 operator+(const Vector2& v);
	Vector2 operator-(const Vector2& v);
	void operator+=(const Vector2& v);
	void operator-=(const Vector2& v);
	Vector2 operator*(float scalar);
	Vector2 operator/(float scalar);
	bool operator==(const Vector2& v);
	bool operator!=(const Vector2& v);

public:
	static Vector2 Nomalize(const Vector2& v);
	static float Length(const Vector2& v);
	static float Dot(const Vector2& v1, const Vector2& v2);
	static float Cross(const Vector2& v1, const Vector2& v2);

public:
	inline float GetX()const { return mX; }
	inline void SetX(float x) { mX = x; }
	inline float GetY()const { return mY; }
	inline void SetY(float y) { mY = y; }
};
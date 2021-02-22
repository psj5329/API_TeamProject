#include "pch.h"
#include "Vector2.h"

Vector2::Vector2()
	: mX(0.f), mY(0.f)
{
}

Vector2::Vector2(float x, float y)
	: mX(x), mY(y)
{
}

Vector2::Vector2(int x, int y)
	: mX((float)x), mY((float)y)
{
}

Vector2::Vector2(POINT pt)
	: mX((float)pt.x), mY((float)pt.y)
{
}

Vector2 Vector2::operator+(const Vector2& v)
{
	Vector2 result;
	result.mX = mX + v.mX;
	result.mY = mY + v.mY;
	return result;
}

Vector2 Vector2::operator-(const Vector2& v)
{
	Vector2 result;
	result.mX = mX - v.mX;
	result.mY = mY - v.mY;
	return result;
}

void Vector2::operator+=(const Vector2& v)
{
	mX += v.mX;
	mY += v.mY;
}

void Vector2::operator-=(const Vector2& v)
{
	mX -= v.mX;
	mY -= v.mY;
}

Vector2 Vector2::operator*(float scalar)
{
	Vector2 result;
	result.mX = mX * scalar;
	result.mY = mY * scalar;
	return result;
}

Vector2 Vector2::operator/(float scalar)
{
	Vector2 result;
	result.mX = mX / scalar;
	result.mY = mY / scalar;
	return result;
}

bool Vector2::operator==(const Vector2& v)
{
	if (Math::FloatEqual(mX, v.mX))
	{
		if (Math::FloatEqual(mY, v.mY))
		{
			return true;
		}
	}

	return false;
}

bool Vector2::operator!=(const Vector2& v)
{
	if (!Math::FloatEqual(mX, v.mX))
		return true;

	if (!Math::FloatEqual(mY, v.mY))
		return true;
	
	return false;
}

Vector2 Vector2::Nomalize(const Vector2& v)
{
	Vector2 result;
	float length = sqrtf(result.mX * result.mX + result.mY + result.mY);
	result.mX /= length;
	result.mY /= length;
	return result;
}

float Vector2::Length(const Vector2& v)
{
	return sqrtf(v.mX * v.mX + v.mY + v.mY);
}

float Vector2::Dot(const Vector2& v1, const Vector2& v2)
{
	return v1.mX * v2.mX + v1.mY * v2.mY;
}

float Vector2::Cross(const Vector2& v1, const Vector2& v2)
{
	return v1.mX * v2.mY - v1.mY * v2.mX;
}
#pragma once
#define PI 3.1415926535f
#define PI2 (3.1415926535f * 2.f)
#define Epsilon (1E-6f)

class Math
{
public:
	static float GetDistance(float aX, float aY, float bX, float bY);
	static float GetAngle(float aX, float aY, float bX, float bY);
	static float Lerp(float start, float end, float ratio);
	static bool FloatEqual(float a, float b);
};
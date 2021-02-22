#pragma once

inline RECT RectMake(int x, int y, int width, int height)
{
	return { x, y, x + width, y + height };
}

inline RECT RectMakeCenter(int x, int y, int width, int height)
{
	return { x - width / 2, y - height / 2, x + width / 2, y + height / 2 };
}

inline void RenderRect(HDC hdc, RECT rc)
{
	Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
}

inline void RenderRect(HDC hdc, int left, int top, int right, int bottom)
{
	Rectangle(hdc, left, top, right, bottom);
}

inline void RenderEllipse(HDC hdc, RECT rc)
{
	Ellipse(hdc, rc.left, rc.top, rc.right, rc.bottom);
}

inline void RenderEllipse(HDC hdc, int x, int y, int radius)
{
	Ellipse(hdc, x - radius, y - radius, x + radius, y + radius);
}

inline void RenderLine(HDC hdc, int startX, int startY, int endX, int endY)
{
	MoveToEx(hdc, startX, startY, NULL);
	LineTo(hdc, endX, endY);
}

inline float GetDistance(int aX, int aY, int bX, int bY)
{
	float width = (float)(aX - bX);
	float height = (float)(aY - bY);

	return sqrtf(width * width + height * height);
}

inline bool IntersectRectToCircle(RECT rc, int x, int y, int radius)
{
	if ((rc.left <= x && x <= rc.right) || (rc.top <= y && y <= rc.bottom))
	{
		RECT newRect = rc;
		newRect.left -= radius;
		newRect.top -= radius;
		newRect.right += radius;
		newRect.bottom += radius;

		if (newRect.left <= x && x <= newRect.right && newRect.top <= y && y <= newRect.bottom)
			return true;
	}

	if (radius >= GetDistance(x, y, rc.left, rc.top)) return true;
	if (radius >= GetDistance(x, y, rc.left, rc.bottom)) return true;
	if (radius >= GetDistance(x, y, rc.right, rc.top)) return true;
	if (radius >= GetDistance(x, y, rc.right, rc.bottom)) return true;

	return false;
}
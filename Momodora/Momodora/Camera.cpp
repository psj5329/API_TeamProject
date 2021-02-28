#include "pch.h"
#include "Camera.h"
#include "Image.h"
#include "Player.h"
#include "Scene.h"

void Camera::Init()
{
	mX = WINSIZEX / 2;
	mY = WINSIZEY / 2;
	mSizeX = WINSIZEX;
	mSizeY = WINSIZEY;
	mRect = RectMakeCenter((int)mX, (int)mY, (int)mSizeX, (int)mSizeY);

	mMode = Mode::Free;
	mTarget = nullptr;
	mMoveSpeed = 5.f;

	mMarginX = 0;
	mMarginY = 0;

	tempRight = true; // 임시
}

void Camera::Release()
{
}

void Camera::Update()
{
	float targetRight = 0.f;
	float targetLeft = 0.f;
	float targetY = 0.f;

	Player* player = NULL;
	Direction playerDir = (Direction)NULL;

	if (SCENEMANAGER->GetCurrentSceneName() != L"LoadingScene")
	//if (player != nullptr)
	{
		player = OBJECTMANAGER->GetPlayer();
		playerDir = player->GetDirection();
	}

	int sceneSizeX = SCENEMANAGER->GetCurrentScene()->GetSceneSizeX();
	int sceneSizeY = SCENEMANAGER->GetCurrentScene()->GetSceneSizeY();

	switch (mMode)
	{
	case Camera::Mode::Follow:
		if (mTarget)
		{
			targetRight = mTarget->GetX() + WINSIZEX / 5.f;
			targetLeft = mTarget->GetX() - WINSIZEX / 5.f;
			targetY = mTarget->GetY() + WINSIZEY / 10.f;

			//if (player != nullptr)
			//{
				//mX = mTarget->GetX();
			if (playerDir == Direction::Right)//(tempRight)      // 고정 인 곳 신사이즈로 조절
				if (targetRight <= WINSIZEX / 2.f)
					mX = Math::Lerp(mX, WINSIZEX / 2.f, 0.4f * mMoveSpeed * TIME->DeltaTime());
				else if (targetRight >= sceneSizeX - WINSIZEX / 2.f)
					mX = Math::Lerp(mX, sceneSizeX - WINSIZEX / 2.f, 0.4f * mMoveSpeed * TIME->DeltaTime());
				else
					mX = Math::Lerp(mX, targetRight, 0.4f * mMoveSpeed * TIME->DeltaTime());
			else
				if (targetLeft <= WINSIZEX / 2.f)
					mX = Math::Lerp(mX, WINSIZEX / 2.f, 0.4f * mMoveSpeed * TIME->DeltaTime());
				else if (targetLeft >= sceneSizeX - WINSIZEX / 2.f)
					mX = Math::Lerp(mX, sceneSizeX - WINSIZEX / 2.f, 0.4f * mMoveSpeed * TIME->DeltaTime());
				else
					mX = Math::Lerp(mX, targetLeft, 0.4f * mMoveSpeed * TIME->DeltaTime());
			//}

			// y도 신사이즈로 조절
			//mY = mTarget->GetY();
			if (targetY <= WINSIZEY / 2.f)
				mY = Math::Lerp(mY, WINSIZEY / 2.f, 2.f * mMoveSpeed * TIME->DeltaTime());
			else if (targetY >= sceneSizeY - WINSIZEY / 2.f)
				mY = Math::Lerp(mY, sceneSizeY - WINSIZEY / 2.f, 2.f * mMoveSpeed * TIME->DeltaTime());
			else
				mY = Math::Lerp(mY, targetY, 2.f * mMoveSpeed * TIME->DeltaTime());
			mRect = RectMakeCenter((int)mX, (int)mY, (int)mSizeX, (int)mSizeY);
		}
		break;
	case Camera::Mode::Fix:
		mX = mFixX;
		mY = mFixY;
		mRect = RectMakeCenter((int)mX, (int)mY, (int)mSizeX, (int)mSizeY);
		break;
	case Camera::Mode::Free:
		if (INPUT->GetKey('A'))
			mX -= mMoveSpeed;
		if (INPUT->GetKey('D'))
			mX += mMoveSpeed;
		if (INPUT->GetKey('W'))
			mY -= mMoveSpeed;
		if (INPUT->GetKey('S'))
			mY += mMoveSpeed;
		mRect = RectMakeCenter((int)mX, (int)mY, (int)mSizeX, (int)mSizeY);
		break;
	}

	if (mShakeTime)
	{
		mShakeTime -= TIME->DeltaTime();

		mShakeX = rand() % (mShakePower * 2 + 1) - mShakePower;
		mShakeY = rand() % (mShakePower * 2 + 1) - mShakePower;

		if (mShakeTime <= 0.f)
		{
			mShakeTime = 0.f;
			mShakeX = 0;
			mShakeY = 0;
		}
	}
}

void Camera::Render(HDC hdc)
{
}

void Camera::Render(HDC hdc, Image* image, int x, int y, bool ui)
{
	if(ui)
		image->Render(hdc, x, y);
	else
		image->Render(hdc, x - mRect.left - mShakeX, y - mRect.top - mShakeY);
}

void Camera::Render(HDC hdc, Image* image, int x, int y, int tempX, int tempY, int tempWidth, int tempHeight, bool ui)
{
	if (ui)
		image->Render(hdc, x, y, tempX, tempY, tempWidth, tempHeight);
	else
		image->Render(hdc, x - mRect.left - mShakeX, y - mRect.top - mShakeY, tempX, tempY, tempWidth, tempHeight);
}

void Camera::FrameRender(HDC hdc, Image* image, int x, int y, int frameX, int frameY, bool ui)
{
	if (ui)
		image->FrameRender(hdc, x, y, frameX, frameY);
	else
		image->FrameRender(hdc, x - mRect.left - mShakeX, y - mRect.top - mShakeY, frameX, frameY);
}

void Camera::AlphaRender(HDC hdc, Image* image, int x, int y, float alpha, bool ui)
{
	if (ui)
		image->AlphaRender(hdc, x, y, alpha);
	else
		image->AlphaRender(hdc, x - mRect.left - mShakeX, y - mRect.top - mShakeY, alpha);
}

void Camera::AlphaRender(HDC hdc, Image* image, int x, int y, int tempX, int tempY, int tempWidth, int tempHeight, float alpha, bool ui)
{
	if (ui)
		image->AlphaRender(hdc, x, y, tempX, tempY, tempWidth, tempHeight, alpha);
	else
		image->AlphaRender(hdc, x - mRect.left - mShakeX, y - mRect.top - mShakeY, tempX, tempY, tempWidth, tempHeight, alpha);
}

void Camera::AlphaFrameRender(HDC hdc, Image* image, int x, int y, int frameX, int frameY, float alpha, bool ui)
{
	if (ui)
		image->AlphaFrameRender(hdc, x, y, frameX, frameY, alpha);
	else
		image->AlphaFrameRender(hdc, x - mRect.left - mShakeX, y - mRect.top - mShakeY, frameX, frameY, alpha);
}

void Camera::ScaleRender(HDC hdc, Image* image, int x, int y, int width, int height, bool ui)
{
	if (ui)
		image->ScaleRender(hdc, x, y, width, height);
	else
		image->ScaleRender(hdc, x - mRect.left - mShakeX, y - mRect.top - mShakeY, width, height);
}

void Camera::ScaleFrameRender(HDC hdc, Image* image, int x, int y, int frameX, int frameY, int width, int height, bool ui)
{
	if (ui)
		image->ScaleFrameRender(hdc, x, y, frameX, frameY, width, height);
	else
		image->ScaleFrameRender(hdc, x - mRect.left - mShakeX, y - mRect.top - mShakeY, frameX, frameY, width, height);
}

void Camera::AlphaScaleRender(HDC hdc, Image* image, int x, int y, int width, int height, float alpha, bool ui)
{
	if (ui)
		image->AlphaScaleRender(hdc, x, y, width, height, alpha);
	else
		image->AlphaScaleRender(hdc, x - mRect.left - mShakeX, y - mRect.top - mShakeY, width, height, alpha);
}

void Camera::AlphaScaleFrameRender(HDC hdc, Image* image, int x, int y, int frameX, int frameY, int width, int height, float alpha, bool ui)
{
	if (ui)
		image->AlphaScaleFrameRender(hdc, x, y, frameX, frameY, width, height, alpha);
	else
		image->AlphaScaleFrameRender(hdc, x - mRect.left - mShakeX, y - mRect.top - mShakeY, frameX, frameY, width, height, alpha);
}

void Camera::RenderRectInCamera(HDC hdc, RECT rect, bool ui)
{
	if (ui)
	{
	}
	else
	{
		rect.left -= mRect.left;
		rect.right -= mRect.left;
		rect.top -= mRect.top;
		rect.bottom -= mRect.top;
	}
	RenderRect(hdc, rect);
}

void Camera::RenderEllipseInCamera(HDC hdc, float x, float y, float radius, bool ui)
{
	if (ui)
		RenderEllipse(hdc, (int)x, (int)y, (int)radius);
	else
		RenderEllipse(hdc, (int)x - mRect.left, (int)y - mRect.top, (int)radius);
}

bool Camera::IsInCameraArea(float x, float y, float width, float height)
{
	RECT rect = RectMakeCenter((int)x, (int)y, (int)width, (int)height);
	return IsInCameraArea(rect);
}

bool Camera::IsInCameraArea(RECT rect)
{
	if (rect.left > mRect.right)
		return false;
	if (rect.right < mRect.left)
		return false;
	if (rect.top > mRect.bottom)
		return false;
	if (rect.bottom < mRect.top)
		return false;

	return true;
}
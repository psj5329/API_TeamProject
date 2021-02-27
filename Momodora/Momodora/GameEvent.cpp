#include "pch.h"
#include "GameEvent.h"

#include "Camera.h"
#include "Image.h"
IChangeCameraTargetEvent::IChangeCameraTargetEvent(GameObject * target)
{
	mTarget = target;
}

void IChangeCameraTargetEvent::Start()
{
	CameraManager::GetInstance()->GetMainCamera()->SetTarget(mTarget);
}

bool IChangeCameraTargetEvent::Update()
{
	float x = CameraManager::GetInstance()->GetMainCamera()->GetX();
	float y = CameraManager::GetInstance()->GetMainCamera()->GetY();

	if (Math::GetDistance(x, y, mTarget->GetX(), mTarget->GetY()) <= 5.0f)
	{
		return true;
	}

	return false;
}

void IChangeCameraTargetEvent::Render(HDC hdc)
{
}

IDelayEvent::IDelayEvent(float delayTime)
{
	mDelayTime = delayTime;
	mCurrentTime = 0.f;
}

void IDelayEvent::Start()
{
}

bool IDelayEvent::Update()
{
	mCurrentTime += Time::GetInstance()->DeltaTime();

	if (mCurrentTime >= mDelayTime)
	{
		return true;
	}

	return false;
}

void IDelayEvent::Render(HDC hdc)
{
}

IScriptEvent::IScriptEvent(wstring image)
{
	mImage = IMAGEMANAGER->FindImage(image);
	mDelayTime = 2.f;
	mCurrentTime = 0.f;
}

void IScriptEvent::Start()
{
}

bool IScriptEvent::Update()
{
	mCurrentTime += Time::GetInstance()->DeltaTime();

	mShakeX = rand() % (2 * 2 + 1) - 2;
	mShakeY = rand() % (2 * 2 + 1) - 2;

	if (/*mCurrentTime >= mDelayTime || */INPUT->GetKeyDown(VK_SPACE))
	{
		return true;
	}

	return false;
}

void IScriptEvent::Render(HDC hdc)
{
	CameraManager::GetInstance()->GetMainCamera()->Render(hdc, mImage
		, WINSIZEX / 2 - mImage->GetWidth() / 2 + CameraManager::GetInstance()->GetMainCamera()->GetRect().left - mShakeX
		, WINSIZEY / 2 - mImage->GetHeight() / 2 + CameraManager::GetInstance()->GetMainCamera()->GetRect().top - mShakeY);
}

IMoveGameObject::IMoveGameObject(GameObject* object, GameObject * target)
{
	mObject = object;
	mTargetX = target->GetX() + target->GetSizeX() + mObject->GetSizeX();
	mTargetY = target->GetY();
	mSpeedX = (mTargetX - mObject->GetX()) * 0.1f * Time::GetInstance()->DeltaTime();
	mSpeedY = (mTargetY - mObject->GetY()) * 0.1f * Time::GetInstance()->DeltaTime();
}

IMoveGameObject::IMoveGameObject(GameObject* object, float x, float y)
{
	mObject = object;
	mTargetX = x;
	mTargetY = y;
	mSpeedX = (mTargetX - mObject->GetX()) * 0.1f * Time::GetInstance()->DeltaTime();
	mSpeedY = (mTargetY - mObject->GetY()) * 0.1f * Time::GetInstance()->DeltaTime();
}

void IMoveGameObject::Start()
{
	/*mObject->SetIsEventMove(true);
	mObject->SetTargetX(mTargetX);
	mObject->SetTargetY(mTargetY);*/
}

bool IMoveGameObject::Update()
{
	//mObject->SetX(Math::Lerp(mObject->GetX(), mTargetX, 0.5f * Time::GetInstance()->DeltaTime()));
	//mObject->SetY(Math::Lerp(mObject->GetY(), mTargetY, 0.5f * Time::GetInstance()->DeltaTime()));
	mObject->SetX(mObject->GetX() + mSpeedX);
	mObject->SetY(mObject->GetY() + mSpeedY);

	/*if (Math::GetDistance(mObject->GetX(), mObject->GetY(), mTargetX, mTargetY) <= 5.0f)
	{
		mObject->SetIsEventMove(false);
		return true;
	}*/

	return false;
}

void IMoveGameObject::Render(HDC hdc)
{
}

IChangeAnimation::IChangeAnimation(GameObject* object, Animation* animation)
{
	mObject = object;
	mAnimation = animation;
}

void IChangeAnimation::Start()
{
}

bool IChangeAnimation::Update()
{
	//mObject->SetCurrentAnimation(mAnimation);
	return true;
}

void IChangeAnimation::Render(HDC hdc)
{
}

IEraseEvent::IEraseEvent(Image* image1, Image* image2, float r, float time)
{
	mImage1 = image1;
	mImage2 = image2;
	mSize = r;
	mDelayTime = time;
}

void IEraseEvent::Start()
{
	int num = sqrtf(WINSIZEX * WINSIZEX + WINSIZEY * WINSIZEY) / 2;// / mEraseSize;

	for (int i = 0; i < num; ++i)
	{
		POINT p = { i * 2 - WINSIZEX / 3, i * 2 + WINSIZEY / 3 };
		mVecEraseCenter.push_back(p);
	}
	mVecBackEraseCenter = mVecEraseCenter;

	mDelayTime = 0.f;
}

bool IEraseEvent::Update()
{
	mDelayTime += TIME->DeltaTime();
	for (int i = 0; i < mVecEraseCenter.size(); ++i)
	{
		float speed = (rand() % 9 + 1) / 10.f;
		mVecEraseCenter[i].x += cosf(30.f * PI / 180.f) * speed * 2;
		mVecEraseCenter[i].y += -sinf(30.f * PI / 180.f) * speed * 2;

		HBRUSH brush = CreateSolidBrush(RGB(255, 0, 255));
		HPEN pen = CreatePen(PS_SOLID, 1, RGB(255, 0, 255));

		if (mVecEraseCenter[i].x >= 0 && mVecEraseCenter[i].x <= WINSIZEX && mVecEraseCenter[i].y <= WINSIZEY && mVecEraseCenter[i].y >= 0)
		{
			HBRUSH oldBrush = (HBRUSH)SelectObject(mImage1->GetHDC(), brush);
			HPEN oldPen = (HPEN)SelectObject(mImage1->GetHDC(), pen);

			COLORREF pixelColor = GetPixel(mImage1->GetHDC(), mVecEraseCenter[i].x, mVecEraseCenter[i].y);

			RenderEllipse(mImage1->GetHDC(), mVecEraseCenter[i].x, mVecEraseCenter[i].y, mSize * 4);

			SelectObject(mImage1->GetHDC(), oldPen);
			SelectObject(mImage1->GetHDC(), oldBrush);
		}

		if (mDelayTime >= 0.1f)
		{
			float speed = (rand() % 9 + 1) / 10.f;
			mVecBackEraseCenter[i].x += cosf(30.f * PI / 180.f) * speed * 2;
			mVecBackEraseCenter[i].y += -sinf(30.f * PI / 180.f) * speed * 2;

			if (mVecBackEraseCenter[i].x >= 0 && mVecBackEraseCenter[i].x <= WINSIZEX && mVecBackEraseCenter[i].y <= WINSIZEY && mVecBackEraseCenter[i].y >= 0)
			{
				HBRUSH oldBrush = (HBRUSH)SelectObject(mImage2->GetHDC(), brush);
				HPEN oldPen = (HPEN)SelectObject(mImage2->GetHDC(), pen);

				COLORREF pixelColor = GetPixel(mImage2->GetHDC(), mVecBackEraseCenter[i].x, mVecBackEraseCenter[i].y);

				RenderEllipse(mImage2->GetHDC(), mVecBackEraseCenter[i].x, mVecBackEraseCenter[i].y, mSize * 4);

				SelectObject(mImage2->GetHDC(), oldPen);
				SelectObject(mImage2->GetHDC(), oldBrush);
			}
		}

		DeleteObject(pen);
		DeleteObject(brush);
	}

	if (mVecBackEraseCenter[mVecBackEraseCenter.size() / 2].x <= WINSIZEX
		&& mVecBackEraseCenter[mVecBackEraseCenter.size() / 2].y >= 0)
		return false;
	else
		return true;
}

void IEraseEvent::Render(HDC hdc)
{
	//for(int i = 0; i < mVecCircleCenter.size(); ++i)
	//	CAMERAMANAGER->GetMainCamera()->RenderEllipseInCamera(hdc, mVecCircleCenter[i].x, mVecCircleCenter[i].y, mSize);
}

IChangeImage::IChangeImage(Image* image1, Image* image2)
{
	mImage1 = image1;
	mImage2 = image2;
}

void IChangeImage::Start()
{
}

bool IChangeImage::Update()
{
	// 아 이럼 이상한디
	//mImage1 = mImage2;
	return false;
}

void IChangeImage::Render(HDC hdc)
{
}

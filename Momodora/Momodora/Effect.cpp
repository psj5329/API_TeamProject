#include "pch.h"
#include "Effect.h"
#include "Image.h"
#include "Animation.h"
#include "Camera.h"
void Effect::Init(wstring imageKey, float x, float y, int startFrameX, int endFrameX, float frameUpdateTime)
{
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Effect, this);


	mImage = ImageManager::GetInstance()->FindImage(imageKey);
	mX = x;
	mY = y;
	mSizeX = mImage->GetFrameWidth() / 3;
	mSizeY = mImage->GetFrameHeight() / 3;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	
	mAnimation = new Animation();
	mAnimation->InitFrameByStartEnd(startFrameX, 0, endFrameX, 0, false);
	mAnimation->SetIsLoop(false);
	mAnimation->SetFrameUpdateTime(frameUpdateTime);
	mAnimation->SetCallbackFunc(bind(&Effect::EndEffect, this));

	mCurrentAnimation = mAnimation;
	mCurrentAnimation->Play();
}

void Effect::Release()
{
	SafeDelete(mAnimation);
}

void Effect::Update()
{
	frameCount += TIME->DeltaTime();

	mCurrentAnimation->Update();
}

void Effect::Render(HDC hdc)
{
	CAMERAMANAGER->GetMainCamera()->ScaleFrameRender(hdc, mImage, mRect.left, mRect.top, mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY(), mSizeX, mSizeY);
}


void Effect::EndEffect()
{
	mCurrentAnimation->Pause();
	this->SetIsDestroy(true);
}
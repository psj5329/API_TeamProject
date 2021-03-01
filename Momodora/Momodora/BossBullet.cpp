#include "pch.h"
#include "BossBullet.h"

#include "Image.h"
#include "Camera.h"
#include "ObjectManager.h"
#include "CollisionManager.h"
#include "Player.h"

void BossBullet::Init()
{
	mName = "BossBullet";
	mImage = IMAGEMANAGER->FindImage(L"BossBullet1");
	mX = 0.f;
	mY = 0.f;
	mSizeX = IMAGEMANAGER->FindImage(L"BossBullet1")->GetWidth() * 3;
	mSizeY = IMAGEMANAGER->FindImage(L"BossBullet1")->GetHeight() * 3;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);

	mPattern = BulletPattern::PatternIdle;
	mAngle = 0.f;
	mSpeed = 200.f;
	mShootTime = 0.f;
	mIsShoot = false;
}

void BossBullet::Release()
{
	//SafeDelete(mImage);
}

void BossBullet::Update()
{
	mShootTime += TIME->DeltaTime();

	switch (mPattern)
	{
	case BulletPattern::PatternIdle:
		break;
	case BulletPattern::PatternBulletDown:			// 그저 아래로
		if(mShootTime >= 0.5f)
			mIsShow = true;

		if (mShootTime >= 1.f)
		{
			mIsShoot = true;
			mX += cosf(mAngle) * mSpeed * TIME->DeltaTime() * 4;
			mY += -sinf(mAngle) * mSpeed * TIME->DeltaTime() * 4;
		}
		break;
	case BulletPattern::PatternBulletUp:			// 물결치며 올라감
		if (mShootTime >= 0.5f)
			mIsShow = true;

		if (mShootTime >= 1.f)
		{
			mIsShoot = true;
			mAngle += 0.1f;
			mX += sinf(mAngle) * mSpeed * TIME->DeltaTime() * 2;
			mY -= mSpeed * TIME->DeltaTime() * 2;
		}
		break;
	case BulletPattern::PatternBulletTarget:		// 플레이어 방향으로 날아감
		mIsShow = true;
		if (mShootTime < 4.f)
		{
			if (!mIsShoot)
			{
				mX += cosf(mAngle) * mSpeed * TIME->DeltaTime();
				mY += -sinf(mAngle) * mSpeed * TIME->DeltaTime();
			}
		}
		else
		{
			if(!mIsShoot)
			{
				mIsShoot = true;

				float x = OBJECTMANAGER->GetPlayer()->GetX();
				float y = OBJECTMANAGER->GetPlayer()->GetY();

				mAngle = Math::GetAngle(mX, mY, x, y);
			}

			mX += cosf(mAngle) * mSpeed * TIME->DeltaTime() * 4;
			mY += -sinf(mAngle) * mSpeed * TIME->DeltaTime() * 4;
		}
		break;
	}

	if (mY - mSizeY / 2 >= 1600 || mY + mSizeY / 2 <= 900)
	{
		mIsActive = false;
		mIsDestroy = true;
	}

	// 확인 결과 땅에 닿을 때에만 사라진다
	if (COLLISIONMANAGER->IsCollideWithPlatform(&mRect) && mIsShoot)
	{
		if (mPattern != BulletPattern::PatternBulletUp)
		{
			mIsActive = false;
			mIsDestroy = true;

			SOUNDMANAGER->Play(L"Explosion", 0.05f);
		}
	}

	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	mAttackBox = RectMakeCenter(mX, mY, mSizeX - 5, mSizeY - 5);
}

void BossBullet::Render(HDC hdc)
{
#ifdef DEBUG
	CAMERAMANAGER->GetMainCamera()->RenderRectInCamera(hdc, mRect);
	CAMERAMANAGER->GetMainCamera()->RenderRectInCamera(hdc, mAttackBox);

#endif // DEBUG

	if(mIsShow)
		CAMERAMANAGER->GetMainCamera()->ScaleRender(hdc, mImage, mRect.left, mRect.top, mSizeX, mSizeY);
}

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
	case BulletPattern::PatternBulletDown:			// ���� �Ʒ���
		if (mShootTime >= 1.f)
		{
			mIsShoot = true;
			mIsShow = true;
			mX += cosf(mAngle) * mSpeed * TIME->DeltaTime() * 4;
			mY += -sinf(mAngle) * mSpeed * TIME->DeltaTime() * 4;
		}
		break;
	case BulletPattern::PatternBulletUp:			// ����ġ�� �ö�
		if (mShootTime >= 1.f)
		{
			mIsShow = true;
			mIsShoot = true;
			mAngle += 0.1f;
			mX += sinf(mAngle) * mSpeed * TIME->DeltaTime() * 2;
			mY -= mSpeed * TIME->DeltaTime() * 2;
		}
		break;
	case BulletPattern::PatternBulletTarget:		// �÷��̾� �������� ���ư�
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

	if (mY - mSizeY / 2 >= WINSIZEY || mY + mSizeY / 2 <= 0)
		mIsActive = false;

	// Ȯ�� ��� ���� ���� ������ �������
	//if (COLLISIONMANAGER->IsCollision(&mRect, &OBJECTMANAGER->GetPlayer()->GetRect()))
	//	mIsActive = false;
	if (COLLISIONMANAGER->IsCollideWithPlatform(&mRect))
		mIsActive = false;

	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
}

void BossBullet::Render(HDC hdc)
{
#ifdef DEBUG
	CAMERAMANAGER->GetMainCamera()->RenderRectInCamera(hdc, mRect);

#endif // DEBUG

	if(mIsShow)
		CAMERAMANAGER->GetMainCamera()->ScaleRender(hdc, mImage, mRect.left, mRect.top, mSizeX, mSizeY);
}
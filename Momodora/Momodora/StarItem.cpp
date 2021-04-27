#include "pch.h"
#include "StarItem.h"

#include "Image.h"
#include "Camera.h"
#include "StarCountUI.h"
#include "Player.h"

void StarItem::Init()
{
	mName = "Star";
	mImage = IMAGEMANAGER->FindImage(L"Star");
	mX = WINSIZEX / 2;
	mY = WINSIZEY / 2;
	mSizeX = mImage->GetWidth();
	mSizeY = mImage->GetHeight();

	mSpeed = 200.f;
	mAngle = 0.f;
	mJumpPower = 3.f;
	mFirstJumpPower = mJumpPower;

	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);

	mIsColl = false;

	//�÷��̾� ã�ƿ���
	vector<GameObject*> player = OBJECTMANAGER->GetObjectList(ObjectLayer::Player);
	mPlayer = (Player*)player[0];
}

void StarItem::Release()
{
}

void StarItem::Update()
{
	//�ڼ����Ծ�����
	if (mPlayer->GetHaveMagnet()) 
	//if (true)
	{
		Magnet();
	}
	//�ڼ��� �ȸԾ�����
	else
	{
		if (mFirstJumpPower >= 0.01f)
		{
			mX += cosf(mAngle) * mSpeed * TIME->DeltaTime();
			mY += -sinf(mAngle) * mSpeed * TIME->DeltaTime() - mJumpPower;
			mJumpPower -= 0.2f;

			if (mJumpPower < 0.f)
				mIsJump = false;
		}

		int col = 0;

		if (COLLISIONMANAGER->IsCollision(&mRect, ObjectLayer::Platform, col))
		{
			if (col == 1)
			{
				// ���� �浹
				if (!mIsJump)
				{
					mIsJump = true;
					mJumpPower = mFirstJumpPower / 3;
					mFirstJumpPower = mJumpPower;
				}
			}
			else if (col == 2)
			{
				// �¿� �浹
				if (!mIsColl)
				{
					mIsColl = true;
					mAngle = PI - mAngle;
				}
			}
		}

	}
	// ��� �浹 �����ް� ui�� �ٲ襤�Ŷ� ������ ��� �� ��
	if (COLLISIONMANAGER->IsCollision(&mRect, ObjectLayer::Player))
	{
		mIsActive = false;
		((StarCountUI*)OBJECTMANAGER->FindObject("StarCountUI"))->SetStarCount(
			((StarCountUI*)OBJECTMANAGER->FindObject("StarCountUI"))->GetStarCount() + 1);
	}
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
}

void StarItem::Render(HDC hdc)
{
#ifdef DEBUG
	//CAMERAMANAGER->GetMainCamera()->RenderRectInCamera(hdc, mRect);
#endif // DEBUG
	CAMERAMANAGER->GetMainCamera()->ScaleRender(hdc, mImage, mRect.left, mRect.top, mSizeX, mSizeY);
}

void StarItem::Magnet()
{
	mFrameCount += TIME->DeltaTime();

	if (mFrameCount < 3) 
	{
		mX += cosf(mAngle) * mSpeed * TIME->DeltaTime();
		mY += -sinf(mAngle) * mSpeed * TIME->DeltaTime() - mJumpPower;
		mJumpPower -= 0.2f;

		if (mJumpPower < 0.f)
			mIsJump = false;

		if (mFirstJumpPower >= 0.01f)
		{
			mX += cosf(mAngle) * mSpeed * TIME->DeltaTime();
			mY += -sinf(mAngle) * mSpeed * TIME->DeltaTime() - mJumpPower;
			mJumpPower -= 0.2f;

			if (mJumpPower < 0.f)
				mIsJump = false;
		}

		int col = 0;

		if (COLLISIONMANAGER->IsCollision(&mRect, ObjectLayer::Platform, col))
		{
			if (col == 1)
			{
				// ���� �浹
				if (!mIsJump)
				{
					mIsJump = true;
					mJumpPower = mFirstJumpPower / 3;
					mFirstJumpPower = mJumpPower;
				}
			}
			else if (col == 2)
			{
				// �¿� �浹
				if (!mIsColl)
				{
					mIsColl = true;
					mAngle = PI - mAngle;
				}
			}
		}
	}
	else
	{
		mAngle = Math::GetAngle(mPlayer->GetX(), mPlayer->GetY(), mX, mY);
		mX -= cosf(mAngle) * mSpeed * TIME->DeltaTime();
		mY -= -sinf(mAngle) * mSpeed * TIME->DeltaTime();
		mSpeed += 2.f;
	}
}
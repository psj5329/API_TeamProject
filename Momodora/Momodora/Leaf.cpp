#include "pch.h"
#include "Leaf.h"
#include "Animation.h"
#include "Image.h"
#include "Camera.h"
#include "Player.h"

void Leaf::Init()
{
	mIsActive = false;
	mIsDestroy = false;

	mLeafImage01 = IMAGEMANAGER->FindImage(L"Leaf1");
	mLeafImage02 = IMAGEMANAGER->FindImage(L"Leaf2");
	mLeafImage03 = IMAGEMANAGER->FindImage(L"Leaf3");
	mAirLeafImage = IMAGEMANAGER->FindImage(L"AirLeaf");

	mLeaf01Left = new Animation();
	mLeaf01Left->InitFrameByStartEnd(0, 1, 6, 1, true);
	mLeaf01Left->SetIsLoop(false);
	mLeaf01Left->SetFrameUpdateTime(0.1f);

	mLeaf01Right = new Animation();
	mLeaf01Right->InitFrameByStartEnd(0, 0, 6, 0, false);
	mLeaf01Right->SetIsLoop(false);
	mLeaf01Right->SetFrameUpdateTime(0.1f);

	mLeaf02Left = new Animation();
	mLeaf02Left->InitFrameByStartEnd(0, 1, 6, 1, true);
	mLeaf02Left->SetIsLoop(false);
	mLeaf02Left->SetFrameUpdateTime(0.1f);

	mLeaf02Right = new Animation();
	mLeaf02Right->InitFrameByStartEnd(0, 0, 6, 0, false);
	mLeaf02Right->SetIsLoop(false);
	mLeaf02Right->SetFrameUpdateTime(0.1f);

	mLeaf03Left = new Animation();
	mLeaf03Left->InitFrameByStartEnd(0, 1, 10, 1, true);
	mLeaf03Left->SetIsLoop(false);
	mLeaf03Left->SetFrameUpdateTime(0.1f);

	mLeaf03Right = new Animation();
	mLeaf03Right->InitFrameByStartEnd(0, 0, 10, 0, false);
	mLeaf03Right->SetIsLoop(false);
	mLeaf03Right->SetFrameUpdateTime(0.1f);

	mAirLeafLeft = new Animation();
	mAirLeafLeft->InitFrameByStartEnd(0, 1, 6, 1, true);
	mAirLeafLeft->SetIsLoop(false);
	mAirLeafLeft->SetFrameUpdateTime(0.1f);

	mAirLeafRight = new Animation();
	mAirLeafRight->InitFrameByStartEnd(0, 0, 6, 0, false);
	mAirLeafRight->SetIsLoop(false);
	mAirLeafRight->SetFrameUpdateTime(0.1f);

	mCurrentAnimation = mLeaf01Right;
}

void Leaf::Release()
{
	SafeDelete(mLeaf01Left);
	SafeDelete(mLeaf01Right);
	SafeDelete(mLeaf02Left);
	SafeDelete(mLeaf02Right);
	SafeDelete(mLeaf03Left);
	SafeDelete(mLeaf03Right);
	SafeDelete(mAirLeafLeft);
	SafeDelete(mAirLeafRight);
}

void Leaf::Update()
{
	Player* player = OBJECTMANAGER->GetPlayer();
	mDirection = player->GetDirection();

	if (mDirection == Direction::Left)
		mX = player->GetX() - player->GetSizeX() / 2.f;
	else
		mX = player->GetX() + player->GetSizeX() / 2.f;
	mY = player->GetY();

	mSizeX = mCurrentImage->GetFrameWidth() * 2.f;
	mSizeY = mCurrentImage->GetFrameHeight() * 2.f;
	mRect = RectMakeCenter((int)mX, (int)mY, (int)mSizeX, (int)mSizeY);

	MakeAttackBox(&mAttackBox);

	mCurrentAnimation->Update();
}

void Leaf::Render(HDC hdc)
{
	//CAMERAMANAGER->GetMainCamera()->RenderRectInCamera(hdc, mAttackBox);
	Player* player = OBJECTMANAGER->GetPlayer();

	CAMERAMANAGER->GetMainCamera()->ScaleFrameRender(hdc, mCurrentImage, mRect.left, mRect.top,
		mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY(), (int)mSizeX, (int)mSizeY);

	//	if(mIsActive)
	//		CAMERAMANAGER->GetMainCamera()->RenderRectInCamera(hdc, mAttackBox);
}

void Leaf::MakeAttackBox(RECT* attackBox)
{
	if (mCurrentAnimation == mLeaf01Left)
	{
		if (mCurrentAnimation->GetNowFrameX() >= 1 && mCurrentAnimation->GetNowFrameX() < 4)
		{
			mAttackBox = RectMakeCenter(mX-5, mY, 80, 60);
		}
		else
		{
			mAttackBox = RectMakeCenter(-2000, -2000, 2, 2);
		}
	}
	else if (mCurrentAnimation == mLeaf01Right)
	{
		if (mCurrentAnimation->GetNowFrameX() >= 3 && mCurrentAnimation->GetNowFrameX() < 6)
		{
			mAttackBox = RectMakeCenter(mX, mY, 80, 60);
		}
		else
		{
			mAttackBox = RectMakeCenter(-2000, -2000, 2, 2);
		}
	}
	else if (mCurrentAnimation == mLeaf02Left)
	{
		if (mCurrentAnimation->GetNowFrameX() >= 1 && mCurrentAnimation->GetNowFrameX() <= 3)
		{
			mAttackBox = RectMakeCenter(mX, mY, 80, 60);
		}
		else
		{
			mAttackBox = RectMakeCenter(-2000, -2000, 2, 2);
		}
	}
	else if (mCurrentAnimation == mLeaf02Right)
	{
		if (mCurrentAnimation->GetNowFrameX() >= 3 && mCurrentAnimation->GetNowFrameX() < 6)
		{
			mAttackBox = RectMakeCenter(mX, mY, 80, 60);
		}
		else
		{
			mAttackBox = RectMakeCenter(-2000, -2000, 2, 2);
		}
	}
	else if (mCurrentAnimation == mLeaf03Left)
	{
		if (mCurrentAnimation->GetNowFrameX() >= 1 && mCurrentAnimation->GetNowFrameX() < 5)
		{
			mAttackBox = RectMakeCenter(mX+10, mY, 90, 80);
		}
		else
		{
			mAttackBox = RectMakeCenter(-2000, -2000, 2, 2);
		}
	}
	else if (mCurrentAnimation == mLeaf03Right)
	{
		if (mCurrentAnimation->GetNowFrameX() >= 4 && mCurrentAnimation->GetNowFrameX() < 8)
		{
			mAttackBox = RectMakeCenter(mX, mY, 90, 80);
		}
		else
		{
			mAttackBox = RectMakeCenter(-2000, -2000, 2, 2);
		}
	}
	else if (mCurrentAnimation == mAirLeafLeft)
	{
		if (mCurrentAnimation->GetNowFrameX() >= 1 && mCurrentAnimation->GetNowFrameX() < 4)
		{
			mAttackBox = RectMakeCenter(mX, mY - 5, 90, 105);
		}
		else
		{
			mAttackBox = RectMakeCenter(-2000, -2000, 2, 2);
		}
	}
	else if (mCurrentAnimation == mAirLeafRight)
	{
		if (mCurrentAnimation->GetNowFrameX() >= 2 && mCurrentAnimation->GetNowFrameX() < 5)
		{
			mAttackBox = RectMakeCenter(mX, mY - 5, 90, 105);
		}
		else
		{
			mAttackBox = RectMakeCenter(-2000, -2000, 2, 2);
		}
	}
}

void Leaf::SetCurrentImageAnimation(int num, bool left)
{
	mIsActive = true;
	mCurrentAnimation->Stop();

	if (num == 1)
	{
		mCurrentImage = mLeafImage01;
		if (left)
			mCurrentAnimation = mLeaf01Left;
		else
			mCurrentAnimation = mLeaf01Right;
	}
	else if (num == 2)
	{
		mCurrentImage = mLeafImage02;
		if (left)
			mCurrentAnimation = mLeaf02Left;
		else
			mCurrentAnimation = mLeaf02Right;
	}
	else if (num == 3)
	{
		mCurrentImage = mLeafImage03;
		if (left)
			mCurrentAnimation = mLeaf03Left;
		else
			mCurrentAnimation = mLeaf03Right;
	}
	else if (num == 4)
	{
		mCurrentImage = mAirLeafImage;
		if (left)
			mCurrentAnimation = mAirLeafLeft;
		else
			mCurrentAnimation = mAirLeafRight;
	}

	mCurrentAnimation->Play();
}

void Leaf::SetStop()
{
	mIsActive = false;
	mCurrentAnimation->Stop();
}
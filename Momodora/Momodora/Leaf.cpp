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
	CAMERAMANAGER->GetMainCamera()->ScaleFrameRender(hdc, mCurrentImage, mRect.left, mRect.top,
		mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY(), (int)mSizeX, (int)mSizeY);
//	if(mIsActive)
//		CAMERAMANAGER->GetMainCamera()->RenderRectInCamera(hdc, mAttackBox);
}

void Leaf::MakeAttackBox(RECT* attackBox)
{
	mAttackBox = mRect; // ������ �� ���ư��� �����Ӻ��� ����ȭ ����

	if (mCurrentAnimation == mLeaf01Left)
	{

	}
	else if (mCurrentAnimation == mLeaf01Right)
	{

	}
	else if (mCurrentAnimation == mLeaf02Left)
	{

	}
	else if (mCurrentAnimation == mLeaf02Right)
	{

	}
	else if (mCurrentAnimation == mLeaf03Left)
	{

	}
	else if (mCurrentAnimation == mLeaf03Right)
	{

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

	mCurrentAnimation->Play();
}

void Leaf::SetStop()
{
	mIsActive = false;
	mCurrentAnimation->Stop();
}
#include "pch.h"
#include "Leaf.h"
#include "Animation.h"
#include "Camera.h"
#include "Player.h"

void Leaf::Init()
{
	mLeafImage01 = IMAGEMANAGER->FindImage(L"Leaf1");
	mLeafImage02 = IMAGEMANAGER->FindImage(L"Leaf2");
	mLeafImage03 = IMAGEMANAGER->FindImage(L"Leaf3");

	mLeaf01Left = new Animation();
	mLeaf01Left->InitFrameByStartEnd(0, 0, 6, 0, false);
	mLeaf01Left->SetIsLoop(false);
	mLeaf01Left->SetFrameUpdateTime(0.1f);

	mLeaf01Right = new Animation();
	mLeaf01Right->InitFrameByStartEnd(0, 0, 6, 0, true);
	mLeaf01Right->SetIsLoop(false);
	mLeaf01Right->SetFrameUpdateTime(0.1f);

	mLeaf02Left = new Animation();
	mLeaf02Left->InitFrameByStartEnd(0, 0, 6, 0, false);
	mLeaf02Left->SetIsLoop(false);
	mLeaf02Left->SetFrameUpdateTime(0.1f);

	mLeaf02Right = new Animation();
	mLeaf02Right->InitFrameByStartEnd(0, 0, 6, 0, true);
	mLeaf02Right->SetIsLoop(false);
	mLeaf02Right->SetFrameUpdateTime(0.1f);

	mLeaf03Left = new Animation();
	mLeaf03Left->InitFrameByStartEnd(0, 0, 10, 0, false);
	mLeaf03Left->SetIsLoop(false);
	mLeaf03Left->SetFrameUpdateTime(0.1f);

	mLeaf03Right = new Animation();
	mLeaf03Right->InitFrameByStartEnd(0, 0, 6, 0, true);
	mLeaf03Right->SetIsLoop(false);
	mLeaf03Right->SetFrameUpdateTime(0.1f);
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
	mX = player->GetX();
	mY = player->GetY();
	mDirection = player->GetDirection();

	//mCurrentImage;
	//mCurrentAnimation;
	//	float mSizeX = mCurrentImage->getframewidth() * 2;
	//	float mSizeY = mCurrentImage->getframeheight() * 2;
	//	RECT mRect;
	//	RECT mAttackBox; // 어택박스(공격)
	//	bool mIsActive; // 끝나면 false로

	//	Leaf1
	//		Leaf2
	//		Leaf3
}

void Leaf::Render(HDC hdc)
{
	CAMERAMANAGER->GetMainCamera()->ScaleFrameRender(hdc, mCurrentImage, mRect.left, mRect.top,
		mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY(), (int)mSizeX, (int)mSizeY);
}
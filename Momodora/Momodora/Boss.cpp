#include "pch.h"
#include "Boss.h"

#include "Image.h"
#include "Camera.h"
#include "Animation.h"
#include "ObjectManager.h"
#include "BossBullet.h"

void Boss::Init()
{
	// ������ ��ġ�� Body�� ���������� Rect�� �������� ���Ѵ�
	mName = "Boss";
	mX = WINSIZEX / 2;
	mY = WINSIZEY / 2;
	mSizeX = 630;//IMAGEMANAGER->FindImage(L"Boss_Chest")->GetWidth();	// �������� �� ���� * 2 (ũ�� �ι��)
	mSizeY = 960;//IMAGEMANAGER->FindImage(L"Boss_Chest")->GetHeight();

	ImageSetting();

	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	mHitBox = mChest.rc;

	mIsHit = false;
	mIsInvincibility = false;
	mHitMoveCount = 0;
	mHitFrameTime = 0.f;

	mLeftIdle = new Animation();
	mLeftIdle->InitFrameByStartEnd(0, 0, 4, 0, false);
	mLeftIdle->SetIsLoop(true);
	mLeftIdle->SetFrameUpdateTime(0.2f);

	// enemy ��ӹ޾Ƽ� ��
	mEnemyState = EnemyState::Idle;
	mDirection = Direction::Left;
	mCurrentAnimation = mLeftIdle;

	mPattern = AttackPattern::PatternIdle;		// �ƹ��͵� ���ϴ� ����
	mAttackTime = 0.f;
}

void Boss::Release()
{
}

void Boss::Update()
{
	if (INPUT->GetKeyDown(VK_RETURN))
	{
		if(!mIsInvincibility)
			mIsHit = true;
	}

	if (INPUT->GetKeyDown('7'))	// PatternBulletDown �׽�Ʈ
	{
		Pattern(AttackPattern::PatternBulletDown);
	}
	else if (INPUT->GetKeyDown('8'))	// PatternBulletUp �׽�Ʈ
	{
		Pattern(AttackPattern::PatternBulletUp);
	}
	else if (INPUT->GetKeyDown('9'))	// PatternBulletTarget �׽�Ʈ
	{
		Pattern(AttackPattern::PatternBulletTarget);
	}

	mCurrentAnimation->Update();		// �Ӹ� �ִϸ��̼�
	MotionFrame();

	vector<BossBullet*>::iterator iter = mVecBullet.begin();
	for (; iter != mVecBullet.end(); )
	{
		if (!((*iter)->GetY() - (*iter)->GetSizeY() <= WINSIZEY && (*iter)->GetY() + (*iter)->GetSizeY() >= 0.f))
		{
			(*iter)->SetIsActive(false);
			iter = mVecBullet.erase(iter);
		}
		else
			iter++;
	}

}

void Boss::Render(HDC hdc)
{
#ifdef DEBUG
	CAMERAMANAGER->GetMainCamera()->RenderRectInCamera(hdc, mBackHair.rc);
	CAMERAMANAGER->GetMainCamera()->RenderRectInCamera(hdc, mLeftArm.rc);
	CAMERAMANAGER->GetMainCamera()->RenderRectInCamera(hdc, mRightArm.rc);
	CAMERAMANAGER->GetMainCamera()->RenderRectInCamera(hdc, mBody.rc);
	CAMERAMANAGER->GetMainCamera()->RenderRectInCamera(hdc, mHead.rc);
	CAMERAMANAGER->GetMainCamera()->RenderRectInCamera(hdc, mChest.rc);
	CAMERAMANAGER->GetMainCamera()->RenderRectInCamera(hdc, mEyes.rc);
	CAMERAMANAGER->GetMainCamera()->RenderRectInCamera(hdc, mPupil.rc);

#endif // DEBUG


	CAMERAMANAGER->GetMainCamera()->ScaleRender(hdc, mBackHair.image, mBackHair.rc.left, mBackHair.rc.top, mBackHair.sizeX, mBackHair.sizeY);
	CAMERAMANAGER->GetMainCamera()->ScaleRender(hdc, mLeftArm.image, mLeftArm.rc.left, mLeftArm.rc.top, mLeftArm.sizeX, mLeftArm.sizeY);
	CAMERAMANAGER->GetMainCamera()->ScaleRender(hdc, mRightArm.image, mRightArm.rc.left, mRightArm.rc.top, mRightArm.sizeX, mRightArm.sizeY);
	CAMERAMANAGER->GetMainCamera()->ScaleRender(hdc, mBody.image, mBody.rc.left, mBody.rc.top, mBody.sizeX, mBody.sizeY);
	CAMERAMANAGER->GetMainCamera()->ScaleFrameRender(hdc, mHead.image, mHead.rc.left, mHead.rc.top, mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY(), mHead.sizeX, mHead.sizeY);
	CAMERAMANAGER->GetMainCamera()->ScaleRender(hdc, mChest.image, mChest.rc.left, mChest.rc.top, mChest.sizeX, mChest.sizeY);
	CAMERAMANAGER->GetMainCamera()->ScaleRender(hdc, mEyes.image, mEyes.rc.left, mEyes.rc.top, mEyes.sizeX, mEyes.sizeY);
	CAMERAMANAGER->GetMainCamera()->ScaleRender(hdc, mPupil.image, mPupil.rc.left, mPupil.rc.top, mPupil.sizeX, mPupil.sizeY);
}

void Boss::ImageSetting()
{
	// ����
	mBody.image = IMAGEMANAGER->FindImage(L"Boss_Body");
	mBody.sizeX = mBody.image->GetWidth() * 3;
	mBody.sizeY = mBody.image->GetHeight() * 3;
	mBody.x = 47 * 3 + mBody.sizeX / 2;
	mBody.y = 144 * 3 + mBody.sizeY / 2;
	mBody.rc = RectMakeCenter(mX - mSizeX / 2 + mBody.x, mY - mSizeY / 2 + mBody.y, mBody.sizeX, mBody.sizeY);
	mBody.move = true;
	mBody.moveTime = 0.f;
	mBody.moveCount = 0;

	// �޸Ӹ�
	mBackHair.image = IMAGEMANAGER->FindImage(L"Boss_BackHair");
	mBackHair.sizeX = mBackHair.image->GetWidth() * 3;
	mBackHair.sizeY = mBackHair.image->GetHeight() * 3;
	mBackHair.x = 7 * 3 + mBackHair.sizeX / 2;
	mBackHair.y = 60 * 3 + mBackHair.sizeY / 2;;
	mBackHair.rc = RectMakeCenter(mX - mSizeX / 2 + mBackHair.x, mY - mSizeY / 2 + mBackHair.y, mBackHair.sizeX, mBackHair.sizeY);
	mBackHair.move = true;
	mBackHair.moveTime = 0.f;
	mBackHair.moveCount = 0;

	// �Ӹ�
	mHead.image = IMAGEMANAGER->FindImage(L"Boss_Head");
	mHead.sizeX = mHead.image->GetWidth() * 3 / 5;
	mHead.sizeY = mHead.image->GetHeight() * 3;
	mHead.x = 5 * 3 + mHead.sizeX / 2;
	mHead.y = 5 * 3 + mHead.sizeY / 2;
	mHead.rc = RectMakeCenter(mX - mSizeX / 2 + mHead.x, mY - mSizeY / 2 + mHead.y, mHead.sizeX, mHead.sizeY);
	mHead.move = true;
	mHead.moveTime = 0.f;
	mHead.moveCount = 0;

	// ����
	mChest.image = IMAGEMANAGER->FindImage(L"Boss_Chest");
	mChest.sizeX = mChest.image->GetWidth() * 3;
	mChest.sizeY = mChest.image->GetHeight() * 3;
	mChest.x = 54 * 3 + mChest.sizeX / 2;
	mChest.y = 194 * 3 + mChest.sizeY / 2;
	mChest.rc = RectMakeCenter(mX - mSizeX / 2 + mChest.x, mY - mSizeY / 2 + mChest.y, mChest.sizeX, mChest.sizeY);
	mChest.move = true;
	mChest.moveTime = 0.f;
	mChest.moveCount = 0;

	// ����
	mEyes.image = IMAGEMANAGER->FindImage(L"Boss_Eyes");
	mEyes.sizeX = mEyes.image->GetWidth() * 3;
	mEyes.sizeY = mEyes.image->GetHeight() * 3;
	mEyes.x = 74 * 3 + mEyes.sizeX / 2;
	mEyes.y = 112 * 3 + mEyes.sizeY / 2;
	mEyes.rc = RectMakeCenter(mX - mSizeX / 2 + mEyes.x, mY - mSizeY / 2 + mEyes.y, mEyes.sizeX, mEyes.sizeY);
	mEyes.move = true;
	mEyes.moveTime = 0.f;
	mEyes.moveCount = 0;
	
	// ������
	mPupil.image = IMAGEMANAGER->FindImage(L"Boss_Pupil");
	mPupil.sizeX = mPupil.image->GetWidth() * 3;
	mPupil.sizeY = mPupil.image->GetHeight() * 3;
	mPupil.x = 80 * 3 + mPupil.sizeX / 2;
	mPupil.y = 114 * 3 + mPupil.sizeY / 2;
	mPupil.rc = RectMakeCenter(mX - mSizeX / 2 + mPupil.x, mY - mSizeY / 2 + mPupil.y, mPupil.sizeX, mPupil.sizeY);
	mPupil.move = true;
	mPupil.moveTime = 0.f;
	mPupil.moveCount = 0;

	// ����
	mLeftArm.image = IMAGEMANAGER->FindImage(L"Boss_LeftArm");
	mLeftArm.sizeX = mLeftArm.image->GetWidth() * 3;
	mLeftArm.sizeY = mLeftArm.image->GetHeight() * 3;
	mLeftArm.x = 45 * 3 + mLeftArm.sizeX / 2;
	mLeftArm.y = 175 * 3 + mLeftArm.sizeY / 2;
	mLeftArm.rc = RectMakeCenter(mX - mSizeX / 2 + mLeftArm.x, mY - mSizeY / 2 + mLeftArm.y, mLeftArm.sizeX, mLeftArm.sizeY);
	mLeftArm.move = true;
	mLeftArm.moveTime = 0.f;
	mLeftArm.moveCount = 0;

	// ������
	mRightArm.image = IMAGEMANAGER->FindImage(L"Boss_RightArm");
	mRightArm.sizeX = mRightArm.image->GetWidth() * 3;
	mRightArm.sizeY = mRightArm.image->GetHeight() * 3;
	mRightArm.x = 123 * 3 + mRightArm.sizeX / 2;
	mRightArm.y = 175 * 3 + mRightArm.sizeY / 2;
	mRightArm.rc = RectMakeCenter(mX - mSizeX / 2 + mRightArm.x, mY - mSizeY / 2 + mRightArm.y, mRightArm.sizeX, mRightArm.sizeY);
	mRightArm.move = true;
	mRightArm.moveTime = 0.f;
	mRightArm.moveCount = 0;
}

void Boss::MotionFrame()
{
	// �Ӹ�, ��
	if (mHead.move)		// true�� �� �������� ���
	{
		mHead.moveTime += TIME->DeltaTime();

		if (mHead.moveCount < 3)
		{
			if (mHead.moveTime >= 0.3f)
			{
				mHead.y -= 1;
				mBackHair.y -= 1;
				mEyes.y -= 1;
				mPupil.y -= 1;
				mHead.moveTime = 0.f;
				mHead.moveCount++;
			}
		}
		else
		{
			if (mHead.moveTime >= 0.5f)
			{
				mHead.move = false;
				mHead.moveTime = 0.f;
				mHead.moveCount = 0;
			}
		}
	}
	else
	{
		mHead.moveTime += TIME->DeltaTime();

		if (mHead.moveCount < 3)
		{
			if (mHead.moveTime >= 0.3f)
			{
				mHead.y += 1;
				mBackHair.y += 1;
				mEyes.y += 1;
				mPupil.y += 1;
				mHead.moveTime = 0.f;
				mHead.moveCount++;
			}
		}
		else
		{
			if (mHead.moveTime >= 0.5f)
			{
				mHead.move = true;
				mHead.moveTime = 0.f;
				mHead.moveCount = 0;
			}
		}
	}

	mHead.rc = RectMakeCenter(mX - mSizeX / 2 + mHead.x, mY - mSizeY / 2 + mHead.y, mHead.sizeX, mHead.sizeY);
	mBackHair.rc = RectMakeCenter(mX - mSizeX / 2 + mBackHair.x, mY - mSizeY / 2 + mBackHair.y, mBackHair.sizeX, mBackHair.sizeY);
	mEyes.rc = RectMakeCenter(mX - mSizeX / 2 + mEyes.x, mY - mSizeY / 2 + mEyes.y, mEyes.sizeX, mEyes.sizeY);
	mPupil.rc = RectMakeCenter(mX - mSizeX / 2 + mPupil.x, mY - mSizeY / 2 + mPupil.y, mPupil.sizeX, mPupil.sizeY);

	// ����
	if (mChest.move)		// true�� �� �������� ���
	{
		mChest.moveTime += TIME->DeltaTime();

		if (mChest.moveCount < 2)
		{
			if (mChest.moveTime >= 0.3f)
			{
				mChest.y -= 2;
				mChest.moveTime = 0.f;
				mChest.moveCount++;
			}
		}
		else
		{
			if (mChest.moveTime >= 0.5f)
			{
				mChest.move = false;
				mChest.moveTime = 0.f;
				mChest.moveCount = 0;
			}
		}
	}
	else
	{
		mChest.moveTime += TIME->DeltaTime();

		if (mChest.moveCount < 2)
		{
			if (mChest.moveTime >= 0.3f)
			{
				mChest.y += 2;
				mChest.moveTime = 0.f;
				mChest.moveCount++;
			}
		}
		else
		{
			if (mChest.moveTime >= 1.f)
			{
				mChest.move = true;
				mChest.moveTime = 0.f;
				mChest.moveCount = 0;
			}
		}
	}

	if (mIsHit)		// �ǰ� ����
	{
		mChest.y -= 10;
		mIsHit = false;
		mIsInvincibility = true;
	}
	
	if (mIsInvincibility)	// �ǰ� �� ���� �ð�
	{
		mHitFrameTime += TIME->DeltaTime();

		if (mHitFrameTime >= 0.3f)
		{
			mHitMoveCount++;
			mHitFrameTime = 0.f;
			mChest.y += 5;

			if (mHitMoveCount >= 2)
			{
				mIsInvincibility = false;
				mHitMoveCount = 0;
			}
		}
	}

	mChest.rc = RectMakeCenter(mX - mSizeX / 2 + mChest.x, mY - mSizeY / 2 + mChest.y, mChest.sizeX, mChest.sizeY);

	// ��
	if (mLeftArm.move)		// true�� �� �������� ���
	{
		mLeftArm.moveTime += TIME->DeltaTime();

		if (mLeftArm.moveCount < 2)
		{
			if (mLeftArm.moveTime >= 0.3f)
			{
				mLeftArm.y -= 2;
				mRightArm.y -= 2;
				mLeftArm.moveTime = 0.f;
				mLeftArm.moveCount++;
			}
		}
		else
		{
			if (mLeftArm.moveTime >= 0.5f)
			{
				mLeftArm.move = false;
				mLeftArm.moveTime = 0.f;
				mLeftArm.moveCount = 0;
			}
		}
	}
	else
	{
		mLeftArm.moveTime += TIME->DeltaTime();

		if (mLeftArm.moveCount < 2)
		{
			if (mLeftArm.moveTime >= 0.3f)
			{
				mLeftArm.y += 2;
				mRightArm.y += 2;
				mLeftArm.moveTime = 0.f;
				mLeftArm.moveCount++;
			}
		}
		else
		{
			if (mLeftArm.moveTime >= 1.f)
			{
				mLeftArm.move = true;
				mLeftArm.moveTime = 0.f;
				mLeftArm.moveCount = 0;
			}
		}
	}

	mLeftArm.rc = RectMakeCenter(mX - mSizeX / 2 + mLeftArm.x, mY - mSizeY / 2 + mLeftArm.y, mLeftArm.sizeX, mLeftArm.sizeY);
	mRightArm.rc = RectMakeCenter(mX - mSizeX / 2 + mRightArm.x, mY - mSizeY / 2 + mRightArm.y, mRightArm.sizeX, mRightArm.sizeY);
}

void Boss::Pattern(AttackPattern pattern)
{
	switch (pattern)
	{
	case AttackPattern::PatternIdle:
		break;
	case AttackPattern::PatternBulletDown:
		for (int i = 0; i < 4; ++i)
		{
			BossBullet* bullet = new BossBullet;
			bullet->Init();
			bullet->SetX(WINSIZEX / 5 * (i + 1));
			bullet->SetY(WINSIZEY / 2);
			bullet->SetAngle(PI * 1.5f);		// �׳� �Ʒ��� ��������
			bullet->SetPattern(BulletPattern::PatternBulletDown);
			bullet->SetObject();
			mVecBullet.push_back(bullet);
			OBJECTMANAGER->AddObject(ObjectLayer::EnemyProjectile, bullet);
		}
		break;
	case AttackPattern::PatternBulletUp:
		for (int i = 0; i < 2; ++i)
		{
			float angle = rand() % 30 / 10.f;
			BossBullet* bullet = new BossBullet;
			bullet->Init();
			bullet->SetX(OBJECTMANAGER->FindObject("Player")->GetX());
			bullet->SetY(WINSIZEY);
			bullet->SetAngle(angle);
			bullet->SetPattern(BulletPattern::PatternBulletUp);
			bullet->SetObject();
			mVecBullet.push_back(bullet);
			OBJECTMANAGER->AddObject(ObjectLayer::EnemyProjectile, bullet);
		}
		break;
	case AttackPattern::PatternBulletTarget:
		for (int i = 0; i < 8; ++i)
		{
			BossBullet* bullet = new BossBullet;

			if (i % 2 == 0)		// ���ʼ� �����ϴ� �ֵ�
			{
				bullet->Init();
				bullet->SetX(-(bullet->GetSizeX()) * (i / 2 + i / 2));
				bullet->SetY(WINSIZEY / 3);
				bullet->SetAngle(0.f);
				bullet->SetPattern(BulletPattern::PatternBulletTarget);
				bullet->SetObject();
			}
			else				// �����ʼ� �����ϴ� �ֵ�
			{
				bullet->Init();
				bullet->SetX(WINSIZEX + (bullet->GetSizeX()) * (i / 2 + i / 2));
				bullet->SetY(WINSIZEY / 3 + bullet->GetSizeY() / 2);
				bullet->SetAngle(PI);
				bullet->SetPattern(BulletPattern::PatternBulletTarget);
				bullet->SetObject();
			}
			mVecBullet.push_back(bullet);
			OBJECTMANAGER->AddObject(ObjectLayer::EnemyProjectile, bullet);
		}
		break;
	}
}
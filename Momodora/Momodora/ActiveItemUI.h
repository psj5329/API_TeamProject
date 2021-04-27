#pragma once
#include "UI.h"

class Image;
class ActiveItemUI : public UI
{
	Image* mItemImage;
	Image* mItemCountImage;

	int mItemMaxCount;
	int mItemCount;

	float mItemSizeX;
	float mItemSizeY;
	float mItemCountSizeX;
	float mItemCountSizeY;

public:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

public:
	void SetItem(wstring name) { mItemImage = IMAGEMANAGER->FindImage(name); }
	void SetItemCount(int count) { mItemCount = count; }

	int GetItemCount() { return mItemCount; }
};
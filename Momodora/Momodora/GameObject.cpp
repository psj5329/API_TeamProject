#include "pch.h"
#include "GameObject.h"

GameObject::GameObject()
	: mIsActive(true), mIsDestroy(false)
{
}

GameObject::GameObject(float x, float y)
	:mX(x), mY(y), mIsActive(true), mIsDestroy(false)
{
}
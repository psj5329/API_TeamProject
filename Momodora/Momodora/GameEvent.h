#pragma once

//interface class : ���������Լ����� ������ �ִ� Ŭ����
class IEvent
{
public:
	//�ڵ������� ���� �����Լ��� �ȴ�
	virtual void Start() = 0;	//�̺�Ʈ ������ �� ȣ��Ǵ� �Լ�
	//�����ϴٰ� ������ return true
	virtual bool Update() = 0;	//�̺�Ʈ ������Ʈ �Լ�
	virtual void Render(HDC hdc) = 0;
};

class IChangeCameraTargetEvent : public IEvent
{
	class GameObject* mTarget;
public:
	IChangeCameraTargetEvent(class GameObject* target);

	void Start()override;
	bool Update()override;
	void Render(HDC hdc)override;
};

class IDelayEvent : public IEvent
{
	float mCurrentTime;
	float mDelayTime;
public:
	IDelayEvent(float delayTime);

	void Start()override;
	bool Update()override;
	void Render(HDC hdc)override;
};

class IScriptEvent : public IEvent
{
	Image* mImage;
	float mCurrentTime;
	float mDelayTime;
	float mShakeX;
	float mShakeY;
public:
	IScriptEvent(wstring image);

	void Start()override;
	bool Update()override;
	void Render(HDC hdc)override;
};

class IEraseEvent : public IEvent
{
	Image* mImage1;
	Image* mImage2;
	float mSize;
	float mDelayTime;
	vector<POINT> mVecEraseCenter;
	vector<POINT> mVecBackEraseCenter;

public:
	IEraseEvent(Image* image1, Image* image2, float r, float time);

	void Start()override;
	bool Update()override;
	void Render(HDC hdc)override;
};

//class IPlayFunctionEvent : public IEvent
//{
//public:
//	IPlayFunctionEvent();
//
//	void Start()override;
//	bool Update()override;
//	void Render(HDC hdc)override;
//};

//class IMoveGameObject : public IEvent
//{
//	class GameObject* mObject;
//	float mTargetX;
//	float mTargetY;
//	float mSpeedX;
//	float mSpeedY;
//public:
//	IMoveGameObject(GameObject* object, GameObject* target);
//	IMoveGameObject(GameObject* object, float x, float y);
//
//	void Start()override;
//	bool Update()override;
//	void Render(HDC hdc)override;
//};
//
//class IChangeAnimation : public IEvent
//{
//	class GameObject* mObject;
//	class Animation* mAnimation;
//public:
//	IChangeAnimation(GameObject* object, Animation* animation);
//
//	void Start()override;
//	bool Update()override;
//	void Render(HDC hdc)override;
//};
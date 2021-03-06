#pragma once

//interface class : 순수가상함수만을 가지고 있는 클래스
class IEvent
{
public:
	//자동적으로 순수 가상함수가 된다
	virtual void Start() = 0;	//이벤트 시작할 때 호출되는 함수
	//실행하다가 끝나면 return true
	virtual bool Update() = 0;	//이벤트 업데이트 함수
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

class IMoveCameraEvent : public IEvent
{
	float mX;
	float mY;
public:
	IMoveCameraEvent(float x, float y);

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

class IMoveGameObject : public IEvent
{
	class GameObject* mObject;
	float mTargetX;
	float mTargetY;
	float mSpeedX;
	float mSpeedY;
public:
	IMoveGameObject(GameObject* object, GameObject* target);
	IMoveGameObject(GameObject* object, float x, float y);
	IMoveGameObject(GameObject* object, float x, float y, float speedX, float speedY);

	void Start()override;
	bool Update()override;
	void Render(HDC hdc)override;
};

class IChangeAnimation : public IEvent
{
	class GameObject* mObject;
	class Animation* mAnimation;
public:
	IChangeAnimation(GameObject* object, Animation* animation);

	void Start()override;
	bool Update()override;
	void Render(HDC hdc)override;
};

class IChangeImage : public IEvent
{
	Image* mImage1;
	wstring mName;

public:
	IChangeImage(Image** image1, wstring name);

	void Start()override;
	bool Update()override;
	void Render(HDC hdc)override;
};

class IObjectStop : public IEvent
{
	bool mIsStop;

public:
	IObjectStop(bool b);

	void Start()override;
	bool Update()override;
	void Render(HDC hdc)override;
};



class IChangeImage2 : public IEvent
{
	Image* mImage1;
	wstring mName;

public:
	IChangeImage2(Image** image1, wstring name);

	void Start()override;
	bool Update()override;
	void Render(HDC hdc)override;
};

class IPlaySoundEffect : public IEvent
{
	wstring mName;
	wstring mPath;
	float mDelay;
	float mTime;
	float mVolume;

public:
	IPlaySoundEffect(wstring name, wstring path, float volume, float delay);

	void Start()override;
	bool Update()override;
	void Render(HDC hdc)override;
};
#pragma once

class Time
{
	_Singleton(Time)

private:
	bool mIsHightHardware;
	float mTimeScale;
	float mDeltaTime;

	__int64 mCurrentTime;
	__int64 mLastTime;
	__int64 mPeriodFrequency;

	unsigned long mFrameRate;
	unsigned long mFPSFrameCount;
	float mFPSTimeElapsed;
	float mWorldTime;

	bool mIsStart;
private:
	Time();

	void Tick(float lockFPS = 60.0f);
	void StartClock();
public:
	void Update();

	inline void Start() { mIsStart = true; StartClock(); }
	inline void Stop() { mIsStart = false; }
	inline unsigned long GetmFrameRate() const { return mFrameRate; }
	inline float DeltaTime()const { return this->mDeltaTime; }
	inline float GetWorldTime()const { return this->mWorldTime; }
	inline float GetTimeScale()const { return this->mTimeScale; }
	inline void SetTimeScale(float scale) { this->mTimeScale = scale; }
};

#define TIME Time::GetInstance()
#pragma once
#define MaxChannelBuffer 50	//최대 채널 수

class SoundManager final
{
	_Singleton(SoundManager)

private:
	struct ChannelInfo
	{
		wstring SoundName;
		FMOD::Channel* Channel;
	};
	typedef map<wstring, FMOD::Sound*>::iterator SoundIter;

private:
	map<wstring, FMOD::Sound*> mSoundList;
	vector<ChannelInfo> mActiveChannels;		//현재 활성화 되어 있는 채널
	FMOD::System* mSystem;

private:
	SoundManager();
	~SoundManager();

public:
	void Update();
	void LoadFromFile(const wstring& keyName, const wstring& fileName, bool isLoop);
	void Play(const wstring& keyName, float volume);
	void Pause(const wstring& keyName);
	void Stop(const wstring& keyName);
};

#define SOUNDMANAGER SoundManager::GetInstance()
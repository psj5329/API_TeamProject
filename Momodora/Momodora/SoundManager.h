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

	//void SetVolume(const wstring& keyName, float volume); // 추가구현(옵션?)
	//float GetVolume(const wstring& keyName); // 추가구현(옵션?)
	//void SetPosition(const wstring& keyName, float time); // 필요없을 것 같음
	//float GetPosition(const wstring& keyName); // 필요없을 것 같음
};

#define SOUNDMANAGER SoundManager::GetInstance()
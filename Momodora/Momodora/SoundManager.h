#pragma once
#define MaxChannelBuffer 50	//�ִ� ä�� ��

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
	vector<ChannelInfo> mActiveChannels;		//���� Ȱ��ȭ �Ǿ� �ִ� ä��
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

	//void SetVolume(const wstring& keyName, float volume); // �߰�����(�ɼ�?)
	//float GetVolume(const wstring& keyName); // �߰�����(�ɼ�?)
	//void SetPosition(const wstring& keyName, float time); // �ʿ���� �� ����
	//float GetPosition(const wstring& keyName); // �ʿ���� �� ����
};

#define SOUNDMANAGER SoundManager::GetInstance()
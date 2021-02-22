#include "pch.h"
#include "SoundManager.h"
_Singleton_NULL(SoundManager)

using namespace FMOD;

SoundManager::SoundManager()
{
	FMOD::System_Create(&mSystem);
	mSystem->init(MaxChannelBuffer, FMOD_INIT_NORMAL, NULL);
}

SoundManager::~SoundManager()
{
	for (int i = 0; i < mActiveChannels.size(); ++i)
	{
		mActiveChannels[i].Channel->stop();
	}

	for (SoundIter iter = mSoundList.begin(); iter != mSoundList.end(); ++iter)
	{
		iter->second->release();
	}

	mSystem->release();
}

void SoundManager::Update()
{
	mSystem->update();

	bool isPaused;
	bool isPlaying;
	for (int i = 0; i < mActiveChannels.size(); ++i)
	{
		mActiveChannels[i].Channel->getPaused(&isPaused);
		if (isPaused)return;
		mActiveChannels[i].Channel->isPlaying(&isPlaying);
		if (isPlaying == false)
		{
			mActiveChannels[i].Channel->stop();
			mActiveChannels.erase(mActiveChannels.begin() + i);
			--i;
		}
	}
}

void SoundManager::LoadFromFile(const wstring & keyName, const wstring & fileName, bool isLoop)
{
	SoundIter iter = mSoundList.find(keyName);
	if (iter != mSoundList.end())
		return;

	string strFileName;
	strFileName.assign(fileName.begin(), fileName.end());

	Sound* sound = nullptr;

	if (isLoop)
	{
		mSystem->createStream(strFileName.c_str(), FMOD_LOOP_NORMAL, NULL, &sound);
	}
	else
	{
		mSystem->createSound(strFileName.c_str(), FMOD_DEFAULT, NULL, &sound);
	}

	if (sound != nullptr)
	{
		mSoundList.insert(make_pair(keyName, sound));
	}
}

void SoundManager::Play(const wstring & keyName, float volume)
{
	for (int i = 0; i < mActiveChannels.size(); ++i)
	{
		if (mActiveChannels[i].SoundName == keyName)
		{
			bool isPaused;
			mActiveChannels[i].Channel->getPaused(&isPaused);
			if (isPaused)
			{
				mActiveChannels[i].Channel->setPaused(false);
				return;
			}
		}
	}

	if (mActiveChannels.size() >= MaxChannelBuffer)
		return;

	SoundIter iter = mSoundList.find(keyName);
	if (iter == mSoundList.end())
		return;

	Channel* channel;
	Sound* sound = iter->second;

	mSystem->playSound(FMOD_CHANNEL_FREE, sound, false, &channel);
	channel->setVolume(volume);

	ChannelInfo channelInfo;
	channelInfo.Channel = channel;
	channelInfo.SoundName = keyName;
	mActiveChannels.push_back(channelInfo);
}

void SoundManager::Pause(const wstring & keyName)
{
	for (int i = 0; i < mActiveChannels.size(); ++i)
	{
		if (mActiveChannels[i].SoundName == keyName)
		{
			mActiveChannels[i].Channel->setPaused(true);
			break;
		}
	}
}

void SoundManager::Stop(const wstring & keyName)
{
	for (int i = 0; i < mActiveChannels.size(); ++i)
	{
		if (mActiveChannels[i].SoundName == keyName)
		{
			mActiveChannels[i].Channel->stop();
			mActiveChannels.erase(mActiveChannels.begin() + i);
			break;
		}
	}
}
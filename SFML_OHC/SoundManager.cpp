#include "pch.h"
#include "SoundManager.h"


void SoundManager::Initialize(int totalChannels)
{
}

void SoundManager::Release()
{
}

void SoundManager::Update(float dt)
{
	auto it = m_PlayingSfx.begin();
	while (it != m_PlayingSfx.end())
	{
		if ((*it)->getStatus() == sf::Sound::Stopped)
		{
			m_WaitingSfx.push_back(*it);
			m_PlayingSfx.erase(it);
		}
		else
		{
			++it;
		}
	}


}

void SoundManager::PlayBgm(std::string id, bool loop, bool fadeIn, float fadeTime, float startvolume)
{
	auto buff = 
	m_BgmData.duration = buff.getDuration().asSeconds();
	if (fadeIn)
	{
		SetFadeInSpeed(m_BgmData, )
	}
	PlayBgm();
}

void SoundManager::PlayBgm(sf::SoundBuffer& buffer, bool loop, bool fadeIn, float fadeTime, float startvolume)
{
}

void SoundManager::StopBgm(bool fadeOut, float fadeTime, float endvolume)
{
}

void SoundManager::PlaySfx(std::string id, bool loop)
{
}

void SoundManager::PlaySfx(sf::SoundBuffer& buffer, bool loop)
{
}

void SoundManager::SetFadeInSpeed(SoundData& sound, float fadeTime, float start)
{
	if (sound.fadeInSpeed > 0 || start > sound.defaultVolume)return;
	sound.defaultVolume = m_BgmVolume;
	
	if (sound.duration < fadeTime)
		fadeTime = sound.duration;
	sound.fadeInSpeed = (sound.defaultVolume - start) / fadeTime;
}

void SoundManager::SetFadeOutSpeed(SoundData& sound, float duration, float end)
{
	if (sound.fadeOutSpeed > 0 || end > sound.defaultVolume)return;
	if (sound.duration < duration)
		duration = sound.duration;
	sound.fadeOutVolume = end;
	sound.fadeOutSpeed = (sound.defaultVolume - end) / duration;
}
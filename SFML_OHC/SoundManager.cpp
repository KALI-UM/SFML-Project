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
	PlayBgm(*ResourceManager<sf::SoundBuffer>::GetInstance()->GetByFilepath(id),
		loop,
		fadeIn,
		fadeTime,
		startvolume);
}

void SoundManager::PlayBgm(sf::SoundBuffer& buffer, bool loop, bool fadeIn, float fadeTime, float startvolume)
{
	m_Bgm.stop();
	m_BgmData.duration = buffer.getDuration().asSeconds();

	if (fadeIn)
	{
		SetFadeInSpeed(m_BgmData, fadeTime, startvolume);
		m_Bgm.setVolume(startvolume * GM->GetGlobalVolume());
	}
	else
	{
		m_Bgm.setVolume(m_BgmVolume * GM->GetGlobalVolume());
	}

	m_Bgm.setLoop(loop);
	m_Bgm.setBuffer(buffer);
	m_Bgm.play();
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

void SoundManager::SetFadeInSpeed(SoundData& data, float fadeTime, float start)
{
	data.defaultVolume = m_BgmVolume;

	if (data.duration < fadeTime)
		fadeTime = data.duration;
	data.fadeInSpeed = (data.defaultVolume - start) / fadeTime;
}

void SoundManager::SetFadeOutSpeed(SoundData& data, float duration, float end)
{
	if (data.fadeOutSpeed > 0 || end > data.defaultVolume)return;
	if (data.duration < duration)
		duration = data.duration;
	data.fadeOutVolume = end;
	data.fadeOutSpeed = (data.defaultVolume - end) / duration;
}
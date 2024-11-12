#include "pch.h"
#include "SoundObject.h"

SoundObject::SoundObject(const std::string& filepath, float volume)
	:m_IsValid(false), m_DefaultVolume(volume* GM->GetGlobalVolume()), m_SoundDuration(0)
{
	sf::SoundBuffer* soundbuff = ResourceManager<sf::SoundBuffer>::GetInstance()->GetByFilepath(filepath);
	if (soundbuff)
	{
		SetIsValid(true);
		m_Sound.setBuffer(*soundbuff);
		m_Sound.setVolume(m_DefaultVolume);
		m_SoundDuration = m_Sound.getBuffer()->getDuration().asSeconds();
	}
}

SoundObject::SoundObject(const SoundObject& other)
	:m_IsValid(false), m_DefaultVolume(other.m_DefaultVolume),m_SoundDuration(other.m_SoundDuration)
{
	if (other.m_Sound.getBuffer())
	{
		SetIsValid(true);
		m_Sound = other.m_Sound;
		m_Sound.setVolume(m_DefaultVolume * GM->GetGlobalVolume());
	}
}

SoundObject::SoundObject(SoundObject&& other)
	:m_IsValid(other.m_IsValid), m_DefaultVolume(other.m_DefaultVolume), m_SoundDuration(other.m_SoundDuration)
{
	if (other.m_Sound.getBuffer())
	{
		m_Sound = other.m_Sound;
	}
	else
	{
		other.SetIsValid(false);
	}
}

SoundObject::~SoundObject()
{
}

void SoundObject::Play()
{
	m_Sound.play();
}

void SoundObject::Pause()
{
	m_Sound.pause();
}

void SoundObject::Stop()
{
	if (GetIsPlaying())
		m_Sound.stop();
}

void SoundObject::SetLoop(bool loop)
{
	m_Sound.setLoop(loop);
}

bool SoundObject::GetIsPlaying() const
{
	return ((int)m_Sound.getStatus() == (int)sf::Sound::Status::Playing);
}


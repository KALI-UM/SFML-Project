#include "pch.h"
#include "SoundObject.h"

SoundObject::SoundObject(const std::string& filepath, float volume, SoundType type)
	:m_IsValid(false), m_Type(type), m_DefaultVolume(volume* GM->GetGlobalVolume()), m_FadeInSpeed(-1), m_FadeOutSpeed(-1), m_FadeOutVolume(m_DefaultVolume)
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
	:m_IsValid(false), m_Type(other.m_Type), m_DefaultVolume(other.m_DefaultVolume), m_FadeInSpeed(-1), m_FadeOutSpeed(-1), m_FadeOutVolume(m_DefaultVolume), m_SoundDuration(other.m_SoundDuration)
{
	if (other.m_Sound.getBuffer())
	{
		SetIsValid(true);
		m_Sound = other.m_Sound;
		m_Sound.setVolume(m_DefaultVolume * GM->GetGlobalVolume());
	}
}

SoundObject::SoundObject(SoundObject&& other)
	:m_IsValid(other.m_IsValid), m_Type(other.m_Type), m_DefaultVolume(other.m_DefaultVolume), m_FadeInSpeed(other.m_FadeInSpeed), m_FadeOutSpeed(other.m_FadeOutSpeed), m_FadeOutVolume(other.m_FadeOutVolume), m_SoundDuration(other.m_SoundDuration)
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

void SoundObject::Play(bool fadeIn, float duration, float startvolume)
{
	if (m_Type == SoundType::BGM)
	{
		if (!GetIsPlaying())
		{
			if (fadeIn)
			{
				if (startvolume < 0.1f)startvolume = 0.1f;
				m_FadeInSpeed = (m_Sound.getVolume() - startvolume) / duration;
			}
			m_Sound.setVolume(startvolume);
			m_Sound.play();
		}
	}
	else
	{
		m_Sound.play();
	}
}

void SoundObject::Pause(bool fadeOut, float duration, float endvolume)
{
	m_Sound.pause();
}

void SoundObject::Stop(bool fadeOut, float duration, float endvolume)
{
	if (GetIsPlaying())
		m_Sound.stop();
}

void SoundObject::SetLoop(bool loop)
{
	m_Sound.setLoop(loop);
}

void SoundObject::Update(float dt)
{
	dt = FM->GetRealDeltaTime();

	if (m_FadeInSpeed > 0)
	{
		float currv = m_Sound.getVolume() + dt * m_FadeInSpeed;
		if (currv > m_DefaultVolume)
		{
			m_Sound.setVolume(m_DefaultVolume);
			m_FadeInSpeed = -1;
		}
		else
		{
			m_Sound.setVolume(currv);
		}
	}

	if (m_FadeOutSpeed > 0)
	{
		float currv = m_Sound.getVolume() - dt * m_FadeOutSpeed;
		if (currv < m_FadeOutVolume)
		{
			Stop();
			m_Sound.setVolume(m_DefaultVolume);
			m_FadeOutSpeed = -1;
		}
		else
		{
			m_Sound.setVolume(currv);
		}
	}
}

bool SoundObject::GetIsPlaying() const
{
	return ((int)m_Sound.getStatus() == (int)sf::Sound::Status::Playing);
}

void SoundObject::SetFadeInSpeed(float duration, float start)
{
	start *= GM->GetGlobalVolume();
	if (m_FadeInSpeed > 0 || start > m_DefaultVolume)return;
	if (m_SoundDuration < duration)
		duration = m_SoundDuration;
	m_FadeInSpeed = (m_DefaultVolume - start) / duration;
}

void SoundObject::SetFadeOutSpeed(float duration, float end)
{
	end *= GM->GetGlobalVolume();
	if (m_FadeOutSpeed > 0 || end > m_DefaultVolume)return;
	if (m_SoundDuration < duration)
		duration = m_SoundDuration;
	m_FadeOutVolume = end;
	m_FadeOutSpeed = (m_DefaultVolume - end) / duration;
}

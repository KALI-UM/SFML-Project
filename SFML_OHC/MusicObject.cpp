#include "pch.h"
#include "MusicObject.h"

MusicObject::MusicObject(const std::string& filepath, float volume)
	:m_IsValid(false), m_DefaultVolume(volume* GM->GetGlobalVolume()), m_FadeInSpeed(-1), m_FadeOutSpeed(-1), m_FadeOutVolume(m_DefaultVolume)
{
	if (m_Music.openFromFile(filepath))
	{
		SetIsValid(true);
		m_Music.setVolume(m_DefaultVolume);
		m_MusicDuration = m_Music.getDuration().asSeconds();
	}
}

MusicObject::~MusicObject()
{
}

void MusicObject::Play(bool fadeIn, float duration, float startvolume)
{
	if (!GetIsPlaying())
	{
		if (fadeIn)
		{
			if (startvolume < 0.1f)startvolume = 0.1f;
			m_FadeInSpeed = (m_Music.getVolume() - startvolume) / duration;
		}
		m_Music.setVolume(startvolume);
		m_Music.play();
	}

}

void MusicObject::Pause(bool fadeOut, float duration, float endvolume)
{
	m_Music.pause();
}

void MusicObject::Stop(bool fadeOut, float duration, float endvolume)
{
	if (GetIsPlaying())
		m_Music.stop();
}

void MusicObject::SetLoop(bool loop)
{
	m_Music.setLoop(loop);
}

void MusicObject::Update(float dt)
{
	dt = FM->GetRealDeltaTime();

	if (m_FadeInSpeed > 0)
	{
		float currv = m_Music.getVolume() + dt * m_FadeInSpeed;
		if (currv > m_DefaultVolume)
		{
			m_Music.setVolume(m_DefaultVolume);
			m_FadeInSpeed = -1;
		}
		else
		{
			m_Music.setVolume(currv);
		}
	}

	if (m_FadeOutSpeed > 0)
	{
		float currv = m_Music.getVolume() - dt * m_FadeOutSpeed;
		if (currv < m_FadeOutVolume)
		{
			Stop();
			m_Music.setVolume(m_DefaultVolume);
			m_FadeOutSpeed = -1;
		}
		else
		{
			m_Music.setVolume(currv);
		}
	}
}

bool MusicObject::GetIsPlaying() const
{
	return ((int)m_Music.getStatus() == (int)sf::Sound::Status::Playing);
}

void MusicObject::SetFadeInSpeed(float duration, float start)
{
	start *= GM->GetGlobalVolume();
	if (m_FadeInSpeed > 0 || start > m_DefaultVolume)return;
	if (m_MusicDuration < duration)
		duration = m_MusicDuration;
	m_FadeInSpeed = (m_DefaultVolume - start) / duration;
}

void MusicObject::SetFadeOutSpeed(float duration, float end)
{
	end *= GM->GetGlobalVolume();
	if (m_FadeOutSpeed > 0 || end > m_DefaultVolume)return;
	if (m_MusicDuration < duration)
		duration = m_MusicDuration;
	m_FadeOutVolume = end;
	m_FadeOutSpeed = (m_DefaultVolume - end) / duration;
}

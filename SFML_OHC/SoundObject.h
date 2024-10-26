#pragma once
#include "SFML/Audio.hpp"

namespace sf
{
	class Sound;
}

enum class SoundType
{
	Effect,	//fade in/out 불가
	BGM		//fade in/out 가능	
};

class SoundObject
{
public:
	SoundObject(const std::string& filepath, float volume, SoundType type);
	SoundObject(const SoundObject& other);
	SoundObject(SoundObject&& other);
	~SoundObject();

	void Play(bool fadeIn = false, float duration = 0, float startvolume = 0);
	void Pause(bool fadeOut = false, float duration = 0, float endvolume=0);
	void Stop(bool fadeOut = false, float duration = 0, float endvolume = 0);
	void SetLoop(bool loop);

	void Update(float dt);
	bool GetIsValid()const { return m_IsValid; }
	void SetIsValid(bool valid) { m_IsValid = valid; }
	SoundType GetType()const { return m_Type; }
	bool GetIsPlaying()const;

private:
	void SetFadeInSpeed(float duration, float start);
	void SetFadeOutSpeed(float duration, float end);


	bool			m_IsValid;
	const SoundType	m_Type;
	sf::Sound		m_Sound;

	float			m_DefaultVolume;
	float			m_FadeInSpeed;
	float			m_FadeOutVolume;
	float			m_FadeOutSpeed;
	float			m_SoundDuration;
};


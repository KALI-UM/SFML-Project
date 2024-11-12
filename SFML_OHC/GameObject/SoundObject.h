#pragma once
#include "SFML/Audio.hpp"

class SoundData
{
public:
	SoundData(const std::string& filepath, float volume);
	SoundData(const SoundData& other);
	SoundData(SoundData&& other);
	~SoundData();

	void Play();
	void Pause();
	void Stop();
	void SetLoop(bool loop);

	bool GetIsValid()const { return m_IsValid; }
	void SetIsValid(bool valid) { m_IsValid = valid; }
	bool GetIsPlaying()const;

private:
	bool			m_IsValid;
	sf::Sound		m_Sound;

	float			defaultVolume;
	float			m_SoundDuration;
};


#include "pch.h"
#include "SoundPlayer.h"
#include "SoundObject.h"

SoundPlayer::SoundPlayer()
{
}

SoundPlayer::~SoundPlayer()
{
}

bool SoundPlayer::Initialize()
{
	m_Effects.insert({ "sound/ButtonClick.wav", new SoundObject("sound/ButtonClick.wav", 100, SoundType::Effect) });
	m_Effects.insert({ "sound/NextScene.wav", new SoundObject("sound/NextScene.wav", 80, SoundType::Effect) });
	m_Effects.insert({ "sound/mon_die.wav", new SoundObject("sound/mon_die.wav", 50, SoundType::Effect) });
	m_Effects.insert({ "sound/baby_dragon_die.wav", new SoundObject("sound/baby_dragon_die.wav", 70, SoundType::Effect) });

	m_BGMs.insert({ "sound/dragon_flight.mp3", new SoundObject("sound/dragon_flight.mp3", 20, SoundType::BGM) });
	m_BGMs.insert({ "sound/my_friend_dragon.mp3", new SoundObject("sound/my_friend_dragon.mp3", 20, SoundType::BGM) });

	return true;
}

void SoundPlayer::Reset()
{
}

void SoundPlayer::Update(float dt)
{
	dt = FM->GetRealDeltaTime();
	for (auto it = m_BGMs.begin(); it != m_BGMs.end(); it++)
	{
		it->second->Update(dt);
	}
}

void SoundPlayer::Release()
{
	//�����������
}

void SoundPlayer::StopAllSound()
{
	for (auto it = m_BGMs.begin(); it != m_BGMs.end(); it++)
	{
		it->second->Stop();
	}
}

void SoundPlayer::PlayEffect(const std::string& filepath)
{
	auto sound = m_Effects.find(filepath);
	if (sound == m_Effects.end())
	{
		std::cout << "�������� �ʴ� ����Ʈ ���� �Դϴ�.\n";
		return;
	}
	sound->second->
	sound->second->Play();
}

void SoundPlayer::PlayBGM(const std::string& filepath)
{
	auto sound = m_BGMs.find(filepath);
	if (sound == m_BGMs.end())
	{
		std::cout << "�������� �ʴ� ������ ���� �Դϴ�.\n";
		return;
	}
	sound->second->Play();
}

void SoundPlayer::StopBGM(const std::string& filepath)
{
	auto sound = m_BGMs.find(filepath);
	if (sound == m_BGMs.end())
	{
		std::cout << "�������� �ʴ� ������ ���� �Դϴ�.\n";
		return;
	}
	sound->second->Stop();
}

void SoundPlayer::FadeOutBGM(const std::string& filepath, float duration)
{
	auto sound = m_BGMs.find(filepath);
	if (sound == m_BGMs.end())
	{
		std::cout << "�������� �ʴ� ������ ���� �Դϴ�.\n";
		return;
	}
	sound->second->Stop(duration);
}

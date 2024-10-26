#pragma once
#include "GameObject.h"

namespace sf
{
	class Sound;
}

class SoundObject;
class SoundPlayer :
    public GameObject
{
public:
	SoundPlayer();
	~SoundPlayer();  

	bool Initialize() override;
	void Reset()override;
	void Update(float dt)override;
	void Release() override;

	void StopAllSound();
	void PlayEffect(const std::string& filepath);
	void PlayBGM(const std::string& filepath);
	void StopBGM(const std::string& filepath);

	//void EffectFadeOut(const std::string& filepath, float duration);
	void FadeOutBGM(const std::string& filepath, float duration);
private:
	std::unordered_map<std::string, SoundObject*> m_Effects;
	std::unordered_map<std::string, SoundObject*> m_BGMs;
};

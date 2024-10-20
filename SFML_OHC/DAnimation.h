#pragma once
#include "DrawableObject.h"

class DAnimation :
	public DrawableObject
{
public:
	DAnimation(sf::Texture* tex, const sf::Vector2u& FrameCnt, float speed = 1.0f, bool playnow = true, bool loop = true, DrawType type = DrawType::Normal);
	DAnimation(const std::string& filepath, const sf::Vector2u& FrameCnt, float speed = 1.0f, bool playnow = true, bool loop = true, DrawType type = DrawType::Normal);
	DAnimation(const DAnimation& other);
	DAnimation(DAnimation&& other);
	virtual ~DAnimation();

	void Update(float dt) override;
	void SetTexture(sf::Texture* tex);
	bool GetIsVisible()const;
	void SetOriginCenter();
	sf::Color GetColor() const;
	virtual void SetColor(const sf::Color& color);
	virtual void SetColor(int r, int g, int b, int a = 255);

	sf::Vector2u GetFrame() const;
	void SetFrame(unsigned int x, unsigned int y);
	void SetFrame(const sf::Vector2u& v);
	bool GetIsLoopAnim()const;
	void SetIsLoopAnim(bool playnow);

private:
	sf::Sprite m_Sprite;
	sf::Vector2u m_FrameCount;
	sf::Vector2u m_FrameSize;
	sf::Vector2u m_CurrFrame;

	float m_Speed;
	float m_FrameTime = 0;
	bool m_IsPlaying;			//재생중인지
	bool m_IsLoopAnim;
};


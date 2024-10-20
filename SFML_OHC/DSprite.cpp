#include "pch.h"
#include "DSprite.h"

DSprite::DSprite(sf::Texture* tex, DrawType type)
	:DrawableObject(DataType::Sprite, type, &m_Sprite, &m_Sprite)
{
	if (tex)
	{
		m_IsValid = true;
		m_Sprite.setTexture(*tex);
	}
	m_Drawable = &m_Sprite;
}

DSprite::DSprite(const std::string& filepath, DrawType type)
	:DrawableObject(DataType::Sprite, type, &m_Sprite, &m_Sprite)
{
	sf::Texture* tex = ResourceManager::GetInstance()->LoadTextureByFileName(filepath);
	if (tex)
	{
		m_IsValid = true;
		m_Sprite.setTexture(*tex);
	}
	m_Drawable = &m_Sprite;
}

DSprite::DSprite(DrawType type)
	:DrawableObject(DataType::Sprite, type, &m_Sprite, &m_Sprite)
{
	m_Drawable = &m_Sprite;
}

DSprite::DSprite(const DSprite& other)
	:DrawableObject(other, &m_Sprite, &m_Sprite), m_Sprite(other.m_Sprite)
{
}

DSprite::DSprite(DSprite&& other)
	:DrawableObject(other, &m_Sprite, &m_Sprite), m_Sprite(other.m_Sprite)
{
}

DSprite::~DSprite()
{
}

void DSprite::SetTexture(sf::Texture* tex)
{
	if (tex)
	{
		m_IsValid = true;
		m_Sprite.setTexture(*tex);
	}
}

bool DSprite::GetIsVisible() const
{
	return (m_Sprite.getColor().a != sf::Color::Transparent.a) || GetIsValid();
}

void DSprite::SetOriginCenter()
{
	m_Sprite.setOrigin(m_Sprite.getLocalBounds().width / 2, m_Sprite.getLocalBounds().height / 2);
}

sf::Color DSprite::GetColor() const
{
	return m_Sprite.getColor();
}

void DSprite::SetColor(const sf::Color& color)
{
	m_Sprite.setColor(color);
}

void DSprite::SetColor(int r, int g, int b, int a)
{
	SetColor(sf::Color(r, g, b, a));
}


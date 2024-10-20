#include "pch.h"
#include "DText.h"

DText::DText(sf::Font* font, const std::string& text, unsigned int charsize, DrawType type)
	:DrawableObject(DataType::Text, type, &m_Text, &m_Text)
{
	if (font)
	{
		m_IsValid = true;
		m_Text.setFont(*font);
	}
	m_Text.setString(text);
	m_Text.setCharacterSize(charsize);
}

DText::DText(const std::string& filepath, const std::string& text, unsigned int charsize, DrawType type)
	:DrawableObject(DataType::Text, type, &m_Text, &m_Text)
{
	sf::Font* font = ResourceManager<sf::Font>::GetInstance()->GetByFilepath(filepath);
	if (font)
	{
		m_IsValid = true;
		m_Text.setFont(*font);
	}
	m_Text.setString(text);
	m_Text.setCharacterSize(charsize);
}

DText::DText(const sf::Vector2f& position, sf::Font* font, const std::string& text, unsigned int charsize, DrawType type)
	:DrawableObject(DataType::Text, type, &m_Text, &m_Text)
{
	m_Text.setPosition(position);
	if (font)
	{
		m_IsValid = true;
		m_Text.setFont(*font);
	}
	m_Text.setString(text);
	m_Text.setCharacterSize(charsize);
}

DText::DText(const sf::Vector2f& position, const std::string& filepath, const std::string& text, unsigned int charsize, DrawType type)
	:DrawableObject(DataType::Text, type, &m_Text, &m_Text)
{
	m_Text.setPosition(position);
	sf::Font* font = ResourceManager<sf::Font>::GetInstance()->GetByFilepath(filepath);
	if (font)
	{
		m_IsValid = true;
		m_Text.setFont(*font);
	}
	m_Text.setString(text);
	m_Text.setCharacterSize(charsize);
}


DText::DText(DrawType type)
	:DrawableObject(DataType::Text, type, &m_Text, &m_Text)
{
}

DText::DText(const DText& other)
	:DrawableObject(other, &m_Text, &m_Text), m_Text(other.m_Text)
{
}

DText::DText(DText&& other)
	:DrawableObject(other, &m_Text, &m_Text), m_Text(other.m_Text)
{
}

DText::~DText()
{
}

void DText::SetFont(sf::Font* font)
{
	if (font)
	{
		m_IsValid = true;
		m_Text.setFont(*font);
	}
}

void DText::SetString(const std::string& text)
{
	m_Text.setString(text);
}

bool DText::GetIsVisible() const
{
	return (m_Text.getFillColor().a != sf::Color::Transparent.a) && (m_Text.getOutlineColor().a != sf::Color::Transparent.a) && GetIsValid();
}

void DText::SetOriginCenter()
{
	m_Text.setOrigin(m_Text.getLocalBounds().width / 2, m_Text.getLocalBounds().height / 2);
}

sf::Color DText::GetColor() const
{
	return m_Text.getFillColor();
}

void DText::SetColor(const sf::Color& color)
{
	SetFillColor(color);
}

void DText::SetColor(int r, int g, int b, int a)
{
	SetFillColor(sf::Color(r, g, b, a));
}

sf::Color DText::GetFillColor() const
{
	return m_Text.getFillColor();
}

sf::Color DText::GetOutlineColor() const
{
	return m_Text.getOutlineColor();
}

void DText::SetFillColor(const sf::Color& color)
{
	m_Text.setFillColor(color);
}

void DText::SetFillColor(int r, int g, int b, int a)
{
	SetFillColor(sf::Color(r, g, b, a));
}

void DText::SetOutlineColor(const sf::Color& color)
{
	m_Text.setOutlineColor(color);
}

void DText::SetOutlineColor(int r, int g, int b, int a)
{
	SetOutlineColor(sf::Color(r, g, b, a));
}

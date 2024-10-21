#include "pch.h"
#include "DRectangle.h"

DRectangle::DRectangle(const sf::Vector2f& position, const sf::Vector2f& widthheight, const sf::Color& line, float thick, const sf::Color& fill, DrawType type)
	:DShape(&m_Rectangle, line, thick, fill, type)
{
	m_Rectangle.setPosition(position);
	m_Rectangle.setSize(widthheight);
	SetOutlineColor(line);
	SetOutlineThickness(thick);
	SetFillColor(fill);
}

DRectangle::DRectangle(const sf::Vector2f& position, const sf::Vector2f& widthheight, sf::Texture* tex, DrawType type)
	:DShape(&m_Rectangle, tex, type)
{
	m_Rectangle.setPosition(position);
	m_Rectangle.setSize(widthheight);
	if (tex)
	{
		m_IsValid = true;
	}
}

DRectangle::DRectangle(const sf::Vector2f& position, const sf::Vector2f& widthheight, const std::string& filepath, DrawType type)
	:DShape(&m_Rectangle, ResourceManager<sf::Texture>::GetInstance()->GetByFilepath(filepath), type)
{
	m_Rectangle.setPosition(position);
	m_Rectangle.setSize(widthheight);
}

DRectangle::DRectangle(const DRectangle& other)
	:DShape(other)
{
}

DRectangle::DRectangle(DRectangle&& other)
	:DShape(other)
{
}

DRectangle::~DRectangle()
{
}

void DRectangle::SetSize(const sf::Vector2f& widthheight)
{
	m_Rectangle.setSize(widthheight);
}


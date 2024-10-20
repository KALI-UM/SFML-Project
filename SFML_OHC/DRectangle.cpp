#include "pch.h"
#include "DRectangle.h"

DRectangle::DRectangle(const sf::Vector2f& widthheight, const sf::Color& line, float thick, const sf::Color& fill, DrawType type)
	:DrawableObject(DataType::Shape, type, &m_Shape, &m_Shape)
{
	m_Shape.setSize(widthheight);
	m_Shape.setOutlineColor(line);
	m_Shape.setOutlineThickness(thick);
	m_Shape.setFillColor(fill);
	m_IsValid = true;
}

DRectangle::DRectangle(const sf::Vector2f& position, const sf::Vector2f& widthheight, const sf::Color& line, float thick, const sf::Color& fill, DrawType type)
	:DrawableObject(DataType::Shape, type, &m_Shape, &m_Shape)
{
	m_Shape.setPosition(position);
	m_Shape.setSize(widthheight);
	m_Shape.setOutlineColor(line);
	m_Shape.setOutlineThickness(thick);
	m_Shape.setFillColor(fill);
	m_IsValid = true;
}

DRectangle::DRectangle(const DRectangle& other)
	:DrawableObject(other, &m_Shape, &m_Shape)
{
}

DRectangle::DRectangle(DRectangle&& other)
	:DrawableObject(other, &m_Shape, &m_Shape)
{
}

DRectangle::~DRectangle()
{
}

bool DRectangle::GetIsVisible() const
{
	return ((m_Shape.getFillColor().a != sf::Color::Transparent.a)&&(m_Shape.getOutlineColor().a != sf::Color::Transparent.a)) || GetIsValid();
}

void DRectangle::SetOriginCenter()
{
	m_Shape.setOrigin(m_Shape.getLocalBounds().width / 2, m_Shape.getLocalBounds().height / 2);
}

sf::Color DRectangle::GetColor() const
{
	return m_Shape.getFillColor();
}

void DRectangle::SetColor(const sf::Color& color)
{
	SetFillColor(color);
}

void DRectangle::SetColor(int r, int g, int b, int a)
{
	SetFillColor(sf::Color(r, g, b, a));
}

sf::Color DRectangle::GetFillColor() const
{
	return m_Shape.getFillColor();
}

sf::Color DRectangle::GetOutlineColor() const
{
	return m_Shape.getOutlineColor();
}

void DRectangle::SetFillColor(const sf::Color& color)
{
	m_Shape.setFillColor(color);
}

void DRectangle::SetFillColor(int r, int g, int b, int a)
{
	SetFillColor(sf::Color(r, g, b, a));
}

void DRectangle::SetOutlineColor(const sf::Color& color)
{
	m_Shape.setOutlineColor(color);
}

void DRectangle::SetOutlineColor(int r, int g, int b, int a)
{
	SetOutlineColor(sf::Color(r, g, b, a));
}

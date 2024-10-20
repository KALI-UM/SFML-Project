#include "pch.h"
#include "DCircle.h"

DCircle::DCircle(float radius, const sf::Color& line, float thick, const sf::Color& fill, DrawType type)
	:DrawableObject(DataType::Shape, type, &m_Shape, &m_Shape)
{
	m_Shape.setRadius(radius);
	m_Shape.setOutlineColor(line);
	m_Shape.setOutlineThickness(thick);
	m_Shape.setFillColor(fill);
	m_IsValid = true;
}

DCircle::DCircle(const sf::Vector2f& position, float radius, const sf::Color& line, float thick, const sf::Color& fill, DrawType type)
	:DrawableObject(DataType::Shape, type, &m_Shape, &m_Shape)
{
	m_Shape.setPosition(position);
	m_Shape.setRadius(radius);
	m_Shape.setOutlineColor(line);
	m_Shape.setOutlineThickness(thick);
	m_Shape.setFillColor(fill);
	m_IsValid = true;
}

DCircle::DCircle(const DCircle& other)
	:DrawableObject(other, &m_Shape, &m_Shape)
{
}

DCircle::DCircle(DCircle&& other)
	:DrawableObject(other, &m_Shape, &m_Shape)
{
}

DCircle::~DCircle()
{
}

bool DCircle::GetIsVisible() const
{
	return (m_Shape.getFillColor().a != sf::Color::Transparent.a) && (m_Shape.getOutlineColor().a != sf::Color::Transparent.a)&&GetIsValid();
}

void DCircle::SetOriginCenter()
{
	m_Shape.setOrigin(m_Shape.getRadius(), m_Shape.getRadius());
}

sf::Color DCircle::GetColor() const
{
	return m_Shape.getFillColor();
}

void DCircle::SetColor(const sf::Color& color)
{
	SetFillColor(color);
}

void DCircle::SetColor(int r, int g, int b, int a)
{
	SetFillColor(sf::Color(r, g, b, a));
}

sf::Color DCircle::GetFillColor() const
{
	return m_Shape.getFillColor();
}

sf::Color DCircle::GetOutlineColor() const
{
	return m_Shape.getOutlineColor();
}

void DCircle::SetFillColor(const sf::Color& color)
{
	m_Shape.setFillColor(color);
}

void DCircle::SetFillColor(int r, int g, int b, int a)
{
	SetFillColor(sf::Color(r, g, b, a));
}

void DCircle::SetOutlineColor(const sf::Color& color)
{
	m_Shape.setOutlineColor(color);
}

void DCircle::SetOutlineColor(int r, int g, int b, int a)
{
	SetOutlineColor(sf::Color(r, g, b, a));
}

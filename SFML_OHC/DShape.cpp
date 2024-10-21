#include "pch.h"
#include "DShape.h"

DShape::DShape(sf::Shape* shape, const sf::Color& line, float thick, const sf::Color& fill, DrawType type)
	:m_Shape(shape), DrawableObject(DataType::Shape, type, shape, shape)
{
	m_IsValid = m_Shape;
}

DShape::DShape(sf::Shape* shape, sf::Texture* tex, DrawType type)
	:m_Shape(shape), DrawableObject(DataType::Shape, type, shape, shape)
{
	m_IsValid = m_Shape;
	SetTexture(tex);
}

DShape::DShape(const DShape& other)
	:DrawableObject(other, m_Shape, m_Shape)
{
}

DShape::DShape(DShape&& other)
	:DrawableObject(other, m_Shape, m_Shape)
{
}

DShape::~DShape()
{
}

void DShape::SetTexture(sf::Texture* tex)
{
	m_Shape->setTexture(tex);
	if (tex)
	{
		SetFillColor(sf::Color::Transparent);
	}
}

bool DShape::GetIsVisible() const
{
	return ((m_Shape->getFillColor().a != sf::Color::Transparent.a) && (m_Shape->getOutlineColor().a != sf::Color::Transparent.a)) && GetIsValid();
}

void DShape::SetOriginCenter()
{
	m_Shape->setOrigin(m_Shape->getLocalBounds().width / 2, m_Shape->getLocalBounds().height / 2);
}

sf::Color DShape::GetColor() const
{
	return m_Shape->getFillColor();
}

void DShape::SetColor(const sf::Color& color)
{
	SetFillColor(color);
}

void DShape::SetColor(int r, int g, int b, int a)
{
	SetFillColor(sf::Color(r, g, b, a));
}

sf::Color DShape::GetFillColor() const
{
	return m_Shape->getFillColor();
}

sf::Color DShape::GetOutlineColor() const
{
	return m_Shape->getOutlineColor();
}

void DShape::SetFillColor(const sf::Color& color)
{
	m_Shape->setFillColor(color);
}

void DShape::SetFillColor(int r, int g, int b, int a)
{
	SetFillColor(sf::Color(r, g, b, a));
}

void DShape::SetOutlineColor(const sf::Color& color)
{
	m_Shape->setOutlineColor(color);
}

void DShape::SetOutlineColor(int r, int g, int b, int a)
{
	SetOutlineColor(sf::Color(r, g, b, a));
}

void DShape::SetOutlineThickness(float thick)
{
	m_Shape->setOutlineThickness(thick);
}

#include "pch.h"
#include "DCircle.h"

#include "pch.h"
#include "DCircle.h"

DCircle::DCircle(const sf::Vector2f& position, float radius, const sf::Color& line, float thick, const sf::Color& fill, int pointcnt, DrawType type)
	:DShape(&m_Circle, line, thick, fill, type)
{
	m_Circle.setPosition(position);
	SetPointCount(pointcnt);
	SetRadius(radius);
	SetOutlineColor(line);
	SetOutlineThickness(thick);
	SetFillColor(fill);
}

DCircle::DCircle(const sf::Vector2f& position, float radius, sf::Texture* tex, int pointcnt, DrawType type)
	:DShape(&m_Circle, tex, type)
{
	m_Circle.setPosition(position);
	SetPointCount(pointcnt);
	SetRadius(radius);
	if (tex)
	{
		m_IsValid = true;
	}
}

DCircle::DCircle(const sf::Vector2f& position, float radius, const std::string& filepath, int pointcnt, DrawType type)
	:DShape(&m_Circle, ResourceManager<sf::Texture>::GetInstance()->GetByFilepath(filepath), type)
{
	m_Circle.setPosition(position);
	m_Circle.setPointCount(pointcnt);
	m_Circle.setRadius(radius);
}

DCircle::DCircle(const DCircle& other)
	:DShape(other)
{
}

DCircle::DCircle(DCircle&& other)
	:DShape(other)
{
}

DCircle::~DCircle()
{
}

void DCircle::SetRadius(float r)
{
	m_Circle.setRadius(r);
}

void DCircle::SetPointCount(int cnt)
{
	m_Circle.setPointCount(cnt);
}

sf::FloatRect DCircle::GetFloatRect() const
{
	return m_Circle.getGlobalBounds();
}



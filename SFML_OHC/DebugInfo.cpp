#include "pch.h"
#include "DebugInfo.h"

DebugInfo::DebugInfo(const sf::FloatRect& target, const sf::Vector2f& pos)
	:m_Target(target), m_Position(pos)
{
	m_Rectangle.setFillColor(sf::Color::Transparent);
	m_Rectangle.setOutlineColor(sf::Color::Green);
	m_Rectangle.setOutlineThickness(1);
	m_X[0].resize(2);
	m_X[1].resize(2);
	m_X[0].setPrimitiveType(sf::LineStrip);
	m_X[1].setPrimitiveType(sf::LineStrip);
	setXColor(sf::Color::Magenta);
	Update(target);
}

DebugInfo::~DebugInfo()
{
}

void DebugInfo::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform(); // getTransform() is defined by sf::Transformable

	target.draw(m_Rectangle, states);
	target.draw(m_X[0], states);
	target.draw(m_X[1], states);
}

void DebugInfo::Update(const sf::FloatRect& target)
{
	m_Target = target;
	m_Rectangle.setSize(m_Target.getSize());
	m_Rectangle.setPosition(m_Target.getPosition());
	m_X[0][0].position = { m_Position.x + 4,m_Position.y + 4 };
	m_X[0][1].position = { m_Position.x - 4,m_Position.y - 4 };
	m_X[1][0].position = { m_Position.x + 4,m_Position.y - 4 };
	m_X[1][1].position = { m_Position.x - 4,m_Position.y + 4 };
}

void DebugInfo::setColor(const sf::Color& color)
{
	setOutlineColor(color);
}

void DebugInfo::setColor(int r, int g, int b, int a)
{
	setColor(sf::Color(r, g, b, a));
}

const sf::Color& DebugInfo::getColor() const
{
	return getRectColor();
}

void DebugInfo::setOutlineColor(const sf::Color& color)
{
	m_Rectangle.setOutlineColor(color);
}

void DebugInfo::setOutlineColor(int r, int g, int b, int a)
{
	setOutlineColor(sf::Color(r, g, b, a));
}

const sf::Color& DebugInfo::getRectColor() const
{
	return m_Rectangle.getOutlineColor();
}

void DebugInfo::setXColor(const sf::Color& color)
{
	m_XColor = color;
	for (int i = 0; i < m_X[0].getVertexCount(); i++)
	{
		m_X[0][i].color = m_XColor;
	}
	for (int i = 0; i < m_X[1].getVertexCount(); i++)
	{
		m_X[1][i].color = m_XColor;
	}
}

void DebugInfo::setXColor(int r, int g, int b, int a)
{
	setXColor(sf::Color(r, g, b, a));
}

const sf::Color& DebugInfo::getXColor() const
{
	return m_XColor;
}

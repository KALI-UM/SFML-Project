#include "pch.h"
#include "Line.h"

Line::Line()
{

}

Line::~Line()
{
}

void Line::setColor(const sf::Color& color)
{
	m_Color = color;
	for (int i = 0; i < m_Vertices.getVertexCount(); i++)
	{
		m_Vertices[i].color = color;
	}
}

const sf::Color& Line::getColor() const
{
	return m_Color;
}

sf::FloatRect Line::getGlobalBounds() const
{
	return getTransform().transformRect(m_Vertices.getBounds());
}

sf::FloatRect Line::getLocalBounds() const
{
	return m_Vertices.getBounds();
}

void Line::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform(); // getTransform() is defined by sf::Transformable
	target.draw(m_Vertices, states);
}
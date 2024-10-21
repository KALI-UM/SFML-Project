#include "pch.h"
#include "DLine.h"

Line::Line()
{
	m_Vertices.setPrimitiveType(sf::TriangleStrip);
}

Line::~Line()
{
}

void Line::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform(); // getTransform() is defined by sf::Transformable
	target.draw(m_Vertices, states);
}


DLine::DLine(const sf::Vector2f& point1, const sf::Vector2f& point2, const sf::Color& line, float thick, DrawType type)
	:DrawableObject(DataType::Shape, type, &m_Line, &m_Line),
	m_Thickness(thick), m_HalfThickness(thick / 2)
{
	SetPoint(point1, point2);
	SetFillColor(line);
}

DLine::DLine(sf::Vector2f points[], int size, const sf::Color& line, float thick, DrawType type)
	:DrawableObject(DataType::Shape, type, &m_Line, &m_Line),
	m_Thickness(thick), m_HalfThickness(thick / 2)
{
	SetFillColor(line);
}

DLine::DLine(const DLine& other)
	:DrawableObject(other, &m_Line, &m_Line),
	m_Thickness(other.m_Thickness), m_HalfThickness(m_Thickness / 2)
{
}

DLine::DLine(DLine&& other)
	:DrawableObject(other, &m_Line, &m_Line),
	m_Thickness(other.m_Thickness), m_HalfThickness(m_Thickness / 2)
{
}

DLine::~DLine()
{
}

void DLine::SetPoint(const sf::Vector2f& p1, const sf::Vector2f& p2)
{
	if (m_Thickness == 1)
	{
		m_Line.m_Vertices.resize(2);
		m_Line.m_Vertices[0] = sf::Vector2f(p1.x, p1.y);
		m_Line.m_Vertices[1] = sf::Vector2f(p2.x, p2.y);
	}
	else
	{
		m_Line.m_Vertices.resize(6);
		m_Line.m_Vertices[0] = sf::Vector2f(p1.x + m_HalfThickness, p1.y);
		m_Line.m_Vertices[1] = sf::Vector2f(p1.x, p1.y);
		m_Line.m_Vertices[2] = sf::Vector2f(p1.x, p1.y + m_HalfThickness);
		m_Line.m_Vertices[3] = sf::Vector2f(p2.x, p2.y + m_HalfThickness);
		m_Line.m_Vertices[4] = sf::Vector2f(p2.x, p2.y);
		m_Line.m_Vertices[5] = sf::Vector2f(p2.x + m_HalfThickness, p2.y);
	}
}

void DLine::SetPoints(sf::Vector2f points[], int size)
{
	if (m_Thickness == 1)
	{
		m_Line.m_Vertices.resize(size);
		for (int i = 0; i < size; i++)
		{
			m_Line.m_Vertices[i] = points[i];
		}
	}
	else
	{
		m_Line.m_Vertices.resize(2+2*size);
		for (int i = 0; i < size; i++)
		{
			m_Line.m_Vertices[i] = points[i];
		}
		//¼öÁ¤Áß
		/*m_Line.m_Vertices[0] = sf::Vector2f(p1.x + m_HalfThickness, p1.y);
		m_Line.m_Vertices[1] = sf::Vector2f(p1.x, p1.y);
		m_Line.m_Vertices[2] = sf::Vector2f(p1.x, p1.y + m_HalfThickness);
		m_Line.m_Vertices[3] = sf::Vector2f(p2.x, p2.y + m_HalfThickness);
		m_Line.m_Vertices[4] = sf::Vector2f(p2.x, p2.y);
		m_Line.m_Vertices[5] = sf::Vector2f(p2.x + m_HalfThickness, p2.y);*/
	}
}

void DLine::SetThickness(float thick)
{
	m_Thickness = thick;
	m_HalfThickness = m_Thickness / 2;
}


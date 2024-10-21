#include "pch.h"
#include "DLine.h"

Line::Line()
{
	m_Vertices.setPrimitiveType(sf::TriangleStrip);
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

void Line::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform(); // getTransform() is defined by sf::Transformable
	target.draw(m_Vertices, states);
}


DLine::DLine(const sf::Vector2f& point1, const sf::Vector2f& point2, const sf::Color& line, float thick, DrawType type)
	:DrawableObject(DataType::Shape, type, &m_Line.m_Vertices, &m_Line),
	m_Thickness(thick), m_HalfThickness(thick / 2)
{
	SetPoint(point1, point2);
	SetFillColor(line);
	m_IsValid = true;
}

DLine::DLine(sf::Vector2f points[], int size, const sf::Color& line, float thick, DrawType type)
	:DrawableObject(DataType::Shape, type, &m_Line.m_Vertices, &m_Line),
	m_Thickness(thick), m_HalfThickness(thick / 2)
{
	SetPoints(points, size);
	SetFillColor(line);
	m_IsValid = true;
}

DLine::DLine(const DLine& other)
	:DrawableObject(other, &m_Line.m_Vertices, &m_Line),
	m_Thickness(other.m_Thickness), m_HalfThickness(m_Thickness / 2)
{
}

DLine::DLine(DLine&& other)
	:DrawableObject(other, &m_Line.m_Vertices, &m_Line),
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
		m_Line.m_Vertices[0].position = sf::Vector2f(p1.x, p1.y);
		m_Line.m_Vertices[1].position = sf::Vector2f(p2.x, p2.y);
	}
	else
	{
		m_Line.m_Vertices.resize(6);
		m_Line.m_Vertices[0].position = sf::Vector2f(p1.x + m_HalfThickness, p1.y);
		m_Line.m_Vertices[1].position = sf::Vector2f(p1.x, p1.y);
		m_Line.m_Vertices[2].position = sf::Vector2f(p1.x, p1.y + m_HalfThickness);
		m_Line.m_Vertices[3].position = sf::Vector2f(p2.x, p2.y + m_HalfThickness);
		m_Line.m_Vertices[4].position = sf::Vector2f(p2.x, p2.y);
		m_Line.m_Vertices[5].position = sf::Vector2f(p2.x + m_HalfThickness, p2.y);
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
		static float root2 = sqrt(2);
		m_Line.m_Vertices.resize(2 * size);
		float theta = 0;
		for (int i = 0; i < size; i++)
		{
			if (i != size - 1)
				theta = atan2f(points[i + 1].y - points[i].y, points[i + 1].x - points[i].x);
			m_Line.m_Vertices[i * 2] = sf::Vector2f(points[i].x + m_HalfThickness * cosf(theta), points[i].y + m_HalfThickness * sinf(theta));
			m_Line.m_Vertices[i * 2 + 1] = sf::Vector2f(points[i].x + m_HalfThickness * cosf(theta), points[i].y + m_HalfThickness * sinf(theta));
		}
	}
}

void DLine::SetThickness(float thick)
{
	m_Thickness = thick;
	m_HalfThickness = m_Thickness / 2;
}

bool DLine::GetIsVisible() const
{
	return (m_Line.getColor().a != sf::Color::Transparent.a) && GetIsValid();
}

void DLine::SetOriginCenter()
{
	//쓰지마라.
	//m_Line.setOrigin(m_Line.getLocalBounds().width / 2, m_Line.getLocalBounds().height / 2);
}

sf::Color DLine::GetColor() const
{
	return m_Line.getColor();
}

void DLine::SetColor(const sf::Color& color)
{
	SetFillColor(color);
}

void DLine::SetColor(int r, int g, int b, int a)
{
	SetFillColor(sf::Color(r, g, b, a));
}

sf::Color DLine::GetFillColor() const
{
	return m_Line.getColor();
}

sf::Color DLine::GetOutlineColor() const
{
	return m_Line.getColor();
}

void DLine::SetFillColor(const sf::Color& color)
{
	m_Line.setColor(color);
}

void DLine::SetFillColor(int r, int g, int b, int a)
{
	SetFillColor(sf::Color(r, g, b, a));
}

void DLine::SetOutlineColor(const sf::Color& color)
{
	m_Line.setColor(color);
}

void DLine::SetOutlineColor(int r, int g, int b, int a)
{
	SetOutlineColor(sf::Color(r, g, b, a));
}

void DLine::SetOutlineThickness(float thick)
{
	SetThickness(thick);
}

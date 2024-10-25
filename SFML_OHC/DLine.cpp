#include "pch.h"
#include "DLine.h"

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

sf::FloatRect Line::getLocalBounds() const
{
	return m_Vertices.getBounds();
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
	m_Line.m_Color = line;
	SetPoint(point1, point2);
	m_IsValid = true;
}

DLine::DLine(sf::Vector2f points[], int size, const sf::Color& line, float thick, DrawType type)
	:DrawableObject(DataType::Shape, type, &m_Line, &m_Line),
	m_Thickness(thick), m_HalfThickness(thick / 2)
{
	m_Line.m_Color = line;
	SetPoints(points, size);
	m_IsValid = true;
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
	SetRawToVertex(p1, p2);
	if (m_Thickness == 1)
	{
		m_Line.m_Vertices.setPrimitiveType(sf::LineStrip);
		m_Line.m_Vertices.resize(2);
		m_Line.m_Vertices[0].position = m_Line.m_RawVertices[0];
		m_Line.m_Vertices[1].position = m_Line.m_RawVertices[1];
	}
	else
	{
		m_Line.m_Vertices.setPrimitiveType(sf::TriangleStrip);
		m_Line.m_Vertices.resize(4);

		//p1과 p2를 잇는 선분에 직교하는 선분의 기울기를 역탄젠트해 직교하는 선분을 빗변으로 하는 삼각형의 세타값을 구한다. 
		//코사인세타, 사인세타값으로 p1을 중심으로 하고 길이가 thick인 포인트의 위치를 구할 수 있다.
		float theta = atan2f(-p2.x + p1.x, p2.y - p1.y);
		m_Line.m_Vertices[0].position = sf::Vector2f(m_Line.m_RawVertices[0].x + m_HalfThickness * cosf(theta), m_Line.m_RawVertices[0].y + m_HalfThickness * sinf(theta));
		m_Line.m_Vertices[1].position = sf::Vector2f(m_Line.m_RawVertices[0].x - m_HalfThickness * cosf(theta), m_Line.m_RawVertices[0].y - m_HalfThickness * sinf(theta));
		m_Line.m_Vertices[2].position = sf::Vector2f(m_Line.m_RawVertices[1].x + m_HalfThickness * cosf(theta), m_Line.m_RawVertices[1].y + m_HalfThickness * sinf(theta));
		m_Line.m_Vertices[3].position = sf::Vector2f(m_Line.m_RawVertices[1].x - m_HalfThickness * cosf(theta), m_Line.m_RawVertices[1].y - m_HalfThickness * sinf(theta));
	}
	SetColor(m_Line.m_Color);
}

void DLine::SetPoints(sf::Vector2f points[], int size)
{
	SetRawToVertex(points, size);
	if (m_Thickness == 1)
	{
		m_Line.m_Vertices.setPrimitiveType(sf::LineStrip);
		m_Line.m_Vertices.resize(size);
		for (int i = 0; i < size; i++)
		{
			m_Line.m_Vertices[i].position = m_Line.m_RawVertices[i];
		}
	}
	else
	{
		m_Line.m_Vertices.setPrimitiveType(sf::TriangleStrip);
		m_Line.m_Vertices.resize(4 * (size - 1));
		float theta = 0;
		for (int i = 1; i < size; i++)
		{
			int j = i - 1;
			theta = atan2f(-points[i].x + points[j].x, points[i].y - points[j].y);
			m_Line.m_Vertices[j * 4].position = sf::Vector2f(points[j].x + m_HalfThickness * cosf(theta), points[j].y + m_HalfThickness * sinf(theta));
			m_Line.m_Vertices[j * 4 + 1].position = sf::Vector2f(points[j].x - m_HalfThickness * cosf(theta), points[j].y - m_HalfThickness * sinf(theta));
			m_Line.m_Vertices[j * 4 + 2].position = sf::Vector2f(points[i].x + m_HalfThickness * cosf(theta), points[i].y + m_HalfThickness * sinf(theta));
			m_Line.m_Vertices[j * 4 + 3].position = sf::Vector2f(points[i].x - m_HalfThickness * cosf(theta), points[i].y - m_HalfThickness * sinf(theta));
		}
	}
	SetColor(m_Line.m_Color);
}

void DLine::SetPoint(int index, const sf::Vector2f& p)
{
	if (m_Line.m_RawVertices.size() <= index)
	{
		return;
	}
	m_Line.m_RawVertices[index] = p;

	if (m_Thickness == 1)
	{
		m_Line.m_Vertices[index].position = m_Line.m_RawVertices[index];
	}
	else
	{
		int i;
		if (index == 0)i = 0;
		else if (index == m_Line.m_RawVertices.size() - 1)
		{
			index -= 1;
			i = index;
		}
		else i = index - 1;

		for (; i <= index; i++)
		{
			float theta = atan2f(-m_Line.m_RawVertices[i + 1].x + m_Line.m_RawVertices[i].x, m_Line.m_RawVertices[i + 1].y - m_Line.m_RawVertices[i].y);
			m_Line.m_Vertices[i * 4].position = sf::Vector2f(m_Line.m_RawVertices[i].x + m_HalfThickness * cosf(theta), m_Line.m_RawVertices[i].y + m_HalfThickness * sinf(theta));
			m_Line.m_Vertices[i * 4 + 1].position = sf::Vector2f(m_Line.m_RawVertices[i].x - m_HalfThickness * cosf(theta), m_Line.m_RawVertices[i].y - m_HalfThickness * sinf(theta));
			m_Line.m_Vertices[i * 4 + 2].position = sf::Vector2f(m_Line.m_RawVertices[i + 1].x + m_HalfThickness * cosf(theta), m_Line.m_RawVertices[i + 1].y + m_HalfThickness * sinf(theta));
			m_Line.m_Vertices[i * 4 + 3].position = sf::Vector2f(m_Line.m_RawVertices[i + 1].x - m_HalfThickness * cosf(theta), m_Line.m_RawVertices[i + 1].y - m_HalfThickness * sinf(theta));
		}
	}
}


void DLine::SetThickness(float thick)
{
	if (m_Thickness == thick)return;

	if (m_Thickness != 1 && thick != 1)
	{
		m_Thickness = thick;
		m_HalfThickness = m_Thickness / 2;
		for (int i = 0; i < m_Line.m_RawVertices.size(); i++)
		{
			SetPoint(i, m_Line.m_RawVertices[i]);
		}
	}
	else
	{
		m_Thickness = thick;
		m_HalfThickness = m_Thickness / 2;
		SetPoints(m_Line.m_RawVertices.data(), m_Line.m_RawVertices.size());
	}
}

bool DLine::GetIsVisible() const
{
	return (m_Line.getColor().a != sf::Color::Transparent.a) && GetIsValid();
}

void DLine::SetOriginCenter()
{
	m_Line.setOrigin(m_Line.getLocalBounds().width / 2, m_Line.getLocalBounds().height / 2);
}

sf::Color DLine::GetColor() const
{
	return m_Line.getColor();
}

void DLine::SetColor(const sf::Color& color)
{
	m_Line.setColor(color);
}

void DLine::SetColor(int r, int g, int b, int a)
{
	SetColor(sf::Color(r, g, b, a));
}

sf::Color DLine::GetFillColor() const
{
	return GetColor();
}

sf::Color DLine::GetOutlineColor() const
{
	return GetColor();
}

void DLine::SetFillColor(const sf::Color& color)
{
	SetColor(color);
}

void DLine::SetFillColor(int r, int g, int b, int a)
{
	SetFillColor(sf::Color(r, g, b, a));
}

void DLine::SetOutlineColor(const sf::Color& color)
{
	SetColor(color);
}

void DLine::SetOutlineColor(int r, int g, int b, int a)
{
	SetOutlineColor(sf::Color(r, g, b, a));
}

void DLine::SetOutlineThickness(float thick)
{
	SetThickness(thick);
}

void DLine::SetRawToVertex(const sf::Vector2f& p1, const sf::Vector2f& p2)
{
	m_Line.m_RawVertices.resize(2);
	m_Line.m_RawVertices[0] = p1;
	m_Line.m_RawVertices[1] = p2;
}

void DLine::SetRawToVertex(sf::Vector2f points[], int size)
{
	m_Line.m_RawVertices.resize(size);
	for (int i = 0; i < size; i++)
	{
		m_Line.m_RawVertices[i] = points[i];
	}
}


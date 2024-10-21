#pragma once
#include "DrawableObject.h"

class Line : public sf::Drawable, public sf::Transformable
{
	friend DLine;
private:
	Line();
	~Line();
	sf::VertexArray m_Vertices;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

class DLine :
	public DrawableObject
{
public:
	DLine(const sf::Vector2f& point1, const sf::Vector2f& point2, const sf::Color& line, float thick = 1.0f, DrawType type = DrawType::Normal);
	DLine(sf::Vector2f points[], int size, const sf::Color& line, float thick = 1.0f, DrawType type = DrawType::Normal);
	DLine(const DLine& other);
	DLine(DLine&& other);
	virtual ~DLine();

	void SetPoint(const sf::Vector2f& p1, const sf::Vector2f& p2);
	void SetPoints(sf::Vector2f points[], int size);
	void SetThickness(float thick);

	bool GetIsVisible()const;
	void SetOriginCenter();
	sf::Color GetColor() const;								//GetFillColor�� ����		
	void SetColor(const sf::Color& color);					//SetFillColor�� ����
	void SetColor(int r, int g, int b, int a = 255);		//SetFillColor�� ����
	sf::Color GetFillColor() const;
	sf::Color GetOutlineColor() const;
	void SetFillColor(const sf::Color& color);
	void SetFillColor(int r, int g, int b, int a = 255);
	void SetOutlineColor(const sf::Color& color);
	void SetOutlineColor(int r, int g, int b, int a = 255);
	void SetOutlineThickness(float thick);
private:
	Line m_Line;
	float m_Thickness;
	float m_HalfThickness;
};

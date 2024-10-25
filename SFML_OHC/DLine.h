#pragma once
#include "DrawableObject.h"

class DLine;
class Line : public sf::Drawable, public sf::Transformable
{
	friend class DLine;
private:
	Line();
	~Line();
	std::vector<sf::Vector2f> m_RawVertices;
	sf::VertexArray m_Vertices;
	sf::Color m_Color;

	void setColor(const sf::Color& color);
	const sf::Color& getColor()const;
	sf::FloatRect getLocalBounds()const;
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
	void SetPoint(int index, const sf::Vector2f& p);
	void SetThickness(float thick);

	bool GetIsVisible()const;
	void SetOriginCenter();
	sf::Color GetColor() const;								//GetFillColor客 悼老		
	void SetColor(const sf::Color& color);					//SetFillColor客 悼老
	void SetColor(int r, int g, int b, int a = 255);		//SetFillColor客 悼老
	sf::Color GetFillColor() const;
	sf::Color GetOutlineColor() const;
	void SetFillColor(const sf::Color& color);
	void SetFillColor(int r, int g, int b, int a = 255);
	void SetOutlineColor(const sf::Color& color);
	void SetOutlineColor(int r, int g, int b, int a = 255);
	void SetOutlineThickness(float thick);
private:
	void SetRawToVertex(const sf::Vector2f& p1, const sf::Vector2f& p2);
	void SetRawToVertex(sf::Vector2f points[], int size);

private:
	Line m_Line;
	float m_Thickness;
	float m_HalfThickness;
};


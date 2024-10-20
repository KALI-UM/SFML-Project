#pragma once
#include "DrawableObject.h"

class DCircle :
	public DrawableObject
{
public:
	DCircle(float radius, const sf::Color& line, float thick = 1.0f, const sf::Color& fill = sf::Color::Transparent, DrawType type = DrawType::Normal);
	DCircle(const sf::Vector2f& position, float radius, const sf::Color& line, float thick = 1.0f, const sf::Color& fill = sf::Color::Transparent, DrawType type = DrawType::Normal);
	DCircle(const DCircle& other);
	DCircle(DCircle&& other);
	virtual ~DCircle();

	bool GetIsVisible()const;
	void SetOriginCenter();
	sf::Color GetColor() const;									//GetFillColor客 悼老
	virtual void SetColor(const sf::Color& color);				//SetFillColor客 悼老
	virtual void SetColor(int r, int g, int b, int a = 255);	//SetFillColor客 悼老
	sf::Color GetFillColor() const;
	sf::Color GetOutlineColor() const;
	void SetFillColor(const sf::Color& color);
	void SetFillColor(int r, int g, int b, int a = 255);
	void SetOutlineColor(const sf::Color& color);
	void SetOutlineColor(int r, int g, int b, int a = 255);

private:
	sf::CircleShape m_Shape;
};


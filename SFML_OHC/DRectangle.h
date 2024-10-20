#pragma once
#include "DrawableObject.h"

class DRectangle :
	public DrawableObject
{
public:
	DRectangle(const sf::Vector2f& widthheight, const sf::Color& line, float thick = 1.0f, const sf::Color& fill = sf::Color::Transparent, DrawType type = DrawType::Normal);
	DRectangle(const sf::Vector2f& position, const sf::Vector2f& widthheight, const sf::Color& line, float thick = 1.0f, const sf::Color& fill = sf::Color::Transparent, DrawType type = DrawType::Normal);
	DRectangle(const DRectangle& other);
	DRectangle(DRectangle&& other);
	virtual ~DRectangle();

	bool GetIsVisible()const;
	void SetOriginCenter();
	sf::Color GetColor() const;									//GetFillColor�� ����
	virtual void SetColor(const sf::Color& color);				//SetFillColor�� ����
	virtual void SetColor(int r, int g, int b, int a = 255);	//SetFillColor�� ����
	sf::Color GetFillColor() const;
	sf::Color GetOutlineColor() const;
	void SetFillColor(const sf::Color& color);
	void SetFillColor(int r, int g, int b, int a = 255);
	void SetOutlineColor(const sf::Color& color);
	void SetOutlineColor(int r, int g, int b, int a = 255);

private:
	sf::RectangleShape m_Shape;
};


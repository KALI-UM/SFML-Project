#pragma once
#include "DShape.h"

class DRectangle :
	public DShape
{
public:
	DRectangle(const sf::Vector2f& position, const sf::Vector2f& widthheight, const sf::Color& line, float thick = 1.0f, const sf::Color& fill = sf::Color::Transparent, DrawType type = DrawType::Normal);
	DRectangle(const sf::FloatRect& rect, const sf::Color& line, float thick = 1.0f, const sf::Color& fill = sf::Color::Transparent, DrawType type = DrawType::Normal);
	DRectangle(const sf::Vector2f& position, const sf::Vector2f& widthheight, sf::Texture* tex, DrawType type = DrawType::Normal);
	DRectangle(const sf::FloatRect& rect, sf::Texture* tex, DrawType type = DrawType::Normal);
	DRectangle(const sf::Vector2f& position, const sf::Vector2f& widthheight, const std::string& filepath, DrawType type = DrawType::Normal);
	DRectangle(const sf::FloatRect& rect, const std::string& filepath, DrawType type = DrawType::Normal);
	DRectangle(const DRectangle& other);
	DRectangle(DRectangle&& other);
	virtual ~DRectangle();

	void SetSize(const sf::Vector2f& widthheight);
	void SetFloatRect(const sf::FloatRect& frect);
	virtual sf::FloatRect GetFloatRect()const;
private:
	sf::RectangleShape m_Rectangle;
	sf::FloatRect m_FloatRect;
};


#pragma once
#include "DShape.h"

class DCircle :
	public DShape
{
public:
	DCircle(const sf::Vector2f& position, float radius, const sf::Color& line, float thick = 1.0f, const sf::Color& fill = sf::Color::Transparent, int pointcnt=20, DrawType type = DrawType::Normal);
	DCircle(const sf::Vector2f& position, float radius, sf::Texture* tex, int pointcnt = 20, DrawType type = DrawType::Normal);
	DCircle(const sf::Vector2f& position, float radius, const std::string& filepath, int pointcnt = 20, DrawType type = DrawType::Normal);
	DCircle(const DCircle& other);
	DCircle(DCircle&& other);
	virtual ~DCircle();

	void SetRadius(float r);
	void SetPointCount(int cnt);
private:
	sf::CircleShape m_Circle;
};


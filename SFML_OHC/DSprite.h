#pragma once
#include "DrawableObject.h"

class DSprite :
	public DrawableObject
{
public:
	DSprite(sf::Texture* tex, DrawType type = DrawType::Normal);
	DSprite(const std::string& filepath, DrawType type = DrawType::Normal);
	DSprite(DrawType type = DrawType::Normal);
	DSprite(const DSprite& other);
	DSprite(DSprite&& other);
	virtual ~DSprite();

	void SetTexture(sf::Texture* tex);
	bool GetIsVisible()const;
	void SetOriginCenter();
	sf::Color GetColor() const;
	virtual void SetColor(const sf::Color& color);
	virtual void SetColor(int r, int g, int b, int a = 255);
	
private:
	sf::Sprite m_Sprite;
};


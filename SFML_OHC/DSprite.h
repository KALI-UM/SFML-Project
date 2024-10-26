#pragma once
#include "DrawableObject.h"

class DSprite :
	public DrawableObject
{
public:
	DSprite(sf::Texture* tex, DrawType type = DrawType::Normal);
	DSprite(const std::string& filepath, DrawType type = DrawType::Normal);
	DSprite(const sf::Vector2f& position, sf::Texture* tex, DrawType type = DrawType::Normal);
	DSprite(const sf::Vector2f& position, const std::string& filepath, DrawType type = DrawType::Normal);
	DSprite(DrawType type = DrawType::Normal);
	DSprite(const DSprite& other);
	DSprite(DSprite&& other);
	virtual ~DSprite();

	void SetTexture(sf::Texture* tex);
	void SetTexture(const std::string& filepath);
	sf::FloatRect GetFloatRect()const;
	sf::Color GetColor() const;
	void SetColor(const sf::Color& color);
	void SetColor(int r, int g, int b, int a = 255);
	virtual sf::Color GetFillColor() const;								//GetColor�� ����						
	virtual sf::Color GetOutlineColor() const;							//GetColor�� ����
	virtual void SetFillColor(const sf::Color& color);					//SetColor�� ����
	virtual void SetFillColor(int r, int g, int b, int a = 255);		//SetColor�� ����
	virtual void SetOutlineColor(const sf::Color& color);				//SetColor�� ����
	virtual void SetOutlineColor(int r, int g, int b, int a = 255);		//SetColor�� ����

private:
	sf::Sprite m_Sprite;
};


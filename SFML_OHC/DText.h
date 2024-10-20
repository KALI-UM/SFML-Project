#pragma once
#include "DrawableObject.h"

class DText :
	public DrawableObject
{
public:
	DText(sf::Font* font, const std::string& text, unsigned int charsize = 10, DrawType type = DrawType::Normal);
	DText(const std::string& filepath, const std::string& text, unsigned int charsize = 10, DrawType type = DrawType::Normal);
	DText(const sf::Vector2f& position, sf::Font* font, const std::string& text, unsigned int charsize = 10, DrawType type = DrawType::Normal);
	DText(const sf::Vector2f& position, const std::string& filepath, const std::string& text, unsigned int charsize = 10, DrawType type = DrawType::Normal);
	DText(DrawType type = DrawType::Normal);
	DText(const DText& other);
	DText(DText&& other);
	virtual ~DText();

	void SetFont(sf::Font* font);
	void SetString(const std::string& text);

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
	sf::Text m_Text;
};


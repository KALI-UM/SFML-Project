#pragma once

class Line : public sf::Drawable, public sf::Transformable
{
public:
	Line();
	~Line();
	sf::VertexArray m_Vertices;
	sf::Color m_Color;

	void setColor(const sf::Color& color);
	const sf::Color& getColor()const;
	sf::FloatRect getGlobalBounds()const;
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

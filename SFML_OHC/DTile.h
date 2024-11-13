#pragma once

class sfTile :public sf::Drawable, public sf::Transformable
{
	sfTile();
	~sfTile();
	sf::VertexArray m_Vertices;
	sf::Color m_Color;

	void setColor(const sf::Color& color);
	const sf::Color& getColor()const;
	sf::FloatRect getGlobalBounds()const;
	sf::FloatRect getLocalBounds()const;
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};


class DTile :
    public DrawableObject
{

};


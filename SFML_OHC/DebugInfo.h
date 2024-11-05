#pragma once
class DebugInfo : public sf::Drawable, public sf::Transformable
{
public:
	DebugInfo(const sf::FloatRect& target, sf::Vector2f& pos);
	~DebugInfo();
	void Update(const sf::FloatRect& target);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
	void setColor(const sf::Color& color);				//rectangle
	void setColor(int r, int g, int b, int a = 255);	//rectangle
	const sf::Color& getColor()const;					//rectangle
	void setOutlineColor(const sf::Color& color);
	void setOutlineColor(int r, int g, int b, int a = 255);	
	const sf::Color& getRectColor()const;
	void setXColor(const sf::Color& color);
	void setXColor(int r, int g, int b, int a = 255);	
	const sf::Color& getXColor()const;

private:
	sf::RectangleShape	m_Rectangle;
	sf::VertexArray		m_X;
	sf::Color			m_XColor;

	sf::FloatRect			m_Target;
	sf::Vector2f&			m_Position;
	sf::Transform			m_Transform;
};


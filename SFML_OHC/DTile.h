#pragma once

class sfTile :public sf::Drawable, public sf::Transformable
{
public:
	sfTile();
	~sfTile();
	sf::VertexArray m_Vertices;
	sf::Color m_Color;
	const sf::Texture* m_Texture;
	sf::Vector2u m_Lot;		//NxM 鸥老

	void setTexture(const sf::Texture& tex);
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
public:
	DTile(sf::Texture* tex);
	DTile(const std::string& filepath);
	DTile(const sf::Vector2f& position, sf::Texture* tex);
	DTile(const sf::Vector2f& position, const std::string& filepath);
	DTile(const DTile& other);
	DTile(DTile&& other);
	virtual ~DTile();


	void SetLot(const sf::Vector2u& lot);
	void SetTexture(sf::Texture* tex, const sf::Vector2u& lot);

	sf::FloatRect GetGlobalBounds()const;
	sf::FloatRect GetLocalBounds()const;
	sf::Color GetColor() const;								//GetFillColor客 悼老		
	void SetColor(const sf::Color& color);					//SetFillColor客 悼老
	void SetColor(int r, int g, int b, int a = 255);		//SetFillColor客 悼老
	sf::Color GetFillColor() const;
	sf::Color GetOutlineColor() const;
	void SetFillColor(const sf::Color& color);
	void SetFillColor(int r, int g, int b, int a = 255);
	void SetOutlineColor(const sf::Color& color);
	void SetOutlineColor(int r, int g, int b, int a = 255);
private:
	float		m_Unit = 64;
	sfTile		m_Tile;
};


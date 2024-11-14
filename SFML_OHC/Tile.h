#pragma once

enum class TileType
{
	Terrain,
	Building,
	Zone,
	Road,
	Rail,
	Highway,
	Underground,
	Other,
};

struct TileInfo
{
	TileType type;
	std::string name;
	std::string filepath;
};

class Tile :
	public GameObject
{
public:
	Tile();
	~Tile();

	bool Initialize() override;
	void Reset() override;
	void Update(float dt) override;
	//void LateUpdate(float dt) override;
	//void FixeUpdate(float dt) override;
	//void Release() override;
	void SetTileTransform(const sf::Vector2f& zero, const sf::Transform& trans);
	void SetCellSize(const sf::Vector2f& cell) { m_CellSize = cell; }

protected:
	std::vector<std::vector<TileInfo>> m_TileInfos;

	sf::Vector2f m_CellSize = { 100.f,100.f };
	sf::Vector2u m_CellCount = { 100,100 };
	sf::Transform m_TileTransform;


	std::string GetTypeToString(TileType type) const;
};


#pragma once
#include "GameObject.h"
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
	std::vector<std::vector<int>> m_TileInfo;
	std::vector<std::string> m_TextureId;

	sf::Vector2f m_CellSize = { 100.f,100.f };
	sf::Transform m_TileTransform;

};


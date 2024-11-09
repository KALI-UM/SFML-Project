#pragma once
#include "GameObject.h"
class TileGrid :
	public GameObject
{
public:
	TileGrid();
	~TileGrid();

	bool Initialize() override;
	void Reset() override;
	void Update(float dt) override;
	//void LateUpdate(float dt) override;
	//void FixeUpdate(float dt) override;
	//void Release() override;

	void SetCellSize(const sf::Vector2f& cell) { m_CellSize = cell; }

protected:
	sf::Vector2f m_CellSize = { 100.f,100.f };
};


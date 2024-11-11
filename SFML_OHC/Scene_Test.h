#pragma once
#include "SceneBase.h"

class TileGrid;
class Tile;
class SpriteObject;
class Scene_Test :
    public SceneBase
{
public:
    Scene_Test();
    ~Scene_Test();


protected:
	bool Initialize() override;
	//void Reset() override;
	void Enter() override;
	void Update(float dt) override;
	//void LateUpdate(float dt) override;
	//void FixedUpdate(float dt) override;
	//void Release() override;
	TileGrid* m_TileGrid;
	Tile* m_Tile;

	sf::Vector2f tilepos;
};





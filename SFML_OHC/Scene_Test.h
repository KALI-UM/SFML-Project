#pragma once
#include "SceneBase.h"

class TileGrid;
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
	TileGrid* m_Tile_1;
	TileGrid* m_Tile_2;
	SpriteObject* m_Sprite;

	sf::Transform trans;
	sf::Vector2f tilepos;
};





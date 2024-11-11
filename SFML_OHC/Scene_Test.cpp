#include "pch.h"
#include "Scene_Test.h"
#include "TileGrid.h"
#include "Tile.h"
#include "MouseCursor.h"
#include "SpriteObject.h"


Scene_Test::Scene_Test()
	:SceneBase("Test", 3, 3)
{
}

Scene_Test::~Scene_Test()
{
}

bool Scene_Test::Initialize()
{
	SetLayerViewIndex(0, 0);
	SetLayerViewIndex(1, 1);
	SetLayerViewIndex(2, 2);
	AddGameObject(2, new MouseCursor("background/1013.png",2));

	m_Tile = AddGameObject(0, new Tile());
	m_Tile->SetCellSize({ 90,90 });
	m_TileGrid = AddGameObject(1, new TileGrid());
	m_TileGrid->SetCellSize({ 90,90 });
	return false;
}

void Scene_Test::Enter()
{
	GM->SetViewSize(0, { 0,0,(float)GM->GetWindow()->getSize().x, (float)GM->GetWindow()->getSize().y });
	GM->SetViewSize(1, { 0,0,(float)GM->GetWindow()->getSize().x, (float)GM->GetWindow()->getSize().y });

	sf::Transform t;
	t.scale(1.0f, 0.5f);
	t.rotate(-45);

	m_Tile->SetTileTransform({ 0,0 }, t);
	m_TileGrid->SetTileTransform({ 0,0 }, t);
}

void Scene_Test::Update(float dt)
{
	sf::Vector2f moveoffset = { IM->GetAxisRaw(Axis::Horizontal) * dt * 100, -IM->GetAxisRaw(Axis::Vertical) * dt * 100 };
	GM->MoveView(0, moveoffset);
	GM->MoveView(1, moveoffset);
}

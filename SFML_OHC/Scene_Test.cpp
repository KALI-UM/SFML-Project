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
	SetLayerViewIndex(1, 1);
	SetLayerViewIndex(2, 2);
	AddGameObject(2, new MouseCursor("background/1013.png", 2));

	m_Tile_2 = AddGameObject(1, new TileGrid());
	m_Tile = AddGameObject(0, new Tile());
	m_Tile_2->SetCellSize({ 90,90 });
	m_Tile->SetCellSize({ 90,90 });
	//m_Tile_1 = AddGameObject(0, new TileGrid());
	return false;
}

void Scene_Test::Enter()
{
	GM->SetViewSize(0, { 0,0,(float)GM->GetWindow()->getSize().x, (float)GM->GetWindow()->getSize().y });
	GM->SetViewSize(1, { 0,0,(float)GM->GetWindow()->getSize().x, (float)GM->GetWindow()->getSize().y * 2.0f });
	GM->SetViewRotation(1, 45);

	sf::Transform t;
	t.scale(1.0f, 0.5f);
	t.rotate(-45);
	m_Tile->SetTileTransform({0,0}, t);
	//m_Tile_1->setPosition(0, 0);
	//m_Tile_1->setRotation(-45);
	//m_Tile_1->setScale(0.79f, 0.79f);
	m_Tile_2->setPosition(GM->GetScreenToViewPos(1, GM->GetViewToScreenPos(0, { 0,0 })));
}

void Scene_Test::Update(float dt)
{
	sf::Vector2f tilepos = IM->GetMouseViewPos(1);

	sf::Vector2f viewx = GM->GetScreenToViewPos(1, sf::Vector2i(1, 0)) - GM->GetScreenToViewPos(1, sf::Vector2i(0, 0));
	sf::Vector2f viewy = GM->GetScreenToViewPos(1, sf::Vector2i(0, 1)) - GM->GetScreenToViewPos(1, sf::Vector2i(0, 0));

	sf::Vector2f moveoffset = { IM->GetAxisRaw(Axis::Horizontal) * dt * 100, -IM->GetAxisRaw(Axis::Vertical) * dt * 100 };
	GM->MoveView(0, moveoffset);
	GM->MoveView(1, viewx * moveoffset.x + viewy * moveoffset.y);
}

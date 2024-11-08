#include "pch.h"
#include "Scene_Test.h"
#include "TileGrid.h"
#include "MouseCursor.h"
#include "SpriteObject.h"


Scene_Test::Scene_Test()
	:SceneBase("Test", 2, 2)
{
}

Scene_Test::~Scene_Test()
{
}

bool Scene_Test::Initialize()
{
	SetLayerViewIndex(1, 1);
	//AddGameObject(0, new MouseCursor("background/1013.png"));
	m_Sprite = AddGameObject(0, new SpriteObject("background/1013.png"));
	m_Tile_1 = AddGameObject(0, new TileGrid());
	m_Tile_2 = AddGameObject(1, new TileGrid());

	sf::Transform t;
	t.scale({ 1.f, 0.5f });
	t.rotate(45);
	trans = t.getInverse();

	return false;
}

void Scene_Test::Enter()
{
	//GM->GetView(1)->setRotation(45);
	//GM->GetView(1)->setSize({ (float)GM->GetWindow()->getSize().x, (float)GM->GetWindow()->getSize().y * 2.0f });
	GM->SetViewSize(1, { 0,0,(float)GM->GetWindow()->getSize().x, (float)GM->GetWindow()->getSize().y * 2.0f });
	GM->SetViewRotation(1, 45);
}

void Scene_Test::Update(float dt)
{
	//tilepos = trans.transformPoint(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);
	//tilepos = trans.transformPoint(MOUSEPOS);
	sf::Vector2f tilepos = IM->GetMouseViewPos(1);
	m_Sprite->setPosition(tilepos);
	std::cout << "x	" << (int)(tilepos.x / 100) << ", y	" << (int)(tilepos.y / 100) << std::endl;

	//sf::Vector2f offset = GM->GetScreenToViewPos(1, sf::Vector2i(IM->GetAxisRaw(Axis::Horizontal) * dt * 100, -IM->GetAxisRaw(Axis::Vertical) * dt * 100));

	//GM->MoveView(0, { IM->GetAxisRaw(Axis::Horizontal) * dt * 100, -IM->GetAxisRaw(Axis::Vertical) * dt * 100 });
	//GM->MoveView(1, offset);
}

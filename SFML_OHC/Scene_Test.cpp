#include "pch.h"
#include "Scene_Test.h"
#include "GameObject.h"
#include "DSprite.h"
#include "DAnimation.h"
#include "DRectangle.h"
#include "DCircle.h"
#include "DText.h"

Scene_Test::Scene_Test()
{
}

Scene_Test::~Scene_Test()
{
}

bool Scene_Test::Initialize()
{
	obj1 = new GameObject();
	obj2 = new GameObject();
	obj3 = new GameObject();
	obj4 = new GameObject();
	obj5 = new GameObject();
	obj6 = new GameObject();

	DSprite* spt1 = new DSprite("resource/ex.png");
	DSprite* spt2 = new DSprite("resource/ex.png");
	obj1->SetDrawable(spt1);
	obj2->SetDrawable(spt2);
	obj2->GetDrawable()->SetOriginCenter();
	DAnimation* aaa = new DAnimation("resource/Warrior_TotalAni.png", sf::Vector2u(16, 7), 100.f);
	aaa->SetFrame(0, 3);
	obj3->SetDrawable(aaa);

	obj1->GetDrawable()->SetColor(200, 0, 0);
	DRectangle* rect = new DRectangle(sf::Vector2f(100, 100), sf::Vector2f(100, 100), sf::Color::White);
	obj4->SetDrawable(rect);
	DCircle* circle = new DCircle(sf::Vector2f(100, 100), 300, sf::Color::Yellow, 20, sf::Color::Blue);
	obj5->SetDrawable(circle);
	DText* text = new DText(sf::Vector2f(500, 500), "resource/KOMIKAP_.ttf", "rdfssf",50, DrawType::Debug);
	obj6->SetDrawable(text);
	m_GameObjects.push_back(obj1);
	m_GameObjects.push_back(obj2);
	m_GameObjects.push_back(obj3);
	m_GameObjects.push_back(obj4);
	m_GameObjects.push_back(obj5);
	m_GameObjects.push_back(obj6);
	return true;
}

void Scene_Test::Update(float dt)
{
	obj2->GetDrawable()->Transform()->setPosition(InputManager::GetInstance()->GetMousePos().x, InputManager::GetInstance()->GetMousePos().y);
	obj3->GetDrawable()->Update(dt);
}

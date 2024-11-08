#include "pch.h"
#include "Scene_Lobby.h"
#include "Background_Lobby.h"
#include "MouseCursor.h"
#include "DustEffect.h"
#include "SoundPlayer.h"
#include "GameStart.h"
#include "Button.h"

Scene_Lobby::Scene_Lobby()
	:SceneBase("Lobby", 2, 2)
{
}

Scene_Lobby::~Scene_Lobby()
{
}

bool Scene_Lobby::Initialize()
{
	SetLayerViewIndex(1, 1);
	m_LobbyImage = AddGameObject(0, new Background_Lobby());
	m_Cursor = AddGameObject(1, new MouseCursor());
	m_Effects.resize(5);
	for (auto& eff : m_Effects)
	{
		eff = new DustEffect();
		AddGameObject(0, eff);
	}

	m_GameStart = AddGameObject(0, new GameStart());
	m_Button = AddGameObject(1, new Button());
	
	m_Button->SetOverlayFunc([]() { std::cout << "overlay" << std::endl; });
	//m_Button->SetClickedFunc([]() {GM->MoveViewport(0, sf::Vector2f(200, 0)); });
	return false;
}

void Scene_Lobby::Reset()
{
	m_FadeSpeed = 3.0f;
	m_Button->SetButtonPosition({ 0, 0 });
}

void Scene_Lobby::Enter()
{
	GM->SetViewSize(0, sf::FloatRect(0, 0, GM->GetWindow()->getSize().x, GM->GetWindow()->getSize().y));
	GM->SetViewSize(1, sf::FloatRect(0, 0, GM->GetWindow()->getSize().x, GM->GetWindow()->getSize().y));
	//GM->SetViewportSize(0, sf::FloatRect(0.f, 0.f, 2.f, 2.f));
	//GetSoundPlayer()->PlayBGM("sound/my_friend_dragon.mp3", true, 5);
}

void Scene_Lobby::Update(float dt)
{
	if (IM->GetMouseDown(sf::Mouse::Left) || IM->GetKeyDown(sf::Keyboard::Enter))
	{
		m_LobbyImage->FadeOutBackGround(m_FadeSpeed);
		for (auto& eff : m_Effects)
		{
			if (!eff->GetIsValid())
			{
				eff->Effect(1.f, { (float)MOUSEPOS.x,(float)MOUSEPOS.y }, 10.f);
				break;
			}
		}
	}

	GM->MoveView(0, sf::Vector2f(200 * IM->GetAxisRaw(Axis::Horizontal) * dt, 0));
	GM->MoveView(0, sf::Vector2f(0, -200 * IM->GetAxisRaw(Axis::Vertical) * dt));
}

void Scene_Lobby::Release()
{
}

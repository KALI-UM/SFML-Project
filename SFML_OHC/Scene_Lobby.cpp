#include "pch.h"
#include "Scene_Lobby.h"
#include "Background_Lobby.h"
#include "MouseCursor.h"
#include "DustEffect.h"
#include "SoundPlayer.h"
#include "GameStart.h"
#include "Button.h"

Scene_Lobby::Scene_Lobby()
	:SceneBase("Lobby")
{
}

Scene_Lobby::~Scene_Lobby()
{
}

bool Scene_Lobby::Initialize()
{
	m_LobbyImage = new Background_Lobby();
	m_GameObjects.push_back(m_LobbyImage);
	m_GameObjects.push_back(new MouseCursor());
	m_Effects.resize(5);
	for (auto& eff : m_Effects)
	{
		eff = new DustEffect();
		m_GameObjects.push_back(eff);
	}

	m_GameStart = new GameStart();
	m_GameObjects.push_back(m_GameStart);

	return false;
}

void Scene_Lobby::Reset()
{
	m_FadeSpeed = 3.0f;
	m_Start = false;
}

void Scene_Lobby::Update(float dt)
{
	if (!m_Start)
		m_SoundPlayer->PlayBGM("sound/my_friend_dragon.mp3");
	m_Start = true;
	if (IM->GetMouseDown(sf::Mouse::Left) || IM->GetKeyDown(sf::Keyboard::Enter))
	{
		m_LobbyImage->FadeOutBackGround(m_FadeSpeed);
		m_SoundPlayer->FadeOutBGM("sound/my_friend_dragon.mp3", 3);
		for (auto& eff : m_Effects)
		{
			if (!eff->GetIsValid())
			{
				eff->Effect(1.f, { (float)MOUSEPOS.x,(float)MOUSEPOS.y }, 10.f);
				break;
			}
		}
	}
}

void Scene_Lobby::Release()
{
}

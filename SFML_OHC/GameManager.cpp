#include "pch.h"
#include "DrawableObject.h"
#include "SFML/Window.hpp"
#include "Scene_Test.h"
#include "Scene_Lobby.h"
#include "Scene_Test.h"


GameManager::GameManager()
	:m_MainWindow(nullptr),
	//m_RTextureManager(ResourceManager<sf::Texture>::GetInstance()),
	//m_RFontManager(ResourceManager<sf::Font>::GetInstance()),
	m_InputManager(InputManager::GetInstance()),
	m_SceneManager(SceneManager::GetInstance())
{
}

//ResourceManager<sf::Texture>* GameManager::GetTextureManager() const
//{
//	return m_RTextureManager;
//}
//
//ResourceManager<sf::Font>* GameManager::GetFontManager() const
//{
//	return m_RFontManager;
//}

InputManager* GameManager::GetInputManager() const
{
	return m_InputManager;
}

SceneManager* GameManager::GetSceneManager() const
{
	return m_SceneManager;
}

bool GameManager::Initialize(sf::RenderWindow* window)
{
	m_MainWindow = window;
	bool success = true;
	//m_MainWindow->setMouseCursorVisible(false);
	success &= GetInputManager()->Initialize();
	success &= GetSceneManager()->Initialize();

	m_Volume = 0.8f;

	Scene_Test* lobby = new Scene_Test();
	SM->PushScene(lobby);
	SM->SetCurrentScene(lobby->GetName());
	lobby->ENTER();
	return success;
}

void GameManager::UpdateEvent(const sf::Event& ev)
{
	GetInputManager()->UpdateEvent(ev);
}

void GameManager::Update(float dt)
{
	if (IM->GetKeyDown(sf::Keyboard::F1))
	{
		std::cout << "Play Mode - Debug\n";
		m_GameMode = GameMode::Debug;
	}
	if (IM->GetKeyDown(sf::Keyboard::F2))
	{
		std::cout << "Play Mode - Normal\n";
		m_GameMode = GameMode::Normal;
	}

	GetInputManager()->Update(dt);
	GetSceneManager()->Update(dt);
	GetSceneManager()->PreRender();
}

void GameManager::Render()
{
	for (int i = 0; i < m_Views.size(); i++)
	{
		m_MainWindow->setView(m_Views[i].view);
		auto& currDrawQue = m_Views[i].drawQue;
		while (!currDrawQue.empty())
		{
			m_MainWindow->draw(*currDrawQue.top()->GetDrawable());
			currDrawQue.pop();
		}
#ifdef _DEBUG
		m_MainWindow->setView(m_DebugViews[i].view);
		auto& currDebugDrawQue = m_DebugViews[i].drawQue;
		while (!currDebugDrawQue.empty())
		{
			m_MainWindow->draw((sf::Drawable&)*currDebugDrawQue.front());
			currDebugDrawQue.pop();
		}
#endif // _DEBUG
	}
	GetSceneManager()->PostRender();
}

void GameManager::LateUpdate(float dt)
{
	GetSceneManager()->LateUpdate(dt);
}

void GameManager::FixedUpdate(float dt)
{
	GetSceneManager()->FixedUpdate(dt);
}

sf::RenderWindow* GameManager::GetWindow()
{
	return m_MainWindow;
}

sf::View* GameManager::GetView(int index)
{
	return &m_Views[index].view;
}

void GameManager::ResizeViews(unsigned int cnt)
{
	m_Views.resize(cnt);
	m_Views[0].view.reset(sf::FloatRect(0, 0, m_MainWindow->getSize().x, m_MainWindow->getSize().y));
#ifdef _DEBUG
	m_DebugViews.resize(cnt);
	m_DebugViews[0].view.reset(sf::FloatRect(0, 0, m_MainWindow->getSize().x, m_MainWindow->getSize().y));
#endif // _DEBUG
}

void GameManager::SetViewSize(int index, const sf::FloatRect& rect)
{
	m_Views[index].view.reset(rect);
#ifdef _DEBUG
	m_DebugViews[index].view.reset(rect);
#endif // _DEBUG
}

void GameManager::SetViewportSize(int index, const sf::FloatRect& rect)
{
	m_Views[index].view.setViewport(rect);
#ifdef _DEBUG
	m_DebugViews[index].view.setViewport(rect);
#endif // _DEBUG
}

void GameManager::SetViewportCenter(int index, const sf::Vector2f& pos)
{
	m_Views[index].view.setCenter(pos);
#ifdef _DEBUG
	m_DebugViews[index].view.setCenter(pos);
#endif // _DEBUG
}

void GameManager::MoveViewport(int index, const sf::Vector2f& offset)
{
	m_Views[index].view.move(offset);
#ifdef _DEBUG
	m_DebugViews[index].view.move(offset);
#endif // _DEBUG
}

void GameManager::PushDrawableObject(int viewindex, DrawableObject* dobj)
{
	m_Views[viewindex].drawQue.push(dobj);
}

void GameManager::PushDebugDrawObject(int viewindex, DebugInfo* dobj)
{
	m_DebugViews[viewindex].drawQue.push(dobj);
}

const GameMode& GameManager::GetGameMode() const
{
	return m_GameMode;
}

float GameManager::GetGlobalVolume() const
{
	return m_Volume;
}

void GameManager::SetGlobalVolume(float volume)
{
	m_Volume = volume;
}

bool PriorityComp::operator()(DrawableObject*& lhs, DrawableObject*& rhs)
{
	return DrawableObject::YCompare(lhs, rhs);
}

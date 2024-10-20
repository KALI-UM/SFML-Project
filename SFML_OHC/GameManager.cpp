#include "pch.h"
#include "DrawableObject.h"

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
	success &= GetInputManager()->Initialize();
	success &= GetSceneManager()->Initialize();
	return success;
}

void GameManager::UpdateEvent(const sf::Event& ev)
{
	GetInputManager()->Update(ev);
}

void GameManager::Update(float dt)
{
	GetSceneManager()->Update(dt);
	GetSceneManager()->PushToDrawQue();
}

void GameManager::Render()
{
	while (!m_DrawQue.empty())
	{
		m_MainWindow->draw(*m_DrawQue.top()->GetDrawable());
		m_DrawQue.pop();
	}
}

void GameManager::LateUpdate()
{
	GetInputManager()->Clear();
}

sf::RenderWindow* GameManager::GetWindow()
{
	return m_MainWindow;
}

void GameManager::PushDrawableObject(DrawableObject* dobj)
{
	m_DrawQue.push(dobj);
}

bool PriorityComp::operator()(DrawableObject*& lhs, DrawableObject*& rhs)
{
	return DrawableObject::YCompare(lhs, rhs);
}

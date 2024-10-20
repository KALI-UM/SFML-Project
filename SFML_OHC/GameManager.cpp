#include "pch.h"
#include "DrawableObject.h"

GameManager::GameManager()
	:m_MainWindow(nullptr)
{
}

ResourceManager* GameManager::GetResourceManager() const
{
	return ResourceManager::GetInstance();
}

InputManager* GameManager::GetInputManager() const
{
	return InputManager::GetInstance();
}

SceneManager* GameManager::GetSceneManager() const
{
	return SceneManager::GetInstance();
}

bool GameManager::Initialize(sf::RenderWindow* window)
{
	m_MainWindow = window;
	bool success = true;
	success &= GetResourceManager()->Initialize();
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

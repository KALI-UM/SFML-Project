#include "pch.h"
#include "Scene_Test.h"

GameManager::GameManager()
	:m_MainWindow(nullptr)
{
}

bool GameManager::Initialize(sf::RenderWindow* window)
{
	m_MainWindow = window;
	bool success = true;
	//m_MainWindow->setMouseCursorVisible(false);
	success &= SCENE_MGR->Initialize();

	Scene_Test* lobby = new Scene_Test();
	SCENE_MGR->PushScene(lobby);
	SCENE_MGR->SetCurrentScene(lobby->GetName());
	lobby->RESET();
	lobby->ENTER();
	return success;
}

void GameManager::UpdateEvent(const sf::Event& ev)
{
}

void GameManager::Update(float dt)
{
	if (INPUT_MGR->GetKeyDown(sf::Keyboard::F1))
	{
		std::cout << "Play Mode - Debug\n";
		m_GameMode = GameMode::Debug;
	}
	if (INPUT_MGR->GetKeyDown(sf::Keyboard::F2))
	{
		std::cout << "Play Mode - Normal\n";
		m_GameMode = GameMode::Normal;
	}

	SCENE_MGR->Update(dt);
	SCENE_MGR->PreRender();
}

void GameManager::Render()
{
	const sf::View& defaultView = m_MainWindow->getView();
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
	m_MainWindow->setView(defaultView);
	SCENE_MGR->PostRender();
}

void GameManager::LateUpdate(float dt)
{
	SCENE_MGR->LateUpdate(dt);
}

void GameManager::FixedUpdate(float dt)
{
	SCENE_MGR->FixedUpdate(dt);
}

void GameManager::ImGuiUpdate()
{
	SCENE_MGR->ImGuiUpdate();
}

sf::RenderWindow* GameManager::GetWindow()
{
	return m_MainWindow;
}

sf::View* GameManager::GetView(int index)
{
	return &m_Views[index].view;
}

const sf::FloatRect& GameManager::GetViewRect(int index)
{
	return m_Views[index].viewRect;
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

sf::Vector2f GameManager::GetScreenToViewPos(int index, const sf::Vector2i& screenPos)
{
	return m_MainWindow->mapPixelToCoords(screenPos, m_Views[index].view);
}

sf::Vector2i GameManager::GetViewToScreenPos(int index, const sf::Vector2f& viewPos)
{
	return m_MainWindow->mapCoordsToPixel(viewPos, m_Views[index].view);
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

void GameManager::SetViewCenter(int index, const sf::Vector2f& pos)
{
	m_Views[index].view.setCenter(pos);
#ifdef _DEBUG
	m_DebugViews[index].view.setCenter(pos);
#endif // _DEBUG
}

void GameManager::MoveView(int index, const sf::Vector2f& offset)
{
	m_Views[index].view.move(offset);
#ifdef _DEBUG
	m_DebugViews[index].view.move(offset);
#endif // _DEBUG
}

void GameManager::SetViewRotation(int index, float rot)
{
	m_Views[index].view.setRotation(rot);
#ifdef _DEBUG
	m_DebugViews[index].view.setRotation(rot);
#endif // _DEBUG
}

void GameManager::RotateView(int index, float rot)
{
	m_Views[index].view.rotate(rot);
#ifdef _DEBUG
	m_DebugViews[index].view.rotate(rot);
#endif // _DEBUG
}

void GameManager::UpdateViewRect()
{
	for (auto& view : m_Views)
	{
		view.viewRect = sf::FloatRect(view.view.getCenter() - view.view.getSize() / 2.0f, view.view.getSize());
	}
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

bool PriorityComp::operator()(DrawableObject*& lhs, DrawableObject*& rhs)
{
	return DrawableObject::YCompare(lhs, rhs);
}

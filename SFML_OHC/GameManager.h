#pragma once
#include "Singleton.h"

namespace sf
{
	class RenderWindow;
}

//class ResourceManager<sf::Texture>;
//class ResourceManager<sf::Font>;

class InputManager;
class SceneManager;
class DrawableObject;

struct PriorityComp
{
	bool operator()(DrawableObject*& lhs, DrawableObject*& rhs);
};

class GameManager :
	public Singleton<GameManager>
{
public:
	GameManager();
	//ResourceManager<sf::Texture>* GetTextureManager() const;
	//ResourceManager<sf::Font>* GetFontManager() const;
	InputManager* GetInputManager() const;
	SceneManager* GetSceneManager() const;

	bool Initialize(sf::RenderWindow* window);
	void UpdateEvent(const sf::Event& ev);
	void Update(float dt);
	void Render();
	void LateUpdate();


	sf::RenderWindow* GetWindow();
	void PushDrawableObject(DrawableObject* dobj);
private:
	sf::RenderWindow* m_MainWindow;
	std::priority_queue<DrawableObject*, std::vector<DrawableObject*>, PriorityComp> m_DrawQue;

	//ResourceManager<sf::Texture>* const		m_RTextureManager;
	//ResourceManager<sf::Font>* const		m_RFontManager;
	InputManager* const						m_InputManager;
	SceneManager* const						m_SceneManager;
};


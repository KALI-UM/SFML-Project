#pragma once
#include "Singleton.h"

namespace sf
{
	class RenderWindow;
}

//class ResourceManager<sf::Texture>;
//class ResourceManager<sf::Font>;

enum class GameMode
{
	Debug,
	Cheat,
	Normal
};

class InputManager;
class SceneManager;
class DrawableObject;
class DebugInfo;

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

	bool Initialize(sf::RenderWindow* window, int viewcnt);
	void UpdateEvent(const sf::Event& ev);
	void Update(float dt);
	void Render();
	void LateUpdate();


	sf::RenderWindow* GetWindow();
	void PushDrawableObject(int viewindex, DrawableObject* dobj);
	void PushDebugDrawObject(DebugInfo* dobj);
	const GameMode& GetGameMode()const;
	float GetGlobalVolume()const;
	void SetGlobalVolume(float volume);
private:
	sf::RenderWindow* m_MainWindow;

	std::vector<sf::View> m_Views;
	std::vector <std::priority_queue<DrawableObject*, std::vector<DrawableObject*>, PriorityComp>> m_DrawQues;
	sf::View				m_DebugView;
	std::queue<DebugInfo*>	m_DebugDrawQue;
	//ResourceManager<sf::Texture>* const	m_RTextureManager;
	//ResourceManager<sf::Font>* const		m_RFontManager;
	InputManager* const						m_InputManager;
	SceneManager* const						m_SceneManager;

	GameMode								m_GameMode;
	float									m_Volume;
};


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

	bool Initialize(sf::RenderWindow* window);
	void UpdateEvent(const sf::Event& ev);
	void Update(float dt);
	void Render();
	void LateUpdate(float dt);
	void FixedUpdate(float dt);

	sf::RenderWindow* GetWindow();
	sf::View* GetView(int index);
	void ResizeViews(unsigned int cnt);

	sf::Vector2f GetScreenToViewPos(int index, const sf::Vector2i& screenPos);
	sf::Vector2i GetViewToScreenPos(int index, const sf::Vector2f& viewPos);


	void SetViewSize(int index, const sf::FloatRect& rect);
	void SetViewportSize(int index, const sf::FloatRect& rect);
	void SetViewCenter(int index, const sf::Vector2f& pos);
	void MoveView(int index, const sf::Vector2f& offset);
	void SetViewRotation(int index, float rot);
	void RotateView(int index, float rot);

	void PushDrawableObject(int viewindex, DrawableObject* dobj);
	void PushDebugDrawObject(int viewindex, DebugInfo* dobj);

	const GameMode& GetGameMode()const;
	float GetGlobalVolume()const;
	void SetGlobalVolume(float volume);

private:
	sf::RenderWindow* m_MainWindow;

	InputManager* const						m_InputManager;
	SceneManager* const						m_SceneManager;

	GameMode								m_GameMode;
	float									m_Volume;


	struct ViewDrawInfo
	{
		sf::View							view;
		std::priority_queue<DrawableObject*, std::vector<DrawableObject*>, PriorityComp> drawQue;
	};
	std::vector<ViewDrawInfo>				m_Views;

	struct ViewDebugInfo
	{
		sf::View							view;
		std::queue<DebugInfo*>				drawQue;
	};
	std::vector<ViewDebugInfo>				m_DebugViews;
};


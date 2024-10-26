#include "GameObject.h"

class DRectangle;
class DSprite;
class DText;
class Button :
	public GameObject
{
public:
	Button();
	~Button();

	bool Initialize();
	void Reset();
	void Update(float dt);

	void SetButtonPosition(const sf::Vector2f& pos);
	void SetButtonText(const std::string& text);
	void SetButtonColor(const sf::Color& on, const sf::Color& off);

	bool GetIsOveraying()const;
	bool GetIsClicked()const;

private:

	bool m_IsOverlaying;
	bool m_IsClicked;

	DRectangle* m_ButtonArea;
	DSprite*	m_ButtonSprite;
	DText*		m_ButtonText;

	sf::Color	m_DefaultColor;
	sf::Color	m_OverayColor;
};

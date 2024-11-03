#pragma once

class DrawableObject;
class SceneBase;
class DebugInfo;
class GameObject
{
public:
	const int	m_Id;
public:
	GameObject();
	GameObject(const GameObject& other);
	GameObject(GameObject&& other) noexcept;
	virtual ~GameObject();
	bool operator==(const GameObject& rhs);

	bool INITIALIZE();
	void RESET();
	void UPDATE(float dt);
	void RELEASE();

	void SetIsValid(bool value);
	bool GetIsValid()const;
	bool GetIsVisible()const;
	bool GetIsVisible(size_t index)const;

	DrawableObject* GetDrawable(size_t index = 0) const;
	DrawableObject* GetDrawable(const std::string& name) const;
	void SetDrawable(DrawableObject* dobj);
	int GetDrawbleCount()const { return (int)m_Drawable.size(); }
	bool GetIsMovable() const { return m_IsMovable; }

protected:
	virtual bool Initialize();
	virtual void Reset();
	virtual void Update(float dt);
	virtual void Release();

private:
	bool			m_IsValid;
	const bool		m_IsMovable;


	std::vector<DrawableObject*> m_Drawable;
	sf::Vector2f	m_Position;
	sf::Vector2f	m_Origin;
	sf::Vector2f	m_Scale;
	float			m_Rotation;

public:

	void SetPosition(const sf::Vector2f& position);
	void SetOrigin(const sf::Vector2f& origin);
	void SetScale(const sf::Vector2f& scale);
	void SetRotation(float angle);
	sf::Vector2f GetPosition() const;
	sf::Vector2f GetOrigin() const;
	sf::Vector2f GetScale() const;
	float GetRotation() const;

private:
	static int m_GameObjectsCount;
	static int m_IdNumber;
};


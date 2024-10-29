#pragma once

class DrawableObject;
class DebugInfo;
class GameObject
{
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
	bool GetIsVisible(size_t index = 0)const;

	DrawableObject* GetDrawable(size_t index = 0) const;
	DrawableObject* GetDrawable(const std::string& name) const;
	void SetDrawable(DrawableObject* dobj);
	int GetDrawbleCount()const;

protected:
	virtual bool Initialize();
	virtual void Reset();
	virtual void Update(float dt);
	virtual void Release();

private:
	const int	m_Id;
	bool		m_IsValid;

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


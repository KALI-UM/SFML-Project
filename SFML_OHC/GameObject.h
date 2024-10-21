#pragma once

class DrawableObject;
class GameObject
{
public:
	GameObject();
	GameObject(const GameObject& other);
	GameObject(GameObject&& other) noexcept;
	virtual ~GameObject();
	bool operator==(const GameObject& rhs);

	virtual bool Initialize();
	virtual void Update(float dt);

	void SetIsValid(bool value);
	bool GetIsValid()const;
	bool GetIsVisible()const;

	
	DrawableObject* GetDrawable() const;
	void SetDrawable(DrawableObject* dobj);

private:
	const int	m_Id;
	bool		m_IsValid;

	DrawableObject* m_Drawable = nullptr;

	static int m_GameObjectsCount;
	static int m_IdNumber;
};


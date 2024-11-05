#pragma once
#include "Transform.h"

class DrawableObject;
class SceneBase;
class DebugInfo;
class GameObject :public Transform
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
	void SetDrawable(DrawableObject* dobj, bool isChild = true);
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

private:
	static int m_GameObjectsCount;
	static int m_IdNumber;
};


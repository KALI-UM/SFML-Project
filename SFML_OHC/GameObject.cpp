#include "pch.h"
#include "GameObject.h"
#include <SFML/Graphics.hpp>
#include "DrawableObject.h"

int GameObject::m_GameObjectsCount = 1;
int GameObject::m_IdNumber = 0;

GameObject::GameObject()
	:m_Id(m_IdNumber++), m_IsValid(true), m_IsMovable(true)
{
	Transform::Init(nullptr);
	m_GameObjectsCount++;
}

GameObject::GameObject(const GameObject& other)
	:m_Id(m_IdNumber++), m_IsValid(other.m_IsValid), m_IsMovable(other.m_IsMovable)
{
	Transform::Init(other, nullptr);
	m_GameObjectsCount++;
}

GameObject::GameObject(GameObject&& other)noexcept
	:m_Id(other.m_Id), m_IsValid(other.m_IsValid), m_Drawable(other.m_Drawable),m_IsMovable(other.m_IsMovable)
{
	//�̿�
	Transform::Init(other, nullptr);
	other.m_Drawable.clear();
	other.SetIsValid(false);
}

GameObject::~GameObject()
{
	m_GameObjectsCount--;
}

bool GameObject::INITIALIZE()
{
	bool result = Initialize();
	RESET();
	return result;
}

void GameObject::RESET()
{
	Reset();
}

void GameObject::UPDATE(float dt)
{
	Update(dt);

	for (auto& drawable : m_Drawable)
	{
		drawable->Update(dt);
	}
}

void GameObject::RELEASE()
{
	Release();

	for (auto& drawable : m_Drawable)
	{
		delete drawable;
	}
}

bool GameObject::Initialize()
{
	return true;
}

void GameObject::Reset()
{
}

void GameObject::Update(float dt)
{
}

void GameObject::Release()
{
}

void GameObject::SetIsValid(bool value)
{
	m_IsValid = value;
}

bool GameObject::GetIsValid() const
{
	return m_IsValid;
}

bool GameObject::GetIsVisible() const
{
	return GetIsValid() && GetDrawbleCount()!=0;
}

bool GameObject::GetIsVisible(size_t index) const
{
	//return GetIsValid() && GetDrawable(index) && GetDrawable(index)->GetIsVisible();
	return GetIsValid() && GetDrawable(index) && GetDrawable(index)->GetIsValid();
}

DrawableObject* GameObject::GetDrawable(size_t index)const
{
	if (index >= m_Drawable.size())return nullptr;
	return m_Drawable[index];
}

DrawableObject* GameObject::GetDrawable(const std::string& name) const
{
	for (auto& drawable : m_Drawable)
	{
		if (drawable->GetName() == name)
			return drawable;
	}
	return nullptr;
}

void GameObject::SetDrawable(DrawableObject* dobj, bool isChild )
{
	if (isChild)
		SetChild(dobj);
	m_Drawable.push_back(dobj);
}


#include "pch.h"
#include "GameObject.h"
#include <SFML/Graphics.hpp>
#include "DrawableObject.h"

int GameObject::m_GameObjectsCount = 1;
int GameObject::m_IdNumber = 0;

GameObject::GameObject()
	:m_Id(m_IdNumber++), m_IsValid(true)
{
	m_GameObjectsCount++;
}

GameObject::GameObject(const GameObject& other)
	:m_Id(m_IdNumber++), m_IsValid(other.m_IsValid)
{
	m_GameObjectsCount++;
}

GameObject::GameObject(GameObject&& other)noexcept
	:m_Id(other.m_Id), m_IsValid(other.m_IsValid), m_Drawable(other.m_Drawable)
{
	//¹Ì¿Ï
	other.m_Drawable = nullptr;
	other.SetIsValid(false);
}

GameObject::~GameObject()
{
	m_GameObjectsCount--;
	delete m_Drawable;
}

bool GameObject::Initialize()
{
	return false;
}

void GameObject::Update(float dt)
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
	return GetIsValid() && GetDrawable() && GetDrawable()->GetIsVisible();
}

DrawableObject* GameObject::GetDrawable()const
{
	return m_Drawable;
}

void GameObject::SetDrawable(DrawableObject* dobj)
{
	m_Drawable = dobj;
}


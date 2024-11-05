#include "pch.h"
#include "Transform.h"

//Transform::Transform(sf::Transformable* transformable)
//	//:m_T(transformable),
//	//m_ParentPosition({ 0,0 }), m_LocalPosition(m_T->getPosition()),
//	//m_ParentRotation(0), m_LocalRotation(m_T->getRotation()),
//	//m_ParentScale({ 1,1 }), m_LocalScale(m_T->getScale())
//{
//}
//
//Transform::Transform(const Transform& other, sf::Transformable* transformable)
//	//:m_T(transformable),
//	//m_ParentPosition(other.getParentPosition()), m_LocalPosition(other.getLocalPosition()),
//	//m_ParentRotation(other.getParentRotation()), m_LocalRotation(other.getLocalRotation()),
//	//m_ParentScale(other.getParentScale()), m_LocalScale(other.getLocalScale())
//{
//}
//
//Transform::Transform(Transform&& other, sf::Transformable* transformable)
//	//:m_T(transformable),
//	//m_ParentPosition(other.getParentPosition()), m_LocalPosition(other.getLocalPosition()),
//	//m_ParentRotation(other.getParentRotation()), m_LocalRotation(other.getLocalRotation()),
//	//m_ParentScale(other.getParentScale()), m_LocalScale(other.getLocalScale())
//{
//}

void Transform::Init(sf::Transformable* transformable)
{
	m_T = transformable;
	if (!m_T)m_T = new sf::Transformable();
	Reset();
	m_LocalScale = { 1,1 };
}

void Transform::Init(const Transform& other, sf::Transformable* transformable)
{
	m_T = transformable;
	if (!m_T)m_T = new sf::Transformable();
	m_ParentPosition = other.getParentPosition();
	m_LocalPosition = other.getLocalPosition();
	m_ParentRotation = other.getParentRotation();
	m_LocalRotation = other.getLocalRotation();
	m_ParentScale = other.getParentScale();
	m_LocalScale = other.getLocalScale();
}

void Transform::Reset()
{
	ResetParentTransform();
	ResetLocalTransform();
}

void Transform::ResetParentTransform()
{
	if (m_Parent)
	{
		m_ParentPosition = m_Parent->getPosition();
		m_ParentRotation = m_Parent->getRotation();
		m_ParentScale = m_Parent->getScale();
	}
	else
	{
		m_ParentPosition = { 0,0 };
		m_ParentRotation = 0;
		m_ParentScale = { 1,1 };
	}
}

void Transform::ResetLocalTransform()
{
	m_LocalPosition = m_T->getPosition();
	m_LocalRotation = m_T->getRotation();
	m_LocalScale = m_T->getScale();
}

void Transform::SetChild(Transform* child)
{
	child->m_Parent = this;
	m_Children.push_back(child);
	child->setParentPosition(getPosition());
	child->setParentRotation(getRotation());
	child->setParentScale(getScale());
}

void Transform::RemoveChild(Transform* child)
{
	for (auto t = m_Children.begin(); t != m_Children.end(); t++)
	{
		if (*t == child)
		{
			child->m_Parent = nullptr;
			child->setParentPosition({ 0,0 });
			child->setParentRotation(0);
			child->setParentScale({ 1,1 });
			m_Children.erase(t);
			break;
		}
	}
}

void Transform::SetParent(Transform* parent)
{
	if (m_Parent)
	{
		m_Parent->RemoveChild(this);
	}
	m_Parent = parent;
	m_Parent->SetChild(this);
}

void Transform::setPosition(const sf::Vector2f& pos)
{
	m_LocalPosition = pos - m_ParentPosition;
	setPosition();
}

void Transform::setPosition(float posx, float posy)
{
	setPosition(sf::Vector2f(posx, posy));
}

void Transform::setPosition(const sf::Vector2f& parentpos, const sf::Vector2f& localpos)
{
	m_ParentPosition = parentpos;
	m_LocalPosition = localpos;
	setPosition();
}

void Transform::setParentPosition(const sf::Vector2f& parentpos)
{
	m_ParentPosition = parentpos;
	setPosition();
}

void Transform::setLocalPosition(const sf::Vector2f& localpos)
{
	m_LocalPosition = localpos;
	setPosition();
}

void Transform::move(const sf::Vector2f& pos)
{
	m_LocalPosition += pos;
	m_T->move(pos);
	for (auto& child : m_Children)
	{
		child->setParentPosition(getPosition());
	}
}

void Transform::setPosition()
{
	m_T->setPosition(m_ParentPosition + m_LocalPosition);
	for (auto& child : m_Children)
	{
		child->setParentPosition(getPosition());
	}
}

void Transform::setRotation(float rot)
{
	m_LocalRotation = rot - m_ParentRotation;
	setRotation();
}

void Transform::setRotation(float parentrot, float localrot)
{
	m_ParentRotation = parentrot;
	m_LocalRotation = localrot;
	setRotation();
}

void Transform::setParentRotation(float parentrot)
{
	m_ParentRotation = parentrot;
	setRotation();
}

void Transform::setLocalRotation(float localrot)
{
	m_LocalRotation = localrot;
	setRotation();
}

void Transform::rotate(float rot)
{
	m_LocalRotation += rot;
	m_T->rotate(rot);
	for (auto& child : m_Children)
	{
		child->setParentRotation(getRotation());
	}
}

void Transform::setRotation()
{
	m_T->setRotation(m_ParentRotation + m_LocalRotation);
	for (auto& child : m_Children)
	{
		child->setParentRotation(getRotation());
	}
}

void Transform::setScale(const sf::Vector2f& scale)
{
	m_LocalScale = { scale.x / m_ParentScale.x, scale.y / m_ParentScale.y };
	setScale();
}

void Transform::setScale(float scalex, float scaley)
{
	setScale(sf::Vector2f(scalex, scaley));
}

void Transform::setScale(const sf::Vector2f& Parentscale, const sf::Vector2f& localscale)
{
	m_ParentScale = Parentscale;
	m_LocalScale = localscale;
	setScale();
}

void Transform::setParentScale(const sf::Vector2f& parentscale)
{
	m_ParentScale = parentscale;
	setScale();
}

void Transform::setLocalScale(const sf::Vector2f& localscale)
{
	m_LocalScale = localscale;
	setScale();
}

void Transform::setScale()
{
	m_T->setScale({ m_ParentScale.x * m_LocalScale.x, m_ParentScale.y * m_LocalScale.y });
	for (auto& child : m_Children)
	{
		child->setParentScale(getScale());
	}
}

void Transform::setOrigin(const sf::Vector2f& origin)
{
	m_T->setOrigin(origin);
}

void Transform::setOrigin(float originx, float originy)
{
	setOrigin(sf::Vector2f(originx, originy));
}

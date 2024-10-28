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
	m_ParentPosition = {0,0};
	m_LocalPosition = m_T->getPosition();
	m_ParentRotation = 0;
	m_LocalRotation = m_T->getRotation();
	m_ParentScale = { 1,1 };
	m_LocalScale = { 1,1 };
}

void Transform::Init(const Transform& other, sf::Transformable* transformable)
{
	m_T = transformable;
	m_ParentPosition = other.getParentPosition();
	m_LocalPosition = other.getLocalPosition();
	m_ParentRotation = other.getParentRotation();
	m_LocalRotation = other.getLocalRotation();
	m_ParentScale = other.getParentScale();
	m_LocalScale = other.getLocalScale();
}

void Transform::setPosition(const sf::Vector2f& pos)
{
	m_ParentPosition = pos - m_LocalPosition;
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
	m_ParentPosition += pos;
	m_T->move(pos);
}

void Transform::setPosition()
{
	m_T->setPosition(m_ParentPosition + m_LocalPosition);
}

void Transform::setRotation(float rot)
{
	m_ParentRotation = rot - m_LocalRotation;
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
	m_ParentRotation += rot;
	m_T->rotate(rot);
}

void Transform::setRotation()
{
	m_T->setRotation(m_ParentRotation + m_LocalRotation);
}

void Transform::setScale(const sf::Vector2f& scale)
{
	m_ParentScale = { scale.x / m_LocalScale.x, scale.y / m_LocalScale.y };
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
}

void Transform::setOrigin(const sf::Vector2f& origin)
{
	m_T->setOrigin(origin);
}

void Transform::setOrigin(float originx, float originy)
{
	setOrigin(sf::Vector2f(originx, originy));
}

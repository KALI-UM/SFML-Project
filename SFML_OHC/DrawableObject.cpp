#include "pch.h"
#include "DrawableObject.h"
#include "DebugInfo.h"

DrawableObject::DrawableObject(DataType datatype, DrawType drawtype, sf::Drawable* drawable, sf::Transformable* transform)
	:m_DataType(datatype), m_DrawType(drawtype), m_Drawable(drawable), m_Transform(transform), m_IsValid(false), m_DebugInfo(nullptr)
{
	Init(m_Transform);
#ifdef _DEBUG
	m_DebugInfo = new DebugInfo(sf::FloatRect(), const_cast<sf::Vector2f&>(m_Transform->getPosition()));
#endif // _DEBUG
}

DrawableObject::DrawableObject(const DrawableObject& other, sf::Drawable* drawable, sf::Transformable* transform)
	:m_DataType(other.m_DataType), m_DrawType(other.m_DrawType), m_Drawable(drawable), m_Transform(transform), m_IsValid(other.m_IsValid), m_DebugInfo(nullptr)
{
	Init(other, m_Transform);
#ifdef _DEBUG
	m_DebugInfo = new DebugInfo(sf::FloatRect(), const_cast<sf::Vector2f&>(m_Transform->getPosition()));
#endif // _DEBUG
}

DrawableObject::DrawableObject(DrawableObject&& other, sf::Drawable* drawable, sf::Transformable* transform)
	:m_DataType(other.m_DataType), m_DrawType(other.m_DrawType), m_Drawable(drawable), m_Transform(transform), m_IsValid(other.m_IsValid), m_DebugInfo(nullptr)
{
	Init(other, m_Transform);
#ifdef _DEBUG
	m_DebugInfo = new DebugInfo(sf::FloatRect(), const_cast<sf::Vector2f&>(m_Transform->getPosition()));
#endif // _DEBUG
	other.m_IsValid = false;
}

DrawableObject::~DrawableObject()
{
	delete m_DebugInfo;
}

DebugInfo* DrawableObject::GetDebugDraw()
{
	if(m_DebugInfo)
	m_DebugInfo->Update(GetFloatRect());
	return m_DebugInfo;
}

void DrawableObject::SetDebugDraw(bool debug)
{
	if (!m_DebugInfo && debug)
	{
		m_DebugInfo = new DebugInfo(GetFloatRect(), const_cast<sf::Vector2f&>(m_Transform->getPosition()));
	}
	else if (m_DebugInfo && !debug)
	{
		delete m_DebugInfo;
		m_DebugInfo = nullptr;
	}
}

void DrawableObject::SetOriginCenter()
{
	SetOrigin(OriginType::MC);
}

void DrawableObject::SetOrigin(OriginType type, const sf::Vector2f& detail)
{
	setOrigin(((GetFloatRect().width / 2) * ((int)type % 3)) + detail.x,
		((GetFloatRect().height / 2) * ((int)type / 3)) + detail.y);
}

sf::Vector2f DrawableObject::GetPoint(int index) const
{
	//0 , 1
	//2 , 3 ¿Œµ¶Ω∫
	return sf::Vector2f(GetFloatRect().getPosition().x + (index % 2) * GetFloatRect().width,
		GetFloatRect().getPosition().y + (index / 2) * GetFloatRect().height);
}

sf::Vector2u DrawableObject::GetTextureSize() const
{
	return sf::Vector2u(0, 0);
}

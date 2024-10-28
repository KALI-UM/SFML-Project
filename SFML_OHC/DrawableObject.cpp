#include "pch.h"
#include "DrawableObject.h"

DrawableObject::DrawableObject(DataType datatype, DrawType drawtype, sf::Drawable* drawable, sf::Transformable* transform)
	:m_DataType(datatype), m_DrawType(drawtype), m_Drawable(drawable), m_Transform(transform), m_IsValid(false)
{
	Init(m_Transform);
}

DrawableObject::DrawableObject(const DrawableObject& other, sf::Drawable* drawable, sf::Transformable* transform)
	:m_DataType(other.m_DataType), m_DrawType(other.m_DrawType), m_Drawable(drawable), m_Transform(transform), m_IsValid(other.m_IsValid)
{
	Init(other, m_Transform);
}

DrawableObject::DrawableObject(DrawableObject&& other, sf::Drawable* drawable, sf::Transformable* transform)
	:m_DataType(other.m_DataType), m_DrawType(other.m_DrawType), m_Drawable(drawable), m_Transform(transform), m_IsValid(other.m_IsValid)
{
	Init(other, m_Transform);
	other.m_IsValid = false;
}

void DrawableObject::SetOriginCenter()
{
	SetOrigin(OriginType::MC);
}

void DrawableObject::SetOrigin(OriginType type, const sf::Vector2f& detail)
{
	setOrigin(((GetFloatRect().width / 2 )* ((int)type % 3)) + detail.x,
						   ((GetFloatRect().height / 2 )* ((int)type / 3)) + detail.y);
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
	return sf::Vector2u(0,0);
}

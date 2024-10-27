#include "pch.h"
#include "DrawableObject.h"

void DrawableObject::SetOriginCenter()
{
	SetOrigin(OriginType::MC);
}

void DrawableObject::SetOrigin(OriginType type, const sf::Vector2f& detail)
{
	Transform()->setOrigin(((GetFloatRect().width / 2 )* ((int)type % 3)) + detail.x,
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

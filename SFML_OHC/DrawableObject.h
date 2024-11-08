#pragma once
#include "Transform.h"
enum class DataType
{
	Sprite,
	Animation,
	Text,
	Shape,
	None
};

enum class DrawType
{
	Background,
	Normal,
	Effect,
	Debug,
	UI,
};

enum class OriginType
{
	TL = 0, TC = 1, TR = 2,
	ML = 3, MC = 4, MR = 5,
	BL = 6, BC = 7, BR = 8,
	Custom
};

class DebugInfo;
class DrawableObject : public Transform
{
protected:
	DrawableObject(DataType datatype, DrawType drawtype, sf::Drawable* drawable, sf::Transformable* transform);
	DrawableObject(const DrawableObject& other, sf::Drawable* drawable, sf::Transformable* transform);
	DrawableObject(DrawableObject&& other, sf::Drawable* drawable, sf::Transformable* transform);
	
public:
	virtual ~DrawableObject();

	static bool TypeCompare(DrawableObject*& lhs, DrawableObject*& rhs)
	{
		return lhs->m_DrawType > rhs->m_DrawType;
	}

	static bool YCompare(DrawableObject*& lhs, DrawableObject*& rhs)
	{
		return lhs->m_DrawType > rhs->m_DrawType ? true : lhs->m_DrawType == rhs->m_DrawType ? lhs->GetPriority(false) > rhs->GetPriority(false) : false;
	}

	static bool XCompare(DrawableObject*& lhs, DrawableObject*& rhs)
	{
		return lhs->m_DrawType > rhs->m_DrawType ? true : lhs->m_DrawType == rhs->m_DrawType ? lhs->GetPriority(true) > rhs->GetPriority(true) : false;
	}

	
	bool GetIsValid()const {
#ifdef NDEBUG
		if (m_DrawType == DrawType::Debug) //디버그 상황이 아닐때 그려지지 않게 하기 위함
			return false;
		return m_IsValid;
#endif
		if (GM->GetGameMode() != GameMode::Debug && m_DrawType == DrawType::Debug)
		{
			return false;
		}
		return m_IsValid;
	}

	virtual void Update(float dt) {};

	sf::Drawable* GetDrawable()const { return m_Drawable; }
	DebugInfo* GetDebugDraw();

	void SetDebugDraw(bool debug);

	float GetPriority(bool x) { return m_DrawType == DrawType::UI ? m_Priority : x ? getPosition().x : getPosition().y; };
	void SetPriority(float p) { m_Priority = p; };

	std::string GetName()const { return m_Name; }
	void SetName(const std::string& name) { m_Name = name; }

	void SetOriginCenter();
	virtual void SetOrigin(OriginType type, const sf::Vector2f& detail = sf::Vector2f(0, 0));
	sf::Vector2f GetPoint(int index) const; 

	virtual sf::Vector2u GetTextureSize()const;
	virtual sf::FloatRect GetGlobalBounds()const = 0;
	virtual sf::FloatRect GetLocalBounds()const = 0;

	virtual sf::Color GetColor() const = 0;
	virtual void SetColor(const sf::Color& color) = 0;
	virtual void SetColor(int r, int g, int b, int a = 255) = 0;
	virtual sf::Color GetFillColor() const = 0;
	virtual sf::Color GetOutlineColor() const = 0;
	virtual void SetFillColor(const sf::Color& color) = 0;
	virtual void SetFillColor(int r, int g, int b, int a = 255) = 0;
	virtual void SetOutlineColor(const sf::Color& color) = 0;
	virtual void SetOutlineColor(int r, int g, int b, int a = 255) = 0;

	const DataType m_DataType;
	const DrawType m_DrawType;
protected:
	sf::Drawable*			m_Drawable;
	sf::Transformable*		m_Transform;
	bool					m_IsValid;
	std::string				m_Name;
	float					m_Priority = 0;			//m_Priority가 클수록 나중에 그려진다.
	DebugInfo*				m_DebugInfo;

};

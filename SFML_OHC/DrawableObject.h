#pragma once

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

class DrawableObject
{
protected:
	DrawableObject(DataType datatype, DrawType drawtype, sf::Drawable* drawable, sf::Transformable* transform)
		:m_DataType(datatype), m_DrawType(drawtype), m_Drawable(drawable), m_Transform(transform), m_IsValid(false) {}
	DrawableObject(const DrawableObject& other, sf::Drawable* drawable, sf::Transformable* transform)
		:m_DataType(other.m_DataType), m_DrawType(other.m_DrawType), m_Drawable(drawable), m_Transform(transform), m_IsValid(other.m_IsValid) {}
	DrawableObject(DrawableObject&& other, sf::Drawable* drawable, sf::Transformable* transform)
		:m_DataType(other.m_DataType), m_DrawType(other.m_DrawType), m_Drawable(drawable), m_Transform(transform), m_IsValid(other.m_IsValid) {
		other.m_IsValid = false;
	}

public:
	virtual ~DrawableObject() {};

	virtual void Update(float dt) {};
	bool GetIsValid()const {
#ifdef NDEBUG
		if (m_DrawType == DrawType::Debug) //디버그 상황이 아닐때 그려지지 않게 하기 위함
			return false;
#endif
		return m_IsValid;
	}
	virtual bool GetIsVisible()const = 0;
	virtual void SetOriginCenter() = 0;

	sf::Drawable* GetDrawable()const { return m_Drawable; }
	sf::Transformable* Transform() { return m_Transform; }

	virtual sf::Color GetColor() const = 0;
	virtual void SetColor(const sf::Color& color) = 0;
	virtual void SetColor(int r, int g, int b, int a = 255) = 0;
	virtual sf::Color GetFillColor() const = 0;
	virtual sf::Color GetOutlineColor() const = 0;
	virtual void SetFillColor(const sf::Color& color) = 0;
	virtual void SetFillColor(int r, int g, int b, int a = 255) = 0;
	virtual void SetOutlineColor(const sf::Color& color) = 0;
	virtual void SetOutlineColor(int r, int g, int b, int a = 255) = 0;

	static bool TypeCompare(DrawableObject*& lhs, DrawableObject*& rhs)
	{
		return lhs->m_DrawType > rhs->m_DrawType;
	}

	static bool YCompare(DrawableObject*& lhs, DrawableObject*& rhs)
	{
		return lhs->m_DrawType > rhs->m_DrawType ? true : lhs->m_DrawType == rhs->m_DrawType ? lhs->Transform()->getPosition().y > rhs->Transform()->getPosition().y : false;
	}

	static bool XCompare(DrawableObject*& lhs, DrawableObject*& rhs)
	{
		return lhs->m_DrawType > rhs->m_DrawType ? true : lhs->m_DrawType == rhs->m_DrawType ? lhs->Transform()->getPosition().x > rhs->Transform()->getPosition().x : false;
	}

	const DataType m_DataType;
	const DrawType m_DrawType;
protected:
	sf::Drawable* m_Drawable;
	sf::Transformable* m_Transform;
	bool m_IsValid;
};

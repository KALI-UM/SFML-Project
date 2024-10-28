#pragma once

//sf::Transformable을 계층용으로 사용하기 위해 제작

namespace sf
{
	class Transformable;
}

class Transform
{
protected:
	void Init(sf::Transformable* transformable);
	void Init(const Transform& other, sf::Transformable* transformable);
public:
	void setPosition(const sf::Vector2f& pos);					//global
	void setPosition(float posx, float posy);					//global
	void setPosition(const sf::Vector2f& Parentpos, const sf::Vector2f& localpos);
	void setParentPosition(const sf::Vector2f& Parentpos);
	void setLocalPosition(const sf::Vector2f& localpos);
	void move(const sf::Vector2f& pos);
private:
	void setPosition();

public:
	void setRotation(float rot);								//global
	void setRotation(float Parentrot, float localrot);
	void setParentRotation(float Parentrot);
	void setLocalRotation(float localrot);
	void rotate(float rot);
private:
	void setRotation();

public:
	void setScale(const sf::Vector2f& scale);					//global
	void setScale(float scalex, float scaley);					//global
	void setScale(const sf::Vector2f& Parentscale, const sf::Vector2f& localscale);
	void setParentScale(const sf::Vector2f& Parentscale);
	void setLocalScale(const sf::Vector2f& localscale);
private:
	void setScale();

public:
	void setOrigin(const sf::Vector2f& origin);
	void setOrigin(float originx, float originy);

	sf::Vector2f getPosition()const { return m_T->getPosition(); }
	sf::Vector2f getParentPosition()const { return m_ParentPosition; }
	sf::Vector2f getLocalPosition()const { return m_LocalPosition; }

	float getRotation()const { return m_T->getRotation(); }
	float getParentRotation()const { return m_ParentRotation; }
	float getLocalRotation()const { return m_LocalRotation; }

	sf::Vector2f getScale()const { return m_T->getScale(); }
	sf::Vector2f getParentScale()const { return m_ParentScale; }
	sf::Vector2f getLocalScale()const { return m_LocalScale; }

	sf::Vector2f getOrigin()const { return m_T->getOrigin(); }

private:
	sf::Vector3f	m_GlobalPosition;	//x, y, z = 그리기 우선순위 z값이 클수록 위에 그려진다.
	sf::Vector2f	m_ParentPosition;
	sf::Vector2f	m_LocalPosition;
	float			m_ParentRotation;
	float			m_LocalRotation;
	sf::Vector2f	m_ParentScale;
	sf::Vector2f	m_LocalScale;

	sf::Transformable* m_T;
};


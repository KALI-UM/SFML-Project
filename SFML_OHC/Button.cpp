#include "pch.h"
#include "Button.h"
#include "DRectangle.h"
#include "DSprite.h"
#include "DText.h"

Button::Button()
{
}

Button::~Button()
{
}

bool Button::Initialize()
{
	m_ButtonSprite = new DSprite("ui/button.png", DrawType::UI);
	m_ButtonSprite->Transform()->setScale(0.4f, 0.4f);
	m_ButtonSprite->SetOriginCenter();
	m_ButtonSprite->SetPriority(10);
	SetDrawable(m_ButtonSprite);
	m_ButtonArea = new DRectangle(m_ButtonSprite->GetFloatRect(), sf::Color::Blue, 1, sf::Color::Transparent, DrawType::Debug);
	m_ButtonArea->SetOriginCenter();
	SetDrawable(m_ButtonArea);
	m_ButtonText = new DText("resource/CookieRun Black.ttf", "", 30, DrawType::UI);
	m_ButtonText->SetOutlineColor(sf::Color::Black);
	m_ButtonText->SetOutlineThickness(1);
	m_ButtonText->SetOriginCenter();
	m_ButtonText->SetPriority(100);
	SetDrawable(m_ButtonText);

	return true;
}

void Button::Reset()
{
	m_ButtonSprite->SetColor(m_DefaultColor);
	m_IsOverlaying = false;
	m_IsClicked = false;
}

void Button::Update(float dt)
{
	m_IsOverlaying = m_ButtonArea->GetFloatRect().contains({ (float)MOUSEPOS.x,(float)MOUSEPOS.y });
	m_IsClicked = m_IsOverlaying && IM->GetMouseDown(sf::Mouse::Left);

	if (m_IsOverlaying)
	{
		m_ButtonSprite->SetColor(m_OverayColor);
		m_ButtonArea->SetOutlineColor(sf::Color::Red);
	}
	else
	{
		m_ButtonSprite->SetColor(m_DefaultColor);
		m_ButtonArea->SetOutlineColor(sf::Color::Blue);
	}
}

void Button::SetButtonPosition(const sf::Vector2f& pos)
{
	m_ButtonSprite->Transform()->setPosition(pos);
	m_ButtonText->Transform()->setPosition(pos);
	m_ButtonArea->SetFloatRect(m_ButtonSprite->GetFloatRect());
}

void Button::SetButtonText(const std::string& text)
{
	m_ButtonText->SetString(text);
	m_ButtonText->SetOriginCenter();
}

void Button::SetButtonColor(const sf::Color& on, const sf::Color& off)
{
	m_DefaultColor = off;
	m_OverayColor = on;
}

bool Button::GetIsOveraying() const
{
	return m_IsOverlaying;
}

bool Button::GetIsClicked() const
{
	return m_IsClicked;
}

#include "pch.h"
#include "InputManager.h"

bool InputManager::Initialize()
{
	Clear();
	m_HeldKey.reset();
	//m_HeldMouse.reset();

	m_Axis.resize(2);
	m_Axis[(int)Axis::Horizontal].AddKey(false, sf::Keyboard::A);
	m_Axis[(int)Axis::Horizontal].AddKey(true, sf::Keyboard::D);
	m_Axis[(int)Axis::Horizontal].AddKey(false, sf::Keyboard::Left);
	m_Axis[(int)Axis::Horizontal].AddKey(true, sf::Keyboard::Right);

	m_Axis[(int)Axis::Vertical].AddKey(false, sf::Keyboard::S);
	m_Axis[(int)Axis::Vertical].AddKey(true, sf::Keyboard::W);
	m_Axis[(int)Axis::Vertical].AddKey(false, sf::Keyboard::Down);
	m_Axis[(int)Axis::Vertical].AddKey(true, sf::Keyboard::Up);

	return true;
}

void InputManager::Update(const sf::Event& ev)
{
	switch (ev.type)
	{
	case sf::Event::KeyPressed:
	{
		if (!GetKey(ev.key.code))
		{
			m_DownKey.set(ev.key.code, 1);
			m_HeldKey.set(ev.key.code, 1);
		}
		break;
	}
	case sf::Event::KeyReleased:
	{
		m_UpKey.set(ev.key.code, 1);
		m_HeldKey.set(ev.key.code, 0);
		break;
	}
	case sf::Event::MouseButtonPressed:
	{
		if (!GetMouse(ev.mouseButton.button))
		{
			m_DownKey.set(sf::Keyboard::KeyCount+ev.mouseButton.button, 1);
			m_HeldKey.set(sf::Keyboard::KeyCount+ev.mouseButton.button, 1);
		}
		break;
	}
	case sf::Event::MouseButtonReleased:
	{
		m_UpKey.set(sf::Keyboard::KeyCount+ev.mouseButton.button, 1);
		m_HeldKey.set(sf::Keyboard::KeyCount+ev.mouseButton.button, 0);
		break;
	}
	break;
	}
}

void InputManager::Clear()
{
	m_DownKey.reset();
	m_UpKey.reset();

	//m_DownMouse.reset();
	//m_UpMouse.reset();
}

bool InputManager::GetKeyDown(sf::Keyboard::Key key)
{
	return m_DownKey.test(key);
}

bool InputManager::GetKeyUp(sf::Keyboard::Key key)
{
	return m_UpKey.test(key);
}

bool InputManager::GetKey(sf::Keyboard::Key key)
{
	return m_HeldKey.test(key);
}

sf::Vector2i InputManager::GetMousePos() const
{
	return sf::Mouse::getPosition(*GameManager::GetInstance()->GetWindow());
}

sf::Vector2f InputManager::GetMouseViewPos() const
{
	return GameManager::GetInstance()->GetWindow()->mapPixelToCoords(GetMousePos());
}

bool InputManager::GetMouseDown(sf::Mouse::Button btt)
{
	return m_DownKey.test(sf::Keyboard::KeyCount + btt);
}

bool InputManager::GetMouseUp(sf::Mouse::Button btt)
{
	return m_UpKey.test(sf::Keyboard::KeyCount + btt);
}

bool InputManager::GetMouse(sf::Mouse::Button btt)
{
	return m_HeldKey.test(sf::Keyboard::KeyCount+btt);
}

float InputManager::GetAxis(Axis axis) const
{
	return m_Axis[(int)axis].m_Value;
}

float InputManager::GetAxisRaw(Axis axis) const
{


	return 0.0f;
}

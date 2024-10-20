#include "pch.h"
#include "InputManager.h"


bool InputManager::Initialize()
{
	Clear();
	m_HeldKey.reset();
	m_HeldMouse.reset();
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
			m_DownMouse.set(ev.mouseButton.button, 1);
			m_HeldMouse.set(ev.mouseButton.button, 1);
		}
		break;
	}
	case sf::Event::MouseButtonReleased:
	{
		m_UpMouse.set(ev.mouseButton.button, 1);
		m_HeldMouse.set(ev.mouseButton.button, 0);
		break;
	}
	break;
	}
}

void InputManager::Clear()
{
	m_DownKey.reset();
	m_UpKey.reset();

	m_DownMouse.reset();
	m_UpMouse.reset();
}

bool InputManager::GetKeyDown(sf::Keyboard::Key key)
{
	return m_DownKey.test(key);
}

bool InputManager::GetKeyUp(sf::Keyboard::Key key)
{
	return m_UpKey.test(key);;
}

bool InputManager::GetKey(sf::Keyboard::Key key)
{
	return m_HeldKey.test(key);;
}

sf::Vector2i InputManager::GetMousePos() const
{
	return sf::Mouse::getPosition(*GameManager::GetInstance()->GetWindow());
}

bool InputManager::GetMouseDown(sf::Mouse::Button btt)
{
	return m_DownMouse.test(btt);
}

bool InputManager::GetMouseUp(sf::Mouse::Button btt)
{
	return m_UpMouse.test(btt);;
}

bool InputManager::GetMouse(sf::Mouse::Button btt)
{
	return m_HeldMouse.test(btt);;
}

#pragma once
#include "Singleton.h"
#include <bitset>

class InputManager :
	public Singleton<InputManager>
{
public:
	bool Initialize();
	void Update(const sf::Event& ev);
	void Clear();
	
	bool GetKeyDown(sf::Keyboard::Key key);
	bool GetKeyUp(sf::Keyboard::Key key);
	bool GetKey(sf::Keyboard::Key key);

	sf::Vector2i GetMousePos()const;			//��ũ�� ��ǥ�� ����
	sf::Vector2f GetMouseViewPos()const;		//�� ��ǥ�� ����
	bool GetMouseDown(sf::Mouse::Button btt);
	bool GetMouseUp(sf::Mouse::Button btt);
	bool GetMouse(sf::Mouse::Button btt);

private:
	std::bitset<sf::Keyboard::KeyCount>		m_HeldKey;
	std::bitset<sf::Keyboard::KeyCount>		m_DownKey;
	std::bitset<sf::Keyboard::KeyCount>		m_UpKey;

	std::bitset<sf::Mouse::ButtonCount>		m_HeldMouse;
	std::bitset<sf::Mouse::ButtonCount>		m_DownMouse;
	std::bitset<sf::Mouse::ButtonCount>		m_UpMouse;
};

#define MOUSEPOS (IM->GetMousePos())
#define MOUSEVIEWPOS (IM->GetMouseViewPos())
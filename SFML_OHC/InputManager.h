#pragma once
#include "Singleton.h"
#include <bitset>

enum class Axis
{
	Horizontal = 0,
	Vertical = 1,
};

struct AxisInfo
{
	Axis m_Axis;

	std::vector<int> m_PositiveKeys;
	std::vector<int> m_NegativeKeys;

	float m_Sensitivity = 10;
	float m_Value = 0;

	void AddKey(bool positive, int code)
	{
		if (positive)
		{
			m_PositiveKeys.push_back(code);
		}
		else
		{
			m_NegativeKeys.push_back(code);
		}
	}
};


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

	sf::Vector2i GetMousePos()const;			//Ω∫≈©∏∞ ¡¬«•∞Ë ±‚¡ÿ
	sf::Vector2f GetMouseViewPos()const;		//∫‰ ¡¬«•∞Ë ±‚¡ÿ
	bool GetMouseDown(sf::Mouse::Button btt);
	bool GetMouseUp(sf::Mouse::Button btt);
	bool GetMouse(sf::Mouse::Button btt);

	float GetAxis(Axis axis) const;
	float GetAxisRaw(Axis axis) const;
private:
	std::bitset<sf::Keyboard::KeyCount + sf::Mouse::ButtonCount>		m_HeldKey;
	std::bitset<sf::Keyboard::KeyCount + sf::Mouse::ButtonCount>		m_DownKey;
	std::bitset<sf::Keyboard::KeyCount + sf::Mouse::ButtonCount>		m_UpKey;

	//std::bitset<sf::Mouse::ButtonCount>		m_HeldMouse;
	//std::bitset<sf::Mouse::ButtonCount>		m_DownMouse;
	//std::bitset<sf::Mouse::ButtonCount>		m_UpMouse;

	std::vector<AxisInfo>							m_Axis;
};

#define MOUSEPOS (IM->GetMousePos())
#define MOUSEVIEWPOS (IM->GetMouseViewPos())
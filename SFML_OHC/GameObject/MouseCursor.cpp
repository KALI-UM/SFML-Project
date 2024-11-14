#include "pch.h"
#include "MouseCursor.h"

MouseCursor::MouseCursor(const std::string& texId, int viewIndex)
	:m_TextureId(texId), m_ViewIndex(viewIndex)
{
}

MouseCursor::~MouseCursor()
{
}

bool MouseCursor::Initialize()
{
	m_WhenDownFunc.resize(sf::Mouse::ButtonCount);
	m_WhenUpFunc.resize(sf::Mouse::ButtonCount);
	m_WhenFunc.resize(sf::Mouse::ButtonCount);

	m_CursorSprite = new DSprite(m_TextureId);
	SetDrawable(m_CursorSprite);
	return true;
}

void MouseCursor::Reset()
{
	m_CursorSprite->SetTexture(m_TextureId);
}

void MouseCursor::Update(float dt)
{
	setPosition(INPUT_MGR->GetMouseViewPos(m_ViewIndex));

	for (int mbtt = 0; mbtt < (int)sf::Mouse::ButtonCount; mbtt++)
	{
		if (INPUT_MGR->GetMouseDown((sf::Mouse::Button)mbtt) && m_WhenDownFunc[mbtt])
		{
			m_WhenDownFunc[mbtt]();
		}

		if (INPUT_MGR->GetMouseUp((sf::Mouse::Button)mbtt) && m_WhenUpFunc[mbtt])
		{
			m_WhenUpFunc[mbtt]();
		}

		if (INPUT_MGR->GetMouse((sf::Mouse::Button)mbtt) && m_WhenFunc[mbtt])
		{
			m_WhenFunc[mbtt]();
		}
	}
}

void MouseCursor::SetMouseDownFunc(sf::Mouse::Button btt, const std::function<void()>& func)
{
	m_WhenDownFunc[btt] = func;
}

void MouseCursor::SetMouseUpFunc(sf::Mouse::Button btt, const std::function<void()>& func)
{
	m_WhenUpFunc[btt] = func;
}

void MouseCursor::SetMouseFunc(sf::Mouse::Button btt, const std::function<void()>& func)
{
	m_WhenFunc[btt] = func;
}

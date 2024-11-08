#include "pch.h"
#include "MouseCursor.h"
#include "DSprite.h"
#include "SoundPlayer.h"

MouseCursor::MouseCursor(const std::string& texId)
	:m_TextureId(texId)
{

}

MouseCursor::~MouseCursor()
{
}

bool MouseCursor::Initialize()
{
	m_Cursor = new DSprite(m_TextureId, DrawType::UI);
	SetDrawable(m_Cursor);
	m_Cursor->SetPriority(1000);
	return true;
}

void MouseCursor::Reset()
{
}

void MouseCursor::Update(float dt)
{
	setPosition({ MOUSEPOS });
	if (IM->GetMouseDown(sf::Mouse::Left))
	{
		SM->GetSoundPlayer()->PlayEffect("sound/ButtonClick.wav");
	}
}

#pragma once
#include "GameObject.h"
class DSprite;
class MouseCursor :
    public GameObject
{
public:
	MouseCursor(const std::string& texId= "ui/push.png");
	~MouseCursor();

	bool Initialize() override;
	void Reset()override;
	void Update(float dt)override;

private:
	std::string m_TextureId;
	DSprite* m_Cursor;
	std::function<void()> m_WhenClickedFunc;
};


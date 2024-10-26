#pragma once
#include "GameObject.h"
class DSprite;
class MouseCursor :
    public GameObject
{
public:
	MouseCursor();
	~MouseCursor();

	bool Initialize() override;
	void Reset()override;
	void Update(float dt)override;

private:
	DSprite* m_Cursor;
};


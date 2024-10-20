#include "pch.h"
#include "SceneBase.h"
#include "GameObject.h"

SceneBase::SceneBase()
{
}

SceneBase::~SceneBase()
{
	for (GameObject*& gobj : m_GameObjects)
	{
		delete gobj;
	}
}

bool SceneBase::Initialize()
{
	return false;
}

void SceneBase::Update(float dt)
{
}

void SceneBase::SetInitialState()
{
}

void SceneBase::PushToDrawQue()
{
	for (GameObject*& gobj : m_GameObjects)
	{
		if (gobj->GetIsVisible())
		{
			GameManager::GetInstance()->PushDrawableObject(gobj->GetDrawable());
		}
	}
}

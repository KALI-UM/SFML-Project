#include "pch.h"
#include "SceneBase.h"
#include "DrawableObject.h"
#include "SoundPlayer.h"

SceneBase::SceneBase(const std::string& name, unsigned int layercnt, unsigned int viewIndex)
	:m_TargetViewIndex(viewIndex), m_Name(name), m_SoundPlayer(nullptr)
{
}

SceneBase::~SceneBase()
{
}

bool SceneBase::INITIALIZE()
{
	m_SoundPlayer = new SoundPlayer();
	m_GameObjects.push_back(m_SoundPlayer);
	bool result = Initialize();
	for (auto& gobj : m_GameObjects)
	{
		result &= gobj->INITIALIZE();
	}
	RESET();
	return result;
}

void SceneBase::RESET()
{
	for (auto& gobj : m_GameObjects)
	{
		gobj->RESET();
	}
	Reset();
}

void SceneBase::LATEUPDATE()
{
}

void SceneBase::UPDATE(float dt)
{
	for (auto& gobj : m_GameObjects)
	{
		if (gobj->GetIsValid())
			gobj->UPDATE(dt);
	}
	Update(dt);
}

void SceneBase::PRERENDER()
{
	PreRender();
	PushToDrawQue();
}

void SceneBase::POSTRENDER()
{
	PostRender();
}

void SceneBase::EXIT()
{
	FM->SetTimeScale(1);
	m_SoundPlayer->StopAllSound();
	Exit();
}

void SceneBase::RELEASE()
{
	Release();
	for (GameObject*& gobj : m_GameObjects)
	{
		delete gobj;
	}
}

bool SceneBase::Initialize()
{
	return true;
}

void SceneBase::Reset()
{
}

void SceneBase::Update(float dt)
{
}

void SceneBase::LateUpdate()
{
}

void SceneBase::PreRender()
{
}

void SceneBase::PostRender()
{
}

void SceneBase::Exit()
{
}

void SceneBase::Release()
{
}

std::string SceneBase::GetName() const
{
	return m_Name;
}

SoundPlayer* SceneBase::GetSoundPlayer()
{
	return m_SoundPlayer;
}

void SceneBase::PushToDrawQue()
{
	for (GameObject*& gobj : m_GameObjects)
	{
		if (gobj->GetIsValid())
		{
			for (int i = 0; i < gobj->GetDrawbleCount(); i++)
			{
				if (gobj->GetIsVisible(i))
				{
					GM->PushDrawableObject(m_TargetViewIndex, gobj->GetDrawable(i));
					GM->PushDebugDrawObject(gobj->GetDrawable(i)->GetDebugDraw());
				}
			}
		}
	}
}
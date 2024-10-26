#include "pch.h"
#include "SceneBase.h"
#include "SoundPlayer.h"

SceneBase::SceneBase(const std::string& name)
	:m_Name(name)
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
	Reset();
	for (auto& gobj : m_GameObjects)
	{
		gobj->RESET();
	}
}

void SceneBase::UPDATE(float dt)
{
	Update(dt);
	for (auto& gobj : m_GameObjects)
	{
		if (gobj->GetIsValid())
			gobj->UPDATE(dt);
	}
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

void SceneBase::Exit()
{
}

void SceneBase::Release()
{
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
					GameManager::GetInstance()->PushDrawableObject(gobj->GetDrawable(i));
			}
		}
	}
}

std::string SceneBase::GetName() const
{
	return m_Name;
}

SoundPlayer* SceneBase::GetSoundPlayer()
{
	return m_SoundPlayer;
}

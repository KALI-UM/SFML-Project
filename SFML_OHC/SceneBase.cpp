#include "pch.h"
#include "SceneBase.h"
#include "DrawableObject.h"
#include "SoundPlayer.h"

SceneBase::SceneBase(const std::string& name, unsigned int layercnt, int viewcnt)
	:m_ViewCnt(viewcnt), m_Name(name), m_SoundPlayer(nullptr)
{
	m_GameObjects.resize(layercnt);
	m_LayerIndex.resize(layercnt);
	int viewIndex = 0;
	for (auto it = m_GameObjects.begin(); it != m_GameObjects.end(); it++)
	{
		m_LayerIndex[viewIndex] = it;
		viewIndex++;
	}
}

SceneBase::~SceneBase()
{
}

bool SceneBase::INITIALIZE()
{
	m_SoundPlayer = AddGameObject(0, new SoundPlayer());
	bool result = Initialize();
	for (auto& layer : m_GameObjects)
		for (auto& gobj : layer.gameObjects)
		{
			result &= gobj->INITIALIZE();
		}
	RESET();
	return result;
}

void SceneBase::RESET()
{
	for (auto& layer : m_GameObjects)
		for (auto& gobj : layer.gameObjects)
		{
			gobj->RESET();
		}
	Reset();
}

void SceneBase::ENTER()
{
	ImGuiManager::SetShowDemo(false);
	GM->ResizeViews(m_ViewCnt);
	Enter();
}

void SceneBase::UPDATE(float dt)
{
	for (auto& layer : m_GameObjects)
		for (auto& gobj : layer.gameObjects)
		{
			if (gobj->GetIsValid())
				gobj->UPDATE(dt);
		}
	Update(dt);
}

void SceneBase::LATEUPDATE(float dt)
{
	LateUpdate(dt);
	RemoveGameObject();
}

void SceneBase::FIXEDUPDATE(float dt)
{
	FixedUpdate(dt);
}

void SceneBase::IMGUIUPDATE()
{
	for (auto& layer : m_GameObjects)
		for (auto& gobj : layer.gameObjects)
		{
			if (gobj->GetIsValid())
				gobj->IMGUIUPDATE();
		}
	ImGuiUpdate();
}

void SceneBase::PRERENDER()
{
	PreRender();
	GM->UpdateViewRect();
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
	for (auto& layer : m_GameObjects)
		for (auto& gobj : layer.gameObjects)
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

void SceneBase::Enter()
{
}

void SceneBase::Update(float dt)
{
}

void SceneBase::LateUpdate(float dt)
{
}

void SceneBase::FixedUpdate(float dt)
{
}

void SceneBase::ImGuiUpdate()
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

void SceneBase::SetLayerViewIndex(int layerIndex, int viewIndex)
{
	m_LayerIndex[layerIndex]->viewIndex = viewIndex;
}

void SceneBase::RemoveGameObject(GameObjectInfo gobj)
{
	m_WantsToRemove.push(gobj);
}

void SceneBase::RemoveGameObject(int layerIndex, GameObject* gobj)
{
	RemoveGameObject({ layerIndex, gobj });
}

std::vector<GameObject*>& SceneBase::GetGameObjectsLayerIter(int index)
{
	return m_LayerIndex[index]->gameObjects;
}

void SceneBase::PushToDrawQue()
{
	for (int layerIndex = 0; layerIndex < m_GameObjects.size(); layerIndex++)
	{
		for (auto& gobj : GetGameObjectsLayerIter(layerIndex))
		{
			if (gobj->GetIsValid())
			{
				for (int i = 0; i < gobj->GetDrawbleCount(); i++)
				{
					if (gobj->GetIsVisible(i))
					{
						DrawableObject* dobj = gobj->GetDrawable(i);
						int viewIndex = m_LayerIndex[layerIndex]->viewIndex;
						
						if (GM->GetViewRect(viewIndex).intersects(dobj->GetGlobalBounds()))
						{
							GM->PushDrawableObject(viewIndex, dobj);
#ifdef _DEBUG
							if (dobj->GetDebugDraw())
								GM->PushDebugDrawObject(viewIndex, dobj->GetDebugDraw());
#endif // _DEBUG
						}
					}
				}
			}
		}
	}
}

void SceneBase::RemoveGameObject()
{
	while (!m_WantsToRemove.empty())
	{
		int layerIndex = m_WantsToRemove.front().first;
		GameObject* target = m_WantsToRemove.front().second;

		std::remove(GetGameObjectsLayerIter(layerIndex).begin(), GetGameObjectsLayerIter(layerIndex).end(), target);

		m_WantsToRemove.pop();
	}
}

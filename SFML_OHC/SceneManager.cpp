#include "pch.h"
#include "SceneManager.h"
#include "SceneBase.h"

bool SceneManager::Initialize()
{
	m_EmptyScene = new SceneBase("");
	m_CurrSceneName = "";
	m_WantsTo = nullptr;
	return false;
}

void SceneManager::Reset()
{
	m_CurrScene->RESET();
}

void SceneManager::Update(float dt)
{
	if (m_WantsTo != nullptr)
	{
		m_CurrScene->EXIT();
		SetCurrentScene(m_WantsTo);
		m_CurrSoundPlayer = m_CurrScene->GetSoundPlayer();
		m_WantsTo = nullptr;
		m_CurrScene->RESET();
	}
	else
	{
		m_CurrScene->UPDATE(dt);
	}
}

void SceneManager::PushToDrawQue()
{
	m_CurrScene->PushToDrawQue();
}

void SceneManager::Release()
{
	for (auto& scene : m_Scenes)
	{
		scene.second->RELEASE();
	}
}

std::string SceneManager::GetCurrentSceneName() const
{
	return m_CurrSceneName;
}

void SceneManager::SetCurrentScene(const std::string& name)
{
	m_CurrSceneName = name;
	m_CurrScene = m_Scenes[m_CurrSceneName];
	m_CurrSoundPlayer = m_CurrScene->GetSoundPlayer();
}

bool SceneManager::ChangeScene(const std::string& name)
{
	std::unordered_map<std::string, SceneBase*>::iterator it = m_Scenes.find(name);
	if (it == m_Scenes.end())return false;
	m_WantsTo = it->second;
	return true;
}


void SceneManager::PushScene(SceneBase* scene)
{
	scene->INITIALIZE();
	m_Scenes.insert({ scene->GetName(), scene });
}

SoundPlayer* SceneManager::GetSoundPlayer()
{
	return m_CurrSoundPlayer;
}

void SceneManager::SetCurrentScene(SceneBase* scene)
{
	m_CurrSceneName = scene->GetName();
	m_CurrScene = scene;
	m_CurrSoundPlayer = m_CurrScene->GetSoundPlayer();
}

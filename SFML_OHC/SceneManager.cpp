#include "pch.h"
#include "SceneManager.h"
#include "SceneBase.h"

bool SceneManager::Initialize()
{
    return false;
}

void SceneManager::Update(float dt)
{
    m_Scenes[m_CurrSceneIndex]->Update(dt);
}

void SceneManager::PushToDrawQue()
{
    m_Scenes[m_CurrSceneIndex]->PushToDrawQue();
}

int SceneManager::GetCurrentSceneIndex() const
{
    return m_CurrSceneIndex;
}

void SceneManager::SetCurrentSceneIndex(int index)
{
    m_CurrSceneIndex = index;
}

void SceneManager::PushScene(SceneBase* scene)
{
    scene->Initialize();
    m_Scenes.push_back(scene);
}

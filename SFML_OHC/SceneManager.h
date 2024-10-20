#pragma once
#include "Singleton.h"

class SceneBase;

class SceneManager :
	public Singleton <SceneManager>
{
public:

	bool Initialize();
	void Update(float dt);
	void PushToDrawQue();

	int GetCurrentSceneIndex() const;
	void SetCurrentSceneIndex(int index);
	void PushScene(SceneBase* scene);
private:
	int m_CurrSceneIndex = 0;
	std::vector<SceneBase*> m_Scenes;				//게임 중간 신 삭제 금지
};


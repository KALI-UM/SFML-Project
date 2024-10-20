#pragma once

class GameObject;

class SceneBase
{
public:
	SceneBase();
	//SceneBase(const SceneBase& other);
	//SceneBase(SceneBase&& other);
	virtual ~SceneBase();

	virtual bool Initialize();
	virtual void Update(float dt);

	virtual void SetInitialState();
	void PushToDrawQue();

protected:
	std::vector<GameObject*> m_GameObjects;
	std::string m_Name;
};


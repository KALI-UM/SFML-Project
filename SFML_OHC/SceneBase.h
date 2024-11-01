#pragma once



class Layer;
class GameObject;
class SoundPlayer;
class SceneBase
{
public:
	SceneBase(const std::string& name, unsigned int layercnt = 2, unsigned int viewIndex = 0);
	//SceneBase(const SceneBase& other);
	//SceneBase(SceneBase&& other);
	virtual ~SceneBase();

	bool INITIALIZE();
	void RESET();
	void LATEUPDATE();
	void UPDATE(float dt);
	void PRERENDER();
	void POSTRENDER();
	void EXIT();
	void RELEASE();

	std::string GetName()const;
	SoundPlayer* GetSoundPlayer();

protected:
	virtual bool Initialize();
	virtual void Reset();
	virtual void Update(float dt);
	virtual void LateUpdate();
	virtual void PreRender();
	virtual void PostRender();
	virtual void Exit();
	virtual void Release();
	
	void PushToDrawQue();

	unsigned int				m_TargetViewIndex;
	std::vector<GameObject*>	m_GameObjects;
	SoundPlayer* m_SoundPlayer;
	const std::string			m_Name;
};


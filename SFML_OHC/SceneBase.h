#pragma once

class Layer;
class GameObject;
class SoundPlayer;
typedef std::pair<int, GameObject*> GameObjectInfo;
class SceneBase
{
public:
	SceneBase(const std::string& name, unsigned int layercnt = 2, int viewcnt = 1);
	//SceneBase(const SceneBase& other);
	//SceneBase(SceneBase&& other);
	virtual ~SceneBase();

	bool INITIALIZE();
	void RESET();
	void ENTER();
	void UPDATE(float dt);
	void LATEUPDATE();
	void PRERENDER();
	void POSTRENDER();
	void EXIT();
	void RELEASE();

	std::string GetName()const;
	SoundPlayer* GetSoundPlayer();

	const unsigned int				m_ViewCnt;
protected:
	virtual bool Initialize();
	virtual void Reset();
	virtual void Enter();
	virtual void Update(float dt);
	virtual void LateUpdate();
	virtual void PreRender();
	virtual void PostRender();
	virtual void Exit();
	virtual void Release();

	template <typename T>
	T* AddGameObject(int layerIndex, T* gameObject)
	{
		GetGameObjectsLayerIter(layerIndex).push_back(gameObject);
		return gameObject;
	}

	void RemoveGameObject(GameObjectInfo gobj);
	void RemoveGameObject(int layerIndex, GameObject* gobj);

private:
	const std::string							m_Name;

	struct LayerInfo
	{
		int										viewIndex = 0;
		std::vector<GameObject*>				gameObjects;
	};

	std::list<LayerInfo>						m_GameObjects;
	std::queue<GameObjectInfo>					m_WantsToRemove;

	std::vector<GameObject*>& GetGameObjectsLayerIter(int index);
	std::vector<std::list<LayerInfo>::iterator> m_LayerIndex;


	void PushToDrawQue();
	void RemoveGameObject();


	SoundPlayer* m_SoundPlayer;

};


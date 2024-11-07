#pragma once
#include "SceneBase.h"

//ObjectPoolable을 상속받은 오브젝트만 가능
template<typename T>
class ObjectPool
{
private:
	std::list<T*> unused;
	std::list<T*> used;
	std::queue<T*> needToReturn;

	bool	m_AutoExpand;						//take해줄 수 없을때 오브젝트를 생성할 것인지
	int		m_LayerIndex;
	T*		m_Original;							//원하는 값으로 세팅된 복사원본
	SceneBase*	m_Scene;
public:
	ObjectPool()
	{
	}

	void Initialize(SceneBase* scene, int count, bool autoExpand, int layerIndex, T* copy)
	{
		m_AutoExpand = autoExpand;
		m_LayerIndex = layerIndex;
		m_Original = copy;
		for (int i = 0; i < count; ++i)
		{
			auto obj = new T(*m_Original);
			unused.push_back(obj);
		}
	}

	void Reset()
	{
		while(!used.empty())
		{
			auto& obj = used.front();
			Return(obj);
		}
	}

	void Update(float dt)
	{
		for (auto obj : used)
		{
			if (obj->IsNeedToReturn())
				needToReturn.push(obj);
		}

		while (!needToReturn.empty())
		{
			auto obj = needToReturn.front();
			Return(obj);
			needToReturn.pop();
		}
	}

	void Exit()
	{
		for (auto obj : unused)
		{
			delete obj;
		}

		delete m_Original;
	}

	~ObjectPool()
	{
	}

	T* Take()
	{
		if (unused.empty())
		{
			if (m_AutoExpand!) return nullptr;
			auto obj = new T(*m_Original);
			used.push_back(obj);
			scene->AddGameObject(layerIndex, obj);
			return obj;
		}

		auto obj = unused.front();
		unused.pop_front();
		used.push_back(obj);
		obj->SetActive(true);
		*obj = *m_Original;
		scene->AddGameObject(layerIndex, obj);
		return obj;
	}

	void Return(T* obj)
	{
		auto find = std::find(used.begin(), used.end(), obj);
		if (find == used.end())
		{
			std::cout << "Invaild Obj" << std::endl;
			return;
		}
		used.erase(find);
		obj->SetActive(false);
		unused.push_back(obj);
		m_Scene->RemoveGameObject(m_LayerIndex, obj);
	}
};
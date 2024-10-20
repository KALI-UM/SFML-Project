#pragma once
#include "Singleton.h"

template<typename T>
class ResourceManager :
	public Singleton<ResourceManager<T>>
{
	friend Singleton<ResourceManager<T>>;	//�θ�����ڿ��� ������ �����ֱ� ������ ������ ����
public:
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager(ResourceManager<T>&&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;
	ResourceManager& operator=(ResourceManager&&) = delete;
protected:
	ResourceManager() = default;
	virtual ~ResourceManager() = default;

	static std::unordered_map<std::string, T*> m_Resources;

public:
	bool LoadByFilepath(const std::string& filepath)
	{
		if (m_Resources.find(filepath) == m_Resources.end())
		{
			T* newRes = new T();
			bool success = newRes->loadFromFile(filepath);
			if (success)
			{
				m_Resources[filepath] = newRes;
			}
			else
			{
				delete newRes;
			}
			return success;
		}
		return false;
	}

	bool UnloadByFilepath(const std::string& filepath)
	{
		auto it = m_Resources.find(filepath);
		if (it == m_Resources.end())
		{
			return false;
		}

		delete it->second;
		m_Resources.erase(it);
		return true;
	}

	void UnloadAll()
	{
		for (const auto& pair : m_Resources)
		{
			delete pair.second;
		}
		m_Resources.clear();
	}

	T* GetByFilepath(const std::string& filepath) //���н� nullptr��ȯ
	{
		auto it = m_Resources.find(filepath);
		if (it == m_Resources.end())
		{
			T* newRes = new T();
			if (newRes->loadFromFile(filepath))
			{
				return newRes;
			}
			else
			{
				delete newRes;
				return nullptr;
			}
		}
		else
		{
			return it->second;
		}
	}
};

template<typename T>
std::unordered_map<std::string, T*>  ResourceManager<T>::m_Resources = std::unordered_map<std::string, T*>();
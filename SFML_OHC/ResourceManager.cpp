#include "pch.h"
#include "ResourceManager.h"
#include "DSprite.h"
#include "DAnimation.h"

#include <fstream>


bool ResourceManager::Initialize()
{
	return false;
}

bool ResourceManager::LoadYaml()
{
	YAML::Node test = YAML::LoadFile("resource/numbers.yaml");
	std::cout << test["name"].as<std::string>();
	return false;
}

sf::Texture* ResourceManager::LoadTextureByFileName(const std::string& filepath)
{
	std::unordered_map<std::string, sf::Texture*>::iterator it = m_LoadedTexture.find(filepath);
	if (it == m_LoadedTexture.end())
	{
		sf::Texture* tex = new sf::Texture();
		bool success = tex->loadFromFile(filepath);
		if (success)
		{
			return tex;
		}
		else
		{
			delete tex;
			return nullptr;
		}
	}
	else
	{
		return it->second;
	}
}

bool ResourceManager::LoadTextureByFileName(const std::string& filepath, sf::Texture*& texture)
{
	bool success = false;
	std::unordered_map<std::string, sf::Texture*>::iterator it = m_LoadedTexture.find(filepath);
	if (it == m_LoadedTexture.end())
	{
		success = texture->loadFromFile(filepath);
		if (success)
		{
			m_LoadedTexture.insert({ filepath,texture });
		}
	}
	else
	{
		success = true;
		texture = it->second;
	}

	return success;
}

bool ResourceManager::LoadTextureByFileName(const std::string& filepath, DSprite* sprite)
{
	sf::Texture* tex = LoadTextureByFileName(filepath);
	bool success = tex;

	if (success)
	{
		sprite->SetTexture(tex);
	}
	else
	{
		delete tex;
	}

	return success;
}

bool ResourceManager::LoadTextureByFileName(const std::string& filepath, DAnimation* anim)
{
	sf::Texture* tex = LoadTextureByFileName(filepath);
	bool success = tex;

	if (success)
	{
		anim->SetTexture(tex);
	}
	else
	{
		delete tex;
	}

	return success;
}




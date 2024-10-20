#pragma once
#include "Singleton.h"
#include "SFML/Graphics.hpp"

class DSprite;
class DAnimation;

class ResourceManager :
	public Singleton<ResourceManager>
{
public:
	bool Initialize();
	bool LoadYaml();
	sf::Texture* LoadTextureByFileName(const std::string& filepath);	//실패시 nullptr반환
	bool LoadTextureByFileName(const std::string& filepath, sf::Texture*& texture);
	bool LoadTextureByFileName(const std::string& filepath, DSprite* sprite);
	bool LoadTextureByFileName(const std::string& filepath, DAnimation* anim);


private:
	
	std::unordered_map<std::string, sf::Texture*> m_LoadedTexture;
};


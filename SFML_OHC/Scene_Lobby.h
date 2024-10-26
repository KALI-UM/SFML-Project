#pragma once
#include "SceneBase.h"
class Background_Lobby;
class SoundPlayer;
class DustEffect;
class GameStart;
class Scene_Lobby :
    public SceneBase
{
public:
	Scene_Lobby();
	~Scene_Lobby();

protected:
	bool Initialize() override;
	void Reset() override;
	void Update(float dt) override;
	void Release() override;


private:
	Background_Lobby* m_LobbyImage;
	std::vector< DustEffect*> m_Effects;

	GameStart*		m_GameStart;
	bool			m_Start = false;
	float			m_FadeSpeed;
};


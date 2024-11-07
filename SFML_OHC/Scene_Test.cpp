#include "pch.h"
#include "Scene_Test.h"
#include "TileGrid.h"


Scene_Test::Scene_Test()
	:SceneBase("Test", 2, 2)
{
}

Scene_Test::~Scene_Test()
{
}

bool Scene_Test::Initialize()
{
	AddGameObject(0, new TileGrid());
	return false;
}

void Scene_Test::Enter()
{
}

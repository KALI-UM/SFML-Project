#pragma once
#include "SceneBase.h"


class Scene_Test 
	:public SceneBase
{
public:
	Scene_Test();
	~Scene_Test();

	bool Initialize() override;
	void Update(float dt)override;

	GameObject* obj1;
	GameObject* obj2;
	GameObject* obj3;

};


#pragma once
#include "SceneBase.h"

class Scene_Test :
    public SceneBase
{
public:
    Scene_Test();
    ~Scene_Test();


protected:
	bool Initialize() override;
	//void Reset() override;
	void Enter() override;
	//void Update(float dt) override;
	//void LateUpdate(float dt) override;
	//void FixedUpdate(float dt) override;
	//void Release() override;


};





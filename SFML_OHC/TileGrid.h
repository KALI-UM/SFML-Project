#pragma once
#include "GameObject.h"
class TileGrid :
    public GameObject
{
public:
	TileGrid();
	~TileGrid();

	bool Initialize() override;
	void Reset() override;
	void Update(float dt) override;
	//void LateUpdate(float dt) override;
	//void FixeUpdate(float dt) override;
	//void Release() override;

protected:

};


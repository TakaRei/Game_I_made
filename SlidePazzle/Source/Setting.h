#pragma once
#include "DxLib.h"
#include "SceneManager.h"
#include "Image.h"

class Setting :public Scene {
	int n = 3;
	int select = 0;
	bool guide = true;
public:
	Setting(SceneManager* pManager) :Scene(pManager) {};

	~Setting() {};

	void Update();

	void Draw();
};
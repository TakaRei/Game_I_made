#pragma once
#include "DxLib.h"
#include "SceneManager.h"

class Title :public Scene {
public:
	Title(SceneManager* pManager) :Scene(pManager) {};

	~Title() {};

	void Update();

	void Draw();
};
#pragma once
#include "DxLib.h"
#include "SceneManager.h"

class Result :public Scene {
public:
	Result(SceneManager* pManager) :Scene(pManager) {};

	~Result() {};

	void Update();

	void Draw();
};
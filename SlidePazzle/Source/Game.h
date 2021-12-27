#pragma once
#include "SceneManager.h"
#include "Image.h"
#include <chrono>

class Game :public Scene {

public:
	Game(SceneManager* pManager) :Scene(pManager) {};

	~Game() {};

	void Update();

	void Draw();
};
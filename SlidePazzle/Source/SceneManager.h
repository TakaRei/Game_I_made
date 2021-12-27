#pragma once
#include "Input.h"
#include "Image.h"
#include <chrono>

class SceneManager;

class Scene {
protected:
	SceneManager* manager;
public:
	Scene(SceneManager* pManager) { manager = pManager; };
	virtual ~Scene() {};

	virtual void Update() {};

	virtual void Draw() {};
};

class SceneManager {
	Image* image;
	Input* key;
	std::chrono::system_clock::time_point start, end;
	long long sec = 0;
public:
	Scene* scene;
	SceneManager(Input* pKey) { key = pKey; };
	SceneManager(Input* pKey, Image* pImage) { key = pKey; image = pImage; };
	~SceneManager() { delete scene; };
	Input* GetKey() { return key; }
	Image* GetImage() { return image; }
	long long GetSec() { return sec; }

	std::chrono::system_clock::time_point GetStart() { return start; }
	std::chrono::system_clock::time_point GetEnd() { return end; }

	void setStart(std::chrono::system_clock::time_point start) { this->start = start; }
	void setEnd(std::chrono::system_clock::time_point end) { this->end = end; }
	void setSec(long long sec) { this->sec = sec; }

	void Update() { scene->Update(); };

	void Draw() { scene->Draw(); };
};
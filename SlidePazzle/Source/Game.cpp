#include "DxLib.h"
#include "Game.h"
#include "Result.h"

void Game::Update() {
	if (manager->GetKey()->Check(KEY_INPUT_RIGHT) == 1) {
		manager->GetImage()->swapBox(manager->GetImage()->getX(), manager->GetImage()->getY(), manager->GetImage()->getX() - 1, manager->GetImage()->getY());
	}
	else if (manager->GetKey()->Check(KEY_INPUT_LEFT) == 1) {
		manager->GetImage()->swapBox(manager->GetImage()->getX(), manager->GetImage()->getY(), manager->GetImage()->getX() + 1, manager->GetImage()->getY());
	}
	else if (manager->GetKey()->Check(KEY_INPUT_DOWN) == 1) {
		manager->GetImage()->swapBox(manager->GetImage()->getX(), manager->GetImage()->getY(), manager->GetImage()->getX(), manager->GetImage()->getY() - 1);
	}
	else if (manager->GetKey()->Check(KEY_INPUT_UP) == 1) {
		manager->GetImage()->swapBox(manager->GetImage()->getX(), manager->GetImage()->getY(), manager->GetImage()->getX(), manager->GetImage()->getY() + 1);
	}

	if (manager->GetImage()->finished()) {
		manager->setEnd(std::chrono::system_clock::now());
		manager->setSec(std::chrono::duration_cast<std::chrono::seconds>(manager->GetEnd() - manager->GetStart()).count());
		manager->scene = new Result(manager);
		delete this;
	}
}

void Game::Draw() {
	for (int i = 0; i < manager->GetImage()->getDiv(); i++) {
		for (int j = 0; j < manager->GetImage()->getDiv(); j++) {
			if (j == manager->GetImage()->getX() && i == manager->GetImage()->getY()) {
				continue;
			}

			DrawExtendGraph((640 / manager->GetImage()->getDiv()) * j, (480 / manager->GetImage()->getDiv()) * i, (640 / manager->GetImage()->getDiv()) * j + (640 / manager->GetImage()->getDiv()), (480 / manager->GetImage()->getDiv()) * i + (480 / manager->GetImage()->getDiv()), manager->GetImage()->getGraph(manager->GetImage()->getBox(j, i)), TRUE);
			if (manager->GetImage()->getGuide()) {
				DrawFormatString((640 / manager->GetImage()->getDiv()) * j, (480 / manager->GetImage()->getDiv()) * i, GetColor(255, 0, 0), "%d", manager->GetImage()->getBox(j, i) + 1);
			}
		}
	}
}
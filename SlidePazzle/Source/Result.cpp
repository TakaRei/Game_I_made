#include "Result.h"
#include "Setting.h"

#include<iostream>
#include<vector>
#include<string>
#include<chrono>

using namespace std;

void Result::Update() {
	if (manager->GetKey()->Check(KEY_INPUT_X) == 1) {
		manager->scene = new Setting(manager);
		delete this;
	}
}

void Result::Draw() {
	DrawFormatString(64, 64, GetColor(255, 255, 255), "クリア！");
	DrawFormatString(64, 128, GetColor(255, 255, 255), "クリアタイム：%lld分%lld秒", manager->GetSec() / 60, manager->GetSec() % 60);
	DrawFormatString(64, 160, GetColor(255, 255, 255), "Xキーでもう一度遊ぶ\n\nEscキーで終了する");
	if (manager->GetImage()->getXSize() > manager->GetImage()->getYSize()) {
		DrawExtendGraph(0, 214, 640, 480, manager->GetImage()->getHandle(manager->GetImage()->getSelect()), TRUE);
	}
	else {
		DrawExtendGraph(320, 0, 640, 480, manager->GetImage()->getHandle(manager->GetImage()->getSelect()), TRUE);
	}
}
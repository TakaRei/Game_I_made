#include "Setting.h"
#include "Game.h"

#include<iostream>
#include<vector>
#include<string>
#include<chrono>

using namespace std;

void Setting::Update() {
	if (manager->GetKey()->Check(KEY_INPUT_R) == 1) {
		n++;
	}
	else if (manager->GetKey()->Check(KEY_INPUT_T) == 1) {
		n--;
		if (n < 3) {
			n = 3;
		}
	}

	if (manager->GetKey()->Check(KEY_INPUT_F) == 1) {
		select++;
		select %= manager->GetImage()->getSize();
	}
	else if (manager->GetKey()->Check(KEY_INPUT_G) == 1) {
		select += manager->GetImage()->getSize();
		select--;
		select %= manager->GetImage()->getSize();
	}

	if (manager->GetKey()->Check(KEY_INPUT_C) == 1) {
		guide = !guide;
	}

	if (manager->GetKey()->Check(KEY_INPUT_RETURN) == 1) {
		manager->GetImage()->setGuide(guide);
		manager->GetImage()->setSelect(select);
		manager->GetImage()->setN(n);
		manager->setStart(chrono::system_clock::now());
		manager->scene = new Game(manager);
		delete this;
	}
}

void Setting::Draw() {
	DrawFormatString(64, 64, GetColor(255, 255, 255), "\n設定：ENTERキーでゲームへ");
	DrawFormatString(64, 96, GetColor(255, 255, 255), "\n操作：←↓↑→キーでスライド");
	DrawFormatString(64, 128, GetColor(255, 255, 255), "\n難易度　　　：%d×%d　Rキーで難易度UP、Tキーで難易度DOWN", n, n);
	DrawFormatString(64, 160, GetColor(255, 255, 255), "\n挑戦する画像：%d/%d　Fキーで増加、Gキーで減少", select + 1, manager->GetImage()->getSize());
	DrawFormatString(64, 192, GetColor(255, 255, 255), "\nガイド　　　：%s　　Cキーで変更", (guide ? "あり" : "なし"));
	DrawExtendGraph(64, 240, 544, 480, manager->GetImage()->getHandle(select), TRUE);
}
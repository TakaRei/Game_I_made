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
	DrawFormatString(64, 64, GetColor(255, 255, 255), "\n�ݒ�FENTER�L�[�ŃQ�[����");
	DrawFormatString(64, 96, GetColor(255, 255, 255), "\n����F���������L�[�ŃX���C�h");
	DrawFormatString(64, 128, GetColor(255, 255, 255), "\n��Փx�@�@�@�F%d�~%d�@R�L�[�œ�ՓxUP�AT�L�[�œ�ՓxDOWN", n, n);
	DrawFormatString(64, 160, GetColor(255, 255, 255), "\n���킷��摜�F%d/%d�@F�L�[�ő����AG�L�[�Ō���", select + 1, manager->GetImage()->getSize());
	DrawFormatString(64, 192, GetColor(255, 255, 255), "\n�K�C�h�@�@�@�F%s�@�@C�L�[�ŕύX", (guide ? "����" : "�Ȃ�"));
	DrawExtendGraph(64, 240, 544, 480, manager->GetImage()->getHandle(select), TRUE);
}
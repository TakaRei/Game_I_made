#include "Title.h"
#include "Setting.h"

#include<iostream>
#include<vector>
#include<string>
#include<filesystem>

using namespace std;

void Title::Update() {
	if (manager->GetKey()->Check(KEY_INPUT_X) == 1) {
		manager->scene = new Setting(manager);
		delete this;
	}
}

void Title::Draw() {
	DrawFormatString(64, 64, GetColor(255, 255, 255), "�X���C�h�p�Y���FX�L�[�Ŏ���");
	DrawFormatString(64, 96, GetColor(255, 255, 255), "���̃Q�[����image�t�H���_�ɉ摜�����邾����\n���̉摜�ŃX���C�h�p�Y����V�Ԃ��Ƃ��ł��܂��I\n\nimage�t�H���_�̏ꏊ��SlidePazzle/image�ł�");
}
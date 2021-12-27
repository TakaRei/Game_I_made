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
	DrawFormatString(64, 64, GetColor(255, 255, 255), "スライドパズル：Xキーで次へ");
	DrawFormatString(64, 96, GetColor(255, 255, 255), "このゲームはimageフォルダに画像を入れるだけで\nその画像でスライドパズルを遊ぶことができます！\n\nimageフォルダの場所はSlidePazzle/imageです");
}
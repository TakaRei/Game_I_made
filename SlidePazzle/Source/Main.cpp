#include "DxLib.h"
#include "Input.h"
#include "SceneManager.h"
#include "Title.h"

#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <utility>
#include <cstdlib>
#include <ctime>
#include <string>

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);
	SetMainWindowText("スライドパズル");

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	SetDrawScreen(DX_SCREEN_BACK);

	Input* keyboard = new Input();
	Image* image = new Image();

	SceneManager* manager;

	manager = new SceneManager(keyboard, image);

	manager->scene = new Title(manager);

	while (!ProcessMessage())
	{
		ClearDrawScreen();

		keyboard->Update();

		manager->Draw();

		manager->Update();

		if (manager->GetKey()->Check(KEY_INPUT_ESCAPE) == 1) {
			break;
		}

		ScreenFlip();
	}

	delete manager;
	delete keyboard;
	delete image;

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}
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

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);
	SetMainWindowText("�X���C�h�p�Y��");

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
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

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}
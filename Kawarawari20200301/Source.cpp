#include "DxLib.h"
#include <cstdio>

void KeyUpdate();
void Game();
void Title();
void Result();

enum SCENE {
	TITLE, GAME, RESULT
};

int key[256] = { NULL };
int scene = TITLE;
bool gameend = 0;
int kawarawarinumber = 0;
int kawarapicture[] = { LoadGraph("image/kawara.png"),
						LoadGraph("image/kawaraleft.png"),
						LoadGraph("image/kawararight.png") };


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

	SetDrawScreen(DX_SCREEN_BACK);


	
	while (!ProcessMessage() && gameend == FALSE)
	{
		ClearDrawScreen();

		KeyUpdate();

		switch (scene)
		{
		case TITLE:
			Title();
			break;

		case GAME:
			Game();
			break;
			
		case RESULT:
			Result();
			break;
		}



		ScreenFlip();
	}

	

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}

void KeyUpdate()
{
	char buf[256];

	GetHitKeyStateAll(buf);

	for (int i = 0; i < 256; i++)
	{
		if (buf[i] == 1)
		{
			key[i]++;
		}
		else
		{
			key[i] = 0;
		}
	}
}

void Game()
{

	int rushnumber = 0;
	int power = 0;
	kawarawarinumber = 0;
	double LimitTime = 0;

	gameend = 0;

	// 60frame = 1second 600frame = 10second 

	while (!ProcessMessage() && LimitTime < 600)
	{
		KeyUpdate();

		ClearDrawScreen();

		power = (5 * rushnumber * rushnumber) / 2;

			if (key[KEY_INPUT_RETURN] == 1)
			{
				rushnumber += 1;
			}
		
		

		LimitTime++;

		DrawFormatString(32, 32, GetColor(255, 255, 255), "Enter�L�[��A�ł��ăp���[�����߂悤!");
		DrawFormatString(64, 64, GetColor(255, 255, 255), "�A��%d��", rushnumber);
		DrawFormatString(128, 128, GetColor(255, 255, 255), "�p���[:%d", power);
		DrawFormatString(256, 256, GetColor(255, 255, 255), "�c�莞��%f�b",(double)((600 - LimitTime) / 60));
		DrawFormatString(16, 16, GetColor(255, 255, 255), "%d", key[KEY_INPUT_RETURN]);

		ScreenFlip();
	} 

	scene = RESULT;

	kawarawarinumber = power / 1024;

}

void Title()
{

	if (key[KEY_INPUT_G] > 0)
	{
		 scene = GAME;
	}

	if (key[KEY_INPUT_ESCAPE] > 0)
	{
		gameend = TRUE;
	}


	DrawFormatString(32, 32, GetColor(255, 255, 255), "G�L�[�ŃQ�[���X�^�[�g");
	DrawFormatString(64, 64, GetColor(255, 255, 255), "Esc�L�[�ŃQ�[�����I������");

	//�ȉ��摜����m�F

	int kawarapicture[] = { LoadGraph("image/kawara.png"),
						LoadGraph("image/kawaraleft.png"),
						LoadGraph("image/kawararight.png") };

	int graphx = 128;
	int graphy = 128;

	if (key[KEY_INPUT_RIGHT] > 0)
	{
		graphx += 1;
	}
	if (key[KEY_INPUT_LEFT] > 0)
	{
		graphx -= 1;
	}
	if (key[KEY_INPUT_UP] > 0)
	{
		graphy -= 1;
	}
	if (key[KEY_INPUT_DOWN] > 0)
	{
		graphy += 1;
	}

	DrawRotaGraph(128, 128, 0.25, 0, kawarapicture[1], TRUE);
	DrawRotaGraph(graphx, graphy, 0.25, 0, kawarapicture[2], TRUE);



}

void Result()
{
	if (key[KEY_INPUT_T] > 0)
	{
		scene = TITLE;
	}

	if (key[KEY_INPUT_ESCAPE] > 0)
	{
		gameend = TRUE;
	}

	DrawFormatString(32, 32, GetColor(255, 255, 255), "T�L�[�Ń^�C�g����ʂɖ߂�");
	DrawFormatString(64, 64, GetColor(255, 255, 255), "Esc�L�[�ŃQ�[�����I������");

	if (kawarawarinumber == 0)
	{
		DrawFormatString(16, 16, GetColor(255, 255, 255), "���͂��܂���ł���...");
	}
	else
	{
		DrawFormatString(16, 16, GetColor(255, 255, 255), "����%d���܂���!", kawarawarinumber);
	}

}
	



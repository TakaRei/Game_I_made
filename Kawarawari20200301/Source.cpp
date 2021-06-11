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

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
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

	

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
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

		DrawFormatString(32, 32, GetColor(255, 255, 255), "Enterキーを連打してパワーをためよう!");
		DrawFormatString(64, 64, GetColor(255, 255, 255), "連打%d回", rushnumber);
		DrawFormatString(128, 128, GetColor(255, 255, 255), "パワー:%d", power);
		DrawFormatString(256, 256, GetColor(255, 255, 255), "残り時間%f秒",(double)((600 - LimitTime) / 60));
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


	DrawFormatString(32, 32, GetColor(255, 255, 255), "Gキーでゲームスタート");
	DrawFormatString(64, 64, GetColor(255, 255, 255), "Escキーでゲームを終了する");

	//以下画像動作確認

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

	DrawFormatString(32, 32, GetColor(255, 255, 255), "Tキーでタイトル画面に戻る");
	DrawFormatString(64, 64, GetColor(255, 255, 255), "Escキーでゲームを終了する");

	if (kawarawarinumber == 0)
	{
		DrawFormatString(16, 16, GetColor(255, 255, 255), "瓦はわれませんでした...");
	}
	else
	{
		DrawFormatString(16, 16, GetColor(255, 255, 255), "瓦が%d個われました!", kawarawarinumber);
	}

}
	



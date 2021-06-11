#include "DxLib.h"
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <utility>
#include <cstdlib>
#include <ctime>
#include <string>
#include <stack>
#include "Base.h"
using namespace std;

void title();
void KeyUpdate();
void game();
void initGame();
void result();
void prepare();

enum Scene {
	TITLE,GAME,SELECT,PREPARE,OPTION,RESULT,INIT
};

int key[256] = { NULL };
int scene = TITLE;
bool flag = true;
vector<Base> ObjLis;
int money = 0;
int Number = 0;
int Power = 1;
int HP = 0;
int Score = 0;
int MaxScore = 0;
const string face[6] = {
	"(>_<)b","m9(^�D^)","(-_-)","(^^;","(-`_'-)","(T_T)"
};

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

	SetDrawScreen(DX_SCREEN_BACK);

	while (!ProcessMessage() && flag != false) {
		flag = (key[KEY_INPUT_ESCAPE] > 0) ? false : true;
		ClearDrawScreen();
		KeyUpdate();

		switch (scene) {
		case TITLE:
			title();
			break;
		case GAME:
			game();
			break;
		case INIT:
			initGame();
			break;
		case RESULT:
			result();
			break;
		case PREPARE:
			prepare();
			break;
		}

		ScreenFlip();
	}

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}

void KeyUpdate() {
	char buf[256];

	GetHitKeyStateAll(buf);

	for (int i = 0; i < 256; i++) {
		if (buf[i] == 1) {
			key[i]++;
		}
		else {
			key[i] = 0;
		}
	}
}

void title() {
	if (key[KEY_INPUT_RETURN] == 1) {
		scene = INIT;
	}

	DrawFormatString(64, 64, GetColor(255, 255, 255), "���V���[�e�B���O\n\n�ړ��F���L�[\n\n�U���FSPACE�L�[\n\nEnter�L�[�������Ď���");
}

void game() {
	static int wait = 60;
	static int bulletWait = 0;
	if (key[KEY_INPUT_SPACE] > 0 && bulletWait<=0) {
		Base bullet = Base(ObjLis[0].CurrentX()+16, ObjLis[0].CurrentY()-16, 4,12,12,0, GetColor(255, 255, 255), "��");
		ObjLis.push_back(bullet);
		money-=100;
		bulletWait = 5;
	}

	for (int i = 0; i < ObjLis.size(); i++) {
		for (string j : face) {
			if (ObjLis[i].CurrentS() == j && GetRand(500) < 1 && ObjLis[i].CurrentExist()) {
				Base bullet = Base(ObjLis[i].CurrentX()+16, ObjLis[i].CurrentY(), 4,8,8,0, GetColor(255, 0, 0), "v");
				ObjLis.push_back(bullet);
			}
		}
	}

	for (int i = 0; i < ObjLis.size(); i++) {
		if (ObjLis[i].CurrentS() == "��") {
			ObjLis[i].MoveY(-8);
			for (int j = 0; j < ObjLis.size(); j++) {
				if (i == j || !ObjLis[j].CurrentExist()) {
					continue;
				}

				if (ObjLis[i].isCollision(ObjLis[j])) {
					ObjLis[j].damege(Power);
					if (ObjLis[j].CurrentHp() <= 0) {
						ObjLis[j].Dead();
						if (ObjLis[j].CurrentS() != "v") {
						money += GetRand(1000);
						Number++;
						Score += 1000;
						}
						else {
							Score += 10000;
						}
					}
					ObjLis[i].Dead();
					
				}
			}
		}

		if (ObjLis[i].CurrentS() == "v") {
			ObjLis[i].MoveY(2);

			if (ObjLis[i].isCollision(ObjLis[0])) {
				ObjLis[0].HpUp(-1);
				ObjLis[i].Dead();
				if (ObjLis[0].CurrentHp() <= 0) {
					money = 0;
					scene = RESULT;
				}
			}
		}
		
		for (string j : face) {
			if (ObjLis[i].CurrentS() == j && wait==0) {
				ObjLis[i].MoveY(1);
			}
		}
	}

	for (int i = 0; i < ObjLis.size(); i++) {
		if (ObjLis[i].CurrentY() < 0) {
			ObjLis.erase(ObjLis.begin() + i);
		}
		else if (ObjLis[i].CurrentY() > 480) {
			ObjLis.erase(ObjLis.begin() + i);
		}
	}

	if (key[KEY_INPUT_RIGHT] > 0 && !ObjLis.empty()) {
		ObjLis[0].MoveX(4);
		if (ObjLis[0].CurrentX()+52 > 640) {
			ObjLis[0].MoveX(-4);
		}
	}
	else if (key[KEY_INPUT_LEFT] > 0 && !ObjLis.empty()) {
		ObjLis[0].MoveX(-4);
		if (ObjLis[0].CurrentX() < 0) {
			ObjLis[0].MoveX(4);
		}
	}

	if (!ObjLis.empty()) {
		for (int i = 0; i < ObjLis.size(); i++) {
			ObjLis[i].Draw();
		}
	}
	DrawFormatString(32,400, GetColor(255, 255, 255), "�c���F%d�~\nHP�F%d\n���j���F%d\nScore : %d", money, ObjLis[0].CurrentHp(), Number,Score);

	if (wait == 0) {
		wait = 60;
	}
	else {
		wait--;
	}

	bulletWait--;

	if (Number >= 30) {
		scene = RESULT;
	}

	if (money <= 0) {
		scene = RESULT;
	}
}

void initGame() {
	money += GetRand(10000);
	Number = 0;
	Score = 0;
	ObjLis.clear();

	Base player = Base(320, 440, 6, 6, 52, 0, GetColor(255, 255, 255), "�@��\n���ʁ�");
	ObjLis.push_back(player);

	Base enemy[5][6];
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j <6; j++) {
			enemy[i][j] = Base(j * 100+32, i * 32, 16,6,52,GetRand(4),GetColor(GetRand(255), GetRand(255), GetRand(255)), face[GetRand(5)]);
			ObjLis.push_back(enemy[i][j]);
		}
	}
	scene = PREPARE;
}

void result() {

	if (key[KEY_INPUT_RETURN] == 1) {
		scene = TITLE;
	}

	if (MaxScore < Score) {
		MaxScore = Score;
	}

	if (money <= 0) {
		DrawFormatString(64, 240, GetColor(255, 255, 255), "    GAMEOVER\n\n����ԃX�����܂���......\n\n\n\nEnter�L�[�Ń^�C�g����");
	}
	else {
		DrawFormatString(64, 240, GetColor(255, 255, 255), "%d�~�l��!\n\nScore : %d\n\nBest Score : %d\n\nEnter�L�[�Ń^�C�g����", money,Score,MaxScore);
	}
	
}

void prepare() {
	if (key[KEY_INPUT_SPACE] == 1) {
		if (money >= 1000) {
			Power++;
			money -= 1000;
		}
	}

	if (key[KEY_INPUT_RETURN] == 1) {
		if (money >= 10000) {
			ObjLis[0].HpUp(1);
			money -= 10000;
		}
	}

	if (key[KEY_INPUT_S] == 1) {
		scene = GAME;
	}

	DrawFormatString(64, 64, GetColor(255, 255, 255), "�������F%d�~\n\nSPACE�L�[��1000�~�����Ēe�̈З�UP\n�e�̈З́F�G��%d�񓖂Ă�Γ|����\n\nEnter�L�[��10000�~�����đϋv��UP\n���݂�HP�F%d\n\nS�L�[�ŃX�^�[�g", money, (6 <= Power) ? 1 : 6 - Power,ObjLis[0].CurrentHp());
}
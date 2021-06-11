#pragma once
#include<string>
#include<iostream>
#include"DxLib.h"

using namespace std;

class Base{
public:
	Base(){
		this->x = 0;
		this->y = 0;
		this->size = 0;
		this->s = "";
	}
	Base(int x, int y, int size,int vertical,int horizon,int hp,int color, string s) {
		this->x = x;
		this->y = y;
		this->size = size;
		this->vertical = vertical;
		this->horizon = horizon;
		this->hp += hp;
		this->color = color;
		this->s = s;
	}
private :
	int x, y, size,vertical,horizon,hp=1;
	unsigned int color;
	bool exist = true;
	string s;
public:
	void Draw() {
		if (this->exist) {
			DrawFormatString(x, y, color, s.c_str());
		}
	}

	void HpUp(int HP) {
		this->hp += HP;
	}

	void Dead(){
		this->exist = false;
	}

	void MoveX(int vx) {
		this->x += vx;
	}
	void MoveY(int vy) {
		this->y += vy;
	}

	int CurrentX() {
		return this->x;
	}

	int CurrentY() {
		return this->y;
	}

	string CurrentS() {
		return this->s;
	}

	bool CurrentExist() {
		return this->exist;
	}

	int CurrentHp() {
		return this->hp;
	}

	void damege(int p) {
		this->hp -= p;
	}

	bool isCollision(Base B) {
	/*	if (this->exist && B.exist) {
			return ((B.x - this->x) * (B.x - this->x) + (B.y - this->y) * (B.y - this->y) < (B.size + this->size) * (B.size + this->size));
		}
		else {
			return false;
		}*/

		if (this->exist && B.exist) {
			return (this->x < B.x + B.horizon && this->x + this->horizon > B.x && this->y < B.y + B.vertical && this->y + this->vertical > B.y);
		}
		else {
			return false;
		}
	}
};


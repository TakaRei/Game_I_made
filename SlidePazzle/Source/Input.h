#pragma once
#include<iostream>
#include"DxLib.h"

using namespace std;

class Input {
private:
	char buf[256];
	int key[256];
public:
	Input() {
		for (int i = 0; i < 256; i++) {
			this->buf[i] = 0;
			this->key[i] = 0;
		}
	};

	~Input() {};

	void Update() {
		GetHitKeyStateAll(this->buf);

		for (int i = 0; i < 256; i++) {
			if (this->buf[i] == 1) {
				this->key[i]++;
			}
			else {
				this->key[i] = 0;
			}
		}
	}

	int Check(int key) {
		return this->key[key];
	}
};
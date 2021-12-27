#pragma once
#include"DxLib.h"
#include<vector>
#include<string>
#include<filesystem>
#include<utility>
#include<algorithm>
#include<cstdlib>
#include<ctime>

using namespace std;

class Image {
private:
	vector<string> s;
	vector<int> handle;
	int n = 3;
	int xSize, ySize;
	int x, y;
	int select = 0;
	vector<vector<int>> box;
	int* graph;
	const int dx[4] = { 1,-1,0,0, }, dy[4] = { 0,0,-1,1 };
	int count = 0;
	bool guide = true;

public:
	Image() {
		for (const auto& file : filesystem::directory_iterator("image")) {
			s.emplace_back(file.path().string());

			handle.emplace_back(LoadGraph(file.path().string().c_str()));
		}

		box.resize(n);
		for (int i = 0; i < box.size(); i++) {
			box[i].resize(n);
			for (int j = 0; j < box[i].size(); j++) {
				box[i][j] = count;
				count++;
			}
		}
		count = 0;

		graph = new int[n * n];

		GetGraphSize(handle[select], &xSize, &ySize);
		LoadDivGraph(s[select].c_str(), n * n, n, n, xSize / n, ySize / n, graph);

		srand(time(NULL));
		x = rand() % n;
		y = rand() % n;

		for (int i = 0; i < 1000; i++) {
			int a = rand() % 4;
			if (x + dx[a] >= 0 && x + dx[a] < n && y + dy[a] >= 0 && y + dy[a] < n) {
				swap(box[y][x], box[y + dy[a]][x + dx[a]]);
				x += dx[a];
				y += dy[a];
			}
		}
	}

	~Image() {
		delete[] graph;
	}

	void swapBox(int x1, int y1, int x2, int y2) {
		if (x2 >= 0 && x2 < n && y2 >= 0 && y2 < n) {
			swap(box[y1][x1], box[y2][x2]);
			this->x = x2;
			this->y = y2;
		}
	}

	int getSize() {
		return handle.size();
	}

	int getHandle(int key) {
		return handle[key % this->getSize()];
	}

	auto getHandleAll() {
		return handle;
	}

	int getBox(int x, int y) {
		return box[y][x];
	}

	auto getBoxAll() {
		return box;
	}

	int getGraph(int key) {
		return graph[key];
	}

	auto getGraphAll() {
		return graph;
	}

	int getXSize() {
		return xSize;
	}

	int getYSize() {
		return ySize;
	}

	int getDiv() {
		return n;
	}

	int getX() {
		return x;
	}

	int getY() {
		return y;
	}

	bool getGuide() {
		return guide;
	}

	auto getS() {
		return s;
	}

	int getSsize() {
		return s.size();
	}

	int getSelect() {
		return select;
	}

	void setX(int x) {
		this->x = x;
	}

	void setY(int y) {
		this->y = y;
	}

	void setGuide(bool guide) {
		this->guide = guide;
	}

	void setSelect(int select) {
		this->select = select;

		GetGraphSize(handle[select], &xSize, &ySize);
		LoadDivGraph(s[select].c_str(), n * n, n, n, xSize / n, ySize / n, graph);
	}

	void setN(int n) {
		this->n = n;

		box.resize(n);
		for (int i = 0; i < box.size(); i++) {
			box[i].resize(n);
			for (int j = 0; j < box[i].size(); j++) {
				box[i][j] = count;
				count++;
			}
		}
		count = 0;

		graph = new int[n * n];

		GetGraphSize(handle[select], &xSize, &ySize);
		LoadDivGraph(s[select].c_str(), n * n, n, n, xSize / n, ySize / n, graph);

		srand(time(NULL));
		x = rand() % n;
		y = rand() % n;

		for (int i = 0; i < 1000; i++) {
			int a = rand() % 4;
			if (x + dx[a] >= 0 && x + dx[a] < n && y + dy[a] >= 0 && y + dy[a] < n) {
				swap(box[y][x], box[y + dy[a]][x + dx[a]]);
				x += dx[a];
				y += dy[a];
			}
		}
	}

	bool finished() {
		count = 0;
		for (int i = 0; i < box.size(); i++) {
			for (int j = 0; j < box[i].size(); j++) {
				if (box[i][j] != count) {
					return false;
				}
				count++;
			}
		}
		count = 0;
		return true;
	}
};
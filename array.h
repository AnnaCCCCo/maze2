#pragma once
#ifndef ARRAY_H
#define ARRAY_H
#include <vector>
using namespace std;

class Array1 {
private:
	int width = 0;
	int length = 0;
	int exitNum = 0;
	int exit = 0;
	struct point {
		int x;
		int y;
		int direction;
		point(int _x, int _y, int _d) {
			x = _x;
			y = _y;
			direction = _d;
		}
		point(int _x, int _y) {
			x = _x;
			y = _y;
			direction = 0;
		}
		point() {
			x = 0;
			y = 0;
			direction = 0;
		}
	};
	const int up = 1;
	const int down = 2;
	const int leftn = 3;
	const int rightn = 4;
	vector<point> walls;

public:
	//point start;
	char** storage;//storage[w][l]
	vector<point> starts;
	vector<point> entrances;
	void createArray(int w, int l);
	void assignArray();
	void printArray();
	void generater(int e);

	void FindBlock(int x, int y);
};

#endif // !ARRAY_H



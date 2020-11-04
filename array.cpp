#include <iostream>
#include "array.h"
#include <time.h>
#include <vector>
using namespace std;

void Array1::createArray(int w, int l) {
	storage = new char* [w];
	for (int i = 0; i < w; i++) {
		storage[i] = new char[l];
	}
	width = w;
	length = l;
}

void Array1::assignArray() {
	//draw all
	for (int w = 0; w < width; w++) {
		for (int l = 0; l < length; l++) {
			storage[w][l] = 'X';
		}
	}
}

void Array1::FindBlock(int x, int y) {
	if (x - 1 > 0 && storage[x - 1][y] == 'X') {//up
		walls.push_back(point(x - 1, y, up));
	}
	if (x + 1 < width - 1 && storage[x + 1][y] == 'X') {//down
		walls.push_back(point(x + 1, y, down));
	}
	if (y - 1 > 0 && storage[x][y - 1] == 'X') {//left
		walls.push_back(point(x, y - 1, leftn));
	}
	if (y + 1 < length - 1 && storage[x][y + 1] == 'X') {//right
		walls.push_back(point(x, y + 1, rightn));
	}
}

void Array1::generater(int e) {
	srand((unsigned)time(NULL));
	point entrance1, entrance2, entrance3, entrance4;

	//draw exit
	switch (e) {
	case 4: {
		entrance4 = point(rand() % 2, rand() % (length - 2) + 1);
		if (entrance4.x == 1) {
			entrance4.x = width - 1;
		}
		storage[entrance4.x][entrance4.y] = 'E';
		starts.push_back(point(entrance4.x, entrance4.y));
		entrances.push_back(point(entrance4.x, entrance4.y));
	}
	case 3: {
		entrance3 = point(rand() % (width - 2) + 1, rand() % 2);
		if (entrance3.y == 1) {
			entrance3.y = length - 1;
		}
		storage[entrance3.x][entrance3.y] = 'E';
		starts.push_back(point(entrance3.x, entrance3.y));
		entrances.push_back(point(entrance3.x, entrance3.y));
	}
	case 2: {
		entrance2 = point(rand() % 2, rand() % (length - 2) + 1);
		if (storage[entrance2.x][entrance2.y] == 'E') {
			entrance2.y++;
			if (entrance2.y > length - 2) {
				entrance2.y = entrance2.y - 2;
			}
		}
		if (entrance2.x == 1) {
			entrance2.x = width - 1;
		}
		storage[entrance2.x][entrance2.y] = 'E';
		starts.push_back(point(entrance2.x, entrance2.y));
		entrances.push_back(point(entrance2.x, entrance2.y));
	}
	case 1: {
		entrance1 = point(rand() % (width - 2) + 1, rand() % 2);
		if (storage[entrance1.x][entrance1.y] == 'E') {
			entrance1.x++;
			if (entrance1.x > width - 2) {
				entrance1.x = entrance1.x - 2;
			}
		}
		if (entrance1.y == 1) {
			entrance1.y = length - 1;
		}
		storage[entrance1.x][entrance1.y] = 'E';
		starts.push_back(point(entrance1.x, entrance1.y));
		entrances.push_back(point(entrance1.x, entrance1.y));
	}
	}

	while (starts.size()) {
		srand((unsigned)time(NULL));

		//randomly pick a start
		int startsize = starts.size();
		int randstart = rand() % startsize;
		point start = starts[randstart];

		FindBlock(start.x, start.y);

		while (walls.size()) {
			//randomly pick walls
			srand((unsigned)time(NULL));
			int wallsize = walls.size();
			int randnum = rand() % wallsize;
			point selectwall = walls[randnum];
			point selectwall2 = selectwall;

			//based on the direction of current location and the 1st wall location
			//located the 2nd wall
			switch (selectwall.direction) {
			case 1: //up
				selectwall2.x--; break;
			case 2: //down
				selectwall2.x++; break;
			case 3: //left
				selectwall2.y--; break;
			case 4: //right
				selectwall2.y++; break;
			}

			//if the 2nd wall is bondray
			//ignore it
			if (selectwall.x != width - 1 && selectwall.x != 0 &&
				selectwall.y != length - 1 && selectwall.y != 0) {
				if (selectwall2.x == width - 1 || selectwall2.x == 0 ||
					selectwall2.y == length - 1 || selectwall2.y == 0) {
					storage[selectwall.x][selectwall.y] = ' ';
					FindBlock(selectwall.x, selectwall.y);
				}
				//if both of them are walls, 'X'
				//make them into empty ' '
				else if (storage[selectwall2.x][selectwall2.y] == 'X') {
					storage[selectwall.x][selectwall.y] = ' ';
					storage[selectwall2.x][selectwall2.y] = ' ';
					FindBlock(selectwall2.x, selectwall2.y);
				}

			}
			//erase this one in the vector
			walls.erase(walls.begin() + randnum);
		}
		starts.erase(starts.begin() + randstart);
	}

	//draw center/end
	//put this in the last
	//make sure the start point will not be traped
	if (!(width % 2) && !(length % 2)) {
		for (int a = width / 2 - 2; a < width / 2 + 2; a++) {
			for (int b = length / 2 - 2; b < length / 2 + 2; b++) {
				storage[a][b] = ' ';
			}
		}
		storage[width / 2][length / 2] = 'F';
	}
	else if (width % 2 && !(length % 2)) {
		for (int a = (width - 1) / 2 - 1; a <= (width - 1) / 2 + 1; a++) {
			for (int b = length / 2 - 2; b < length / 2 + 2; b++) {
				storage[a][b] = ' ';
			}
		}
		storage[(width - 1) / 2][length / 2] = 'F';
	}
	else if (!(width % 2) && length % 2) {
		for (int a = width / 2 - 2; a < width / 2 + 2; a++) {
			for (int b = (length - 1) / 2 - 1; b <= (length - 1) / 2 + 1; b++) {
				storage[a][b] = ' ';
			}
		}
		storage[width / 2][(length - 1) / 2] = 'F';
	}
	else if (width % 2 && length % 2) {
		for (int a = (width - 1) / 2 - 1; a <= (width - 1) / 2 + 1; a++) {
			for (int b = (length - 1) / 2 - 1; b <= (length - 1) / 2 + 1; b++) {
				storage[a][b] = ' ';
			}
		}
		storage[(width - 1) / 2][(length - 1) / 2] = 'F';
	}
}

void Array1::printArray() {
	for (int a = 0; a < width; a++) {
		for (int b = 0; b < length; b++) {
			if (storage[a][b] == 'o') {
				cout << ' ';
			}
			else {
				cout << storage[a][b];
			}
		}
		cout << endl;
	}
}
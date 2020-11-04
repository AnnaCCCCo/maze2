#include <iostream>
#include <stdlib.h>
#include <Windows.h>
#include <fstream>
#include <string>
#include <vector>
#include "array.h"
#include "Astar.h"

using namespace std;
int width;
int length;
int exitNum;
Array1 maze;
Astar astar;
char anS, anR, anP;

void findpath() {
	astar.initAstar(maze.storage, width, length);
	while (maze.entrances.size()) {
		astar.entrances.push_back(PathPoint(maze.entrances[0].x, maze.entrances[0].y));
		maze.entrances.erase(maze.entrances.begin());
	}
	PathPoint end(width / 2, length / 2);

	while (astar.entrances.size()) {
		PathPoint start = astar.entrances[0];
		list<PathPoint*>path = astar.getPath(start, end);
		for (auto& p : path) {
			if (maze.storage[p->x][p->y] == ' ') {
				maze.storage[p->x][p->y] = 'P';
				maze.printArray();
				Sleep(100);
				maze.storage[p->x][p->y] = 'o';
				system("cls");
			}
		}
		astar.entrances.erase(astar.entrances.begin());
	}
}

void saveFile() {
	ofstream outfile;
	string FilePath;
	string FileName;
	cout << "Please enter the path of the file:";
	cin >> FilePath;
	FilePath += "\\";
	cout << "Please enter the name of the file:";
	cin >> FileName;
	FilePath += FileName;
	FilePath += ".txt";

	outfile.open(FilePath);
	for (int a = 0; a < width; a++) {
		for (int b = 0; b < length; b++) {
			if (maze.storage[a][b] != ' ') {
				outfile << maze.storage[a][b];
			}
			else {
				outfile << " ";
			}
		}
		outfile << endl;
	}
	outfile.close();
}

void generate() {
	cout << "This is a maze generater." << endl;
	cout << "Enter the width of maze(minmum 20):";
	cin >> width;
	while (width < 20) {
		cout << "*You need more than 20:";
		cin >> width;
		if (width >= 20) {
			break;
		}
	}
	cout << "Enter the length of maze(minmum 20):";
	cin >> length;
	while (length < 20) {
		cout << "*You need more than 20:";
		cin >> length;
		if (length >= 20) {
			break;
		}
	}
	cout << "Enter the entrance(s) of the maze(minmum 2, maximum 4):";
	cin >> exitNum;
	while (exitNum < 2) {
		cout << "*You need more than 2:";
		cin >> exitNum;
		if (exitNum >= 2) {
			break;
		}
	}
	while (exitNum > 4) {
		cout << "*You need less than 4:";
		cin >> exitNum;
		if (exitNum <= 4) {
			break;
		}
	}

	system("cls");
	cout << "Generating a " << width << "*" << length << " maze, with " << exitNum << " exit(s)..." << endl;
	maze.createArray(width, length);
	maze.assignArray();
	maze.generater(exitNum);
	maze.printArray();
	
	cout << endl << endl << "Do you want to find the path?(y/n)";
	cin >> anP;
	while (1) {
		if (anP == 'y') {
			system("cls");
			findpath();
			break;
		}
		else if (anP == 'n') {
			break;
		}
		else {
			cout << "You must enter y/n.";
			cin >> anP;
		}
	}
	cout << endl << "Do you want to save the maze?(y/n)";
	cin >> anS;
	while (1) {
		if (anS == 'y') {
			saveFile();
			break;
		}
		else if (anS == 'n') {
			cout << "Do you want to generate another one?(y/n)";
			cin >> anR;
			while (1) {
				if (anR == 'y') {
					system("cls");
					generate();
					break;
				}
				else if (anS == 'n') {
					cout << "Have fun!";
					break;
				}
				else {
					cout << "You must enter y/n.";
					cin >> anR;
				}
			}
			break;
		}
		else {
			cout << "You must enter y/n.";
			cin >> anS;
		}
		break;
	}
}

void loadFile() {
	ifstream infile;
	string filePath;
	cout << "Please enter the path of the file:";
	cin >> filePath;

	infile.open(filePath);
	string loadmaze;

	while (!infile) {
		cout << "There is no file." << endl;
		cout << "Please re-enter the path of the file:";
		cin >> filePath;
		infile.open(filePath);
		if (infile) {
			break;
		}
	}
	while (getline(infile, loadmaze)) {
		cout << loadmaze.c_str() << endl;
	}
}

void mainMenu() {
	int choose;
	cout << "Welcome to use the MAZE program." << endl;
	//Sleep(3000);
	cout << endl << "What do you want to do?" << endl;
	cout << "1.Create a new maze." << endl;
	cout << "2.Load a existed maze." << endl << endl;
	cout << "*Please type the number:";
	cin >> choose;

	system("cls");

	switch (choose) {
	case 1:
		generate(); break;
	case 2:
		loadFile(); break;
	}
}

int main() {
	mainMenu();
}


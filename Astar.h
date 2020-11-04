#pragma once
#ifndef ASTAR_H
#define ASTAR_H

#include <vector>
#include <list>
using namespace std;

const int cost = 10;

struct PathPoint
{
	int x, y;
	int F, G, H;
	PathPoint* parent;
	PathPoint(int _x, int _y) {
		x = _x;
		y = _y;
		F = 0;
		G = 0;
		H = 0;
		parent = NULL;
	}
};

class Astar {
private:
	char** calmaze;
	int width, length;
	list<PathPoint*> openlist;
	list<PathPoint*> closelist;

	PathPoint* findPath(PathPoint& startPoint, PathPoint& endPoint);
	vector<PathPoint*> getSurroundPoints(const PathPoint* point);
	bool canreach(const PathPoint* point, const PathPoint* target);
	PathPoint* isinlist(const list<PathPoint*>& list, const PathPoint* point);
	PathPoint* getf();

	int calF(PathPoint* point);//F=G+H
	int calG(PathPoint* tempstart, PathPoint* point);//to specific point
	int calH(PathPoint* point, PathPoint* end);//to end point

public:
	vector<PathPoint> entrances;
	void initAstar(char** maze, int w, int l);
	list<PathPoint*> getPath(PathPoint& startPoint, PathPoint& endPoint);
};

#endif // !ASTAR_H

#include "Astar.h"
#include <math.h>

void Astar::initAstar(char** maze, int w, int l) {
	calmaze = maze;
	width = w;
	length = l;
}

int Astar::calG(PathPoint* tempstart, PathPoint* point) {
	int parentG = point->parent == NULL ? 0 : tempstart->G;
	return parentG + cost;
}

int Astar::calH(PathPoint* point, PathPoint* end) {
	int length = sqrt((double)(end->x - point->x) * (double)(end->x - point->x)
		+ (double)(end->y - point->y) * (double)(end->y - point->y)) * cost;
	return length;
}

int Astar::calF(PathPoint* point) {
	return point->G + point->H;
}

PathPoint* Astar::getf() {
	if (!openlist.empty()) {
		auto resPoint = openlist.front();
		for (auto& point : openlist) {
			if (point->F < resPoint->F) {
				resPoint = point;
			}
		}
		return resPoint;
	}
	return NULL;
}

PathPoint* Astar::findPath(PathPoint& startPoint, PathPoint& endPoint) {
	openlist.push_back(new PathPoint(startPoint.x, startPoint.y));
	while (!openlist.empty()) {
		auto curPoint = getf();//find the minmum f point
		openlist.remove(curPoint);//remove that point from openlist
		closelist.push_back(curPoint);//add that point to closelist

		//find a way through
		auto surround = getSurroundPoints(curPoint);
		for (auto& target : surround) {
			if (!isinlist(openlist, target)) {
				//if a point is not in openlist
				//add it to openlist
				//parent is current point
				target->parent = curPoint;

				target->G = calG(curPoint, target);
				target->H = calH(target, &endPoint);
				target->F = calF(target);

				openlist.push_back(target);
			}
			else {
				//if a point is in openlist
				//calculate the G
				//if smaller, parent is current point
				int tempG = calG(curPoint, target);
				if (tempG < target->G) {
					target->parent = curPoint;
					target->G = tempG;
					target->F = calF(target);
				}
			}
			PathPoint* resPoint = isinlist(openlist, &endPoint);
			if (resPoint) {
				return resPoint;
			}
		}
	}
}

list<PathPoint*> Astar::getPath(PathPoint& startPoint, PathPoint& endPoint) {
	PathPoint* result = findPath(startPoint, endPoint);
	list<PathPoint*> path;
	while (result) {
		path.push_front(result);
		result = result->parent;
	}

	openlist.clear();
	closelist.clear();

	return path;
}

PathPoint* Astar::isinlist(const list<PathPoint*>& list, const PathPoint* point) {
	for (auto i : list) {
		if (i->x == point->x && i->y == point->y) {
			return i;
		}
	}
	return NULL;
}

bool Astar::canreach(const PathPoint* point, const PathPoint* target) {
	if (target->x<0 || target->x>width - 1
		|| target->y<0 || target->y>length - 1
		|| calmaze[target->x][target->y] == 'X'
		|| (target->x == point->x && target->y == point->y)
		|| isinlist(closelist, target)) {
		return false;
	}
	else {
		if (abs(point->x - target->x) + abs(point->y - target->y) == 1) {
			return true;
		}
		else if (abs(point->x - target->x) + abs(point->y - target->y) == 2) {
			return false;
		}
	}
}

vector<PathPoint*> Astar::getSurroundPoints(const PathPoint* point) {
	vector<PathPoint*> surrPoints;
	for (int x = point->x - 1; x <= point->x + 1; x++) {
		for (int y = point->y - 1; y <= point->y + 1; y++) {
			if (canreach(point, new PathPoint(x, y))) {
				surrPoints.push_back(new PathPoint(x, y));
			}
		}
	}
	return surrPoints;
}
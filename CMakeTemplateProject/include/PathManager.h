#ifndef PathManager_H
#define PathManager_H

#include <vector>
#include <iostream>
#include "Map.h"

struct Boundary {
	int xUpper = 0;
	int xLower = 0;
	int yUpper = 0;
	int yLower = 0;
};

class PathManager
{
private:
	std::vector<Coordinate> generateListOfPaths(Map *map, Position startPosition, Position endPosition);
	std::vector<Coordinate> generatePath(std::vector<Coordinate> &pathList, Position &start);
public:
	PathManager();
	~PathManager();

	std::vector<Coordinate> createPath(Position startPosition, Position dropOff, Map &map);
	std::vector<Coordinate> editPath(std::vector<Coordinate> path);
	void deletePath(std::vector <Coordinate> path);
};

#endif

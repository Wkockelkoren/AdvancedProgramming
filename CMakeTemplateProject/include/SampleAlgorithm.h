#ifndef SAMPLEALGORITHM_H
#define SAMPLEALGORITHM_H

#include <vector>
#include <iostream>
#include "Map.h"
#include "Structures.h"

struct Coordinate {
	size_t x = 0;
	size_t y = 0;
	size_t counter = 0;
};

class SampleAlgorithm {
private:
	bool startPointReached = false;
	size_t highestCounter = 0;
	bool coordinateAdded = false;
	bool existsAlready = false;

	std::vector<Coordinate> calculateListOfPaths(Map &map, Position startPosition, Position endPosition);

	std::vector<Position> getSinglePath(std::vector<Coordinate> &pathList, Position start);

	void addNewCoordinate(Map &map, const Coordinate newCoordinate, const Position endPosition, const size_t &iterator,
		std::vector<Coordinate> &pathList);

public:
	std::vector<Position> createPath(const Position startPosition, const Position goalPosition, Map &map);

};

#endif
#ifndef SAMPLEALGORITHM_H
#define SAMPLEALGORITHM_H

#include <vector>
#include <iostream>
#include "Map.h"
#include "Structures.h"
/**
Position struct with added counter
*/
struct Coordinate {
	size_t x = 0;
	size_t y = 0;
	size_t counter = 0;
};


/**
Class for the path finding algorithm
*/
class SampleAlgorithm {
private:
	bool startPointReached = false;
	size_t highestCounter = 0;
	bool coordinateAdded = false;
	bool existsAlready = false;

	/**This function generates a vector of coordinates. It starts with the start coordinate and
	then it checks every coordinate adjacent to the start coordinate. If the coordinate is no
	obstacle and within boundaries it adds the coordinate to a list. Next, this action also happens
	with every new coordinate in the list untill the end position is found.
	*/
	std::vector<Coordinate> calculateListOfPaths(Map &map, Position startPosition, Position endPosition);

	/** This function returns a generated path from the output of the calculateListOfPahts function.
	The output of the calcaluteListOfPaths is a vector that contains the actual path and
	a set of unfinished path that don't lead to the right direction. This function searches
	for the actual path and returns that.
	*/
	std::vector<Position> getSinglePath(std::vector<Coordinate> &pathList, Position start);

	/**this function checks if the requested coordinate is the start coordinate or if there is an obstacle at the requested position.
	If both is not the case the coordinate gets added to the argument pathlist
	*/
	void addNewCoordinate(Map &map, const Coordinate newCoordinate, const Position endPosition, const size_t &iterator,
		std::vector<Coordinate> &pathList);

public:
	/**
	this public function can be called in order to generate a path.
	*/
	std::vector<Position> createPath(const Position startPosition, const Position goalPosition, Map &map);

};

#endif
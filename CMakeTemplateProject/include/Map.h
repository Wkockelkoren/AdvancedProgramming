#ifndef MAP_H
#define MAP_H

#include "PointOfInterest.h"

class Map {
private:
	//std::vector<Vehicle> vehicleList;
	PointOfInterest *map;

public:
	const int width;
	const int height;

	Map(int width, int height);// : width(width), height(height);

	~Map();

	PointOfInterest& getPointOfInterest(int x, int y);

	void printMap();
	
};

#endif
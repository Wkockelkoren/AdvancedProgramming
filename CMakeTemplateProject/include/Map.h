#ifndef MAP_H
#define MAP_H

#include "PointOfInterest.h"
#include "Vehicle.h"

struct Coordinate {
	int x = 0;
	int y = 0;
	int counter = 0;
};

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

	void printMap(std::vector<Vehicle> vehicles, std::vector<Coordinate> path);
	void printMap();
	
};

#endif
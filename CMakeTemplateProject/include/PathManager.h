#ifndef PathManager_H
#define PathManager_H

#include <vector>
#include <iostream>
#include "Map.h"
#include "Vehicle.h"


class PathManager{
	/*
	The path manager is responsible for creating paths vehicles can use for navigation.
	*/
private:
	std::vector<Vehicle> listOfVehicles;
	int numberOfVehicles;

	std::vector<Coordinate> generateListOfPaths(Map *map, Position startPosition, Position endPosition);

	std::vector<Coordinate> generatePath(std::vector<Coordinate> &pathList, Position start);

	void PathManager::addNewCoordinate(Map *map, const Coordinate newCoordinate, const Position endPosition, const int &iterator,
	std::vector<Coordinate> &pathList, bool &startPointReached, bool &coordinateAdded, bool &existsAlready);


public:
	PathManager();

	~PathManager();
	void addVehicle(const int xPosition, const int yPosition, const double vehicleSpeed);

	std::vector<Coordinate> createPath(const Position startPosition,const Position dropOff, Map &map);

	std::vector<Coordinate> editPath(std::vector<Coordinate> path);

	void deletePath(std::vector <Coordinate> path);
};

#endif

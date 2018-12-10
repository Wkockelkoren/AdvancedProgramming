#ifndef PathManager_H
#define PathManager_H

#include <vector>
#include <iostream>
#include "Map.h"
#include "Vehicle.h"
#include "Structures.h"

struct Coordinate {
	int x = 0;
	int y = 0;
	int counter = 0;
};

class PathManager{
	/*
	The path manager is responsible for creating paths vehicles can use for navigation.
	*/
private:
	std::vector<Vehicle> listOfVehicles;
	std::vector<Task> listOfTasks;
	std::vector<Position> listOfPaths;
	int numberOfVehicles;
	int numberOfTasks;

	std::vector<Coordinate> generateListOfPaths(Map *map, Position startPosition, Position endPosition);

	std::vector<Position> generatePath(std::vector<Coordinate> &pathList, Position start);

	void PathManager::addNewCoordinate(Map *map, const Coordinate newCoordinate, const Position endPosition, const int &iterator,
	std::vector<Coordinate> &pathList, bool &startPointReached, bool &coordinateAdded, bool &existsAlready);

	void PathManager::setTasks(Task newTask);


public:
	PathManager();

	~PathManager();

	void addVehicle(const int xPosition, const int yPosition, const double vehicleSpeed);

	std::vector<Position> createPath(const Position startPosition,const Position dropOff, Map &map);

	std::vector<Position> editPath(std::vector<Coordinate> path);

	void deletePath(std::vector <Coordinate> path);

	Vehicle getAvailableVehicle();

};

#endif

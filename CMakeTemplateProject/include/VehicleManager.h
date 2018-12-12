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

class VehicleManager{
	/*
	The path manager is responsible for creating paths vehicles can use for navigation.
	*/
private:
	std::vector<Vehicle> listOfVehicles;
	std::vector<Task> listOfTasks;
	std::vector<Position> listOfPaths;
	int numberOfTasks = 0;

	std::vector<Coordinate> calculateListOfPaths(Map &map, Position startPosition, Position endPosition);

	std::vector<Position> getSinglePath(std::vector<Coordinate> &pathList, Position start);

	void addNewCoordinate(Map &map, const Coordinate newCoordinate, const Position endPosition, const int &iterator,
		std::vector<Coordinate> &pathList, bool &startPointReached, bool &coordinateAdded, bool &existsAlready);

	void setTasks(Task newTask);

	int countAvailableVehicles();


public:
	VehicleManager();

	~VehicleManager();

	void addVehicle(const int xPosition, const int yPosition, const double vehicleSpeed);

	void assignPathToVehicle( std::vector<Task> &currentTasks, Map &map);

	Vehicle getAvailableVehicle();

	std::vector<Vehicle>& getVehicles();

	std::vector<Position> createPath(const Position startPosition, const Position dropOff, Map &map);
};

#endif

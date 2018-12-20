#ifndef PathManager_H
#define PathManager_H

#include <vector>
#include <iostream>
#include "Map.h"
#include "Vehicle.h"
#include "Structures.h"

struct Coordinate {
	size_t x = 0;
	size_t y = 0;
	size_t counter = 0;
};

class VehicleManager{
	/*
	The path manager is responsible for creating paths vehicles can use for navigation.
	*/
private:
	std::vector<Vehicle> listOfVehicles;
	std::vector<Task> listOfTasks;
	size_t numberOfTasks = 0;

	std::vector<Coordinate> calculateListOfPaths(Map &map, Position startPosition, Position endPosition);

	std::vector<Position> getSinglePath(std::vector<Coordinate> &pathList, Position start);
	//std::shared_ptr<std::vector<Position>> VehicleManager::getSinglePath(std::vector<Coordinate> &pathList, Position start);

	void addNewCoordinate(Map &map, const Coordinate newCoordinate, const Position endPosition, const size_t &iterator,
		std::vector<Coordinate> &pathList, bool &startPointReached, bool &coordinateAdded, bool &existsAlready);

	void setTasks(Task newTask);

	size_t countAvailableVehicles();


public:
	VehicleManager();

	~VehicleManager();

	void addVehicle(const size_t xPosition, const size_t yPosition, const size_t vehicleSpeed);

	void assignPathToVehicle( std::vector<Task> &currentTasks, Map &map);

	Vehicle& getAvailableVehicle();

	std::vector<Vehicle>& getVehicles();

	std::vector<Position> createPath(const Position startPosition, const Position dropOff, Map &map);
	//std::shared_ptr<std::vector<Position>> createPath(const Position startPosition, const Position dropOff, Map &map);

};

#endif

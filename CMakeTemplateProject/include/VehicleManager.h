#ifndef PathManager_H
#define PathManager_H

#include <vector>
#include <iostream>
#include "Map.h"
#include "SampleAlgorithm.h"
#include "Structures.h"

/**
Generates paths and assigns it to a vehicle when the Go button is pressed.
*/
class VehicleManager{
private:
	std::vector<Vehicle> listOfVehicles;
	AlgorithmChoice currentAlgorithm;
	SampleAlgorithm sampleAlgorithm;

public:
	VehicleManager();

	~VehicleManager();

	/**
	This function can be used to add a vehicle.
	*/
	void addVehicle(Position pos);

	/**
	This function deletes a vehicle by iterator
	*/
	void deleteVehicle(size_t iterator);

	/**
	This public function can be called in order to generate a path for a specific vehicle.
	*/
	void assignPathToVehicle(std::vector<Task> &currentTasks, Map &map);

	/**
	This function choses from the available pathfinding algorithems the desired one and returns the path from the starting position to the goal position.
	*/
	std::vector<Position> getPathFromAlgorithm(Position startPosition, Position goalPosition, Map &map);

	/**
	This function returns a list of the vehicles that are created.
	*/
	std::vector<Vehicle>& getVehicles();

	/**
	This function changes the algorithem that is selected to be used.
	*/
	void setAlgorithm(AlgorithmChoice algorithmChoice);

	/**
	This function returns the number of vehicles
	*/
	size_t countVehicles();

	/**
	This function returns whether all the vehicles are at their goal position
	*/
	bool allVehiclesAtGoalPosition();

	/**
	This function prints a list of all the vehicles with their coordinates
	*/
	void printVehicles();
};

#endif

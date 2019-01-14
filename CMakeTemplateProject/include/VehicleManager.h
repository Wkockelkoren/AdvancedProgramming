#ifndef PathManager_H
#define PathManager_H

#include <vector>
#include <iostream>
#include "Map.h"
#include "SampleAlgorithm.h"
#include "Structures.h"

class VehicleManager{
	/*
	The path manager is responsible for creating paths vehicles can use for navigation.
	*/
private:
	std::vector<Vehicle> listOfVehicles;
	AlgorithmChoice currentAlgorithm;
	SampleAlgorithm sampleAlgorithm;

public:
	VehicleManager();

	~VehicleManager();

	void addVehicle(Position pos);

	void deleteVehicle(size_t iterator);

	void assignPathToVehicle(std::vector<Task> &currentTasks, Map &map);

	std::vector<Position> getPathFromAlgorithm(Position startPosition, Position goalPosition, Map &map);

	std::vector<Vehicle>& getVehicles();

	void setAlgorithm(AlgorithmChoice algorithmChoice);

	size_t countVehicles();

	bool allVehiclesAtGoalPosition();

	void printVehicles();
};

#endif

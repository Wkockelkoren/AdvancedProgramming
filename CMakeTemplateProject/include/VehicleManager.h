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

	void addVehicle(Position pos, const size_t vehicleSpeed);

//TODO: add new vehicle object to assignPathToVehicle
	void assignPathToVehicle(std::vector<Task> &currentTasks, Map &map);

	Vehicle& getAvailableVehicle();

	std::vector<Position> getPathFromAlgorithm(Position startPosition, Position goalPosition, Map &map);

	std::vector<Vehicle>& getVehicles();

	void setAlgorithm(AlgorithmChoice algorithmChoice);

	size_t countVehicles();

	size_t countAvailableVehicles();

	bool allVehiclesAtGoalPosition();
};

#endif

#include "VehicleManager.h"
/**
Generates paths and assigns it to a vehicle when the Go button is pressed.
*/

VehicleManager::VehicleManager(){
	currentAlgorithm = enumSampleAlgorithm;
}

VehicleManager::~VehicleManager(){
}

void VehicleManager::addVehicle(Position pos) {
	/** 
	This function can be used to add a vehicle.
	*/
	Vehicle vehicle(pos);
	listOfVehicles.push_back(vehicle);
}

void VehicleManager::deleteVehicle(size_t iterator) {
	/**
	This function deletes a vehicle by iterator
	*/
	if (iterator < listOfVehicles.size()) {
		listOfVehicles.erase(listOfVehicles.begin() + iterator);
	}
}

std::vector<Position> VehicleManager::getPathFromAlgorithm(Position startPosition, Position goalPosition, Map &map) {
	switch (currentAlgorithm) {
	case enumAstar:
		std::cout << "A* has not yet been implemented." <<
			std::endl << "Sample Algorithm will be chosen. " << std::endl;
		return sampleAlgorithm.createPath(startPosition, goalPosition, map);
		break;

	default:
		return sampleAlgorithm.createPath(startPosition, goalPosition, map);
		break;
	}
}

void VehicleManager::assignPathToVehicle(std::vector<Task> &currentTasks, Map &map) {
	/**
	this public function can be called in order to generate a path for a specific vehicle.

	*/
	/*
	this public function can be called in order to generate a path. it uses the private function
	"ListOfPaths" to generate a vector with 1 path from start to end, and with paths that dont lead
	to the right location. The function generatePath uses this list and returns only the correct path
	*/

	for (size_t currentVehicle = 0; currentVehicle < listOfVehicles.size(); currentVehicle++) {
		if (listOfVehicles[currentVehicle].checkIfWorking() == true) {
			continue;
		}
		if (currentTasks.size() > 0 || !allVehiclesAtGoalPosition()) {
			std::vector<Position> generatedPath;

			if (listOfVehicles[currentVehicle].isAtTaskGoalPosition()) {
				//get new task en create path to start position
				if (currentTasks.size() == 0) {
					continue;
				}
				listOfVehicles[currentVehicle].setTask(currentTasks.front());

				if (listOfVehicles[currentVehicle].hasStartPosition()) {
					generatedPath = getPathFromAlgorithm(listOfVehicles[currentVehicle].getPosition(), currentTasks.front().startPosition, map);
				}
				else {
					generatedPath = getPathFromAlgorithm(listOfVehicles[currentVehicle].getPosition(), currentTasks.front().goalPosition, map);
					std::cout << "has no start position\n";
				}
				currentTasks.erase(currentTasks.begin());
			}
			else if (listOfVehicles[currentVehicle].isAtTaskStartPosition() || !listOfVehicles[currentVehicle].hasStartPosition()) {
				//move to goal position of current task
				generatedPath = getPathFromAlgorithm(listOfVehicles[currentVehicle].getPosition(), listOfVehicles[currentVehicle].getTask()->goalPosition, map);
			}
			else {
				//move to start position of current task
				generatedPath = getPathFromAlgorithm(listOfVehicles[currentVehicle].getPosition(), listOfVehicles[currentVehicle].getTask()->startPosition, map);
			}

			listOfVehicles[currentVehicle].setPath(generatedPath);
		}
	}
}

size_t VehicleManager::countVehicles() {
	/** This function returns the number of vehicles
	*/
	size_t numberOfVehicles = 0;
	for (size_t currentVehicle = 0; currentVehicle < listOfVehicles.size(); currentVehicle++) {
		numberOfVehicles++;
	}
	return numberOfVehicles;
}

std::vector<Vehicle>& VehicleManager::getVehicles() {
	return listOfVehicles;
}

void VehicleManager::setAlgorithm(AlgorithmChoice algorithmChoice) {
	currentAlgorithm = algorithmChoice;
}

bool VehicleManager::allVehiclesAtGoalPosition() {
	for (Vehicle vehicle : listOfVehicles) {
		if (!vehicle.isAtTaskGoalPosition()) {
			return false;
		}
	}
	return true;
}

void VehicleManager::printVehicles() {
	std::cout << "List of Vehicles:\n";
	size_t counter = 0;
	for (Vehicle vehicle : listOfVehicles) {
		std::cout << "Vehicle " << counter << " on position (" << vehicle.getPosition().x << "," << vehicle.getPosition().y << ")\n";
		counter++;
	}
}
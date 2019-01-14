#include "VehicleManager.h"

VehicleManager::VehicleManager(){
	currentAlgorithm = enumSampleAlgorithm;
}

VehicleManager::~VehicleManager(){
}

void VehicleManager::addVehicle(Position pos) {
	Vehicle vehicle(pos);
	listOfVehicles.push_back(vehicle);
}

void VehicleManager::deleteVehicle(size_t iterator) {
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
	for (size_t currentVehicle = 0; currentVehicle < listOfVehicles.size(); currentVehicle++) {
		if (listOfVehicles[currentVehicle].getWorking() == true) {
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
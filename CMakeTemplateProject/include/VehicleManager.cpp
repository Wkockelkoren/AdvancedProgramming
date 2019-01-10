#include "VehicleManager.h"
/**
Generates paths and assigns it to a vehicle when the Go button is pressed.
*/

VehicleManager::VehicleManager(){

}


VehicleManager::~VehicleManager(){
}


void VehicleManager::addVehicle(Position pos, const size_t vehicleSpeed) {
	/** This function can be used to add a vehicle.
	*/
	Vehicle vehicle(pos, vehicleSpeed);
	listOfVehicles.push_back(vehicle);
}

Vehicle& VehicleManager::getAvailableVehicle() {
	/** This function searches for a vehicle that is not working and returns it
	*/
	size_t numberOfVehicles = listOfVehicles.size();

	//check how many vehicles are available
	for (size_t currentVehicle = 0; currentVehicle < numberOfVehicles; currentVehicle++) {
		if (listOfVehicles[currentVehicle].checkIfWorking() == false) {
			Vehicle& availableVehicle = listOfVehicles[currentVehicle];
			return availableVehicle;
		}
	}
	//return should have an been triggered in the for loop. Otherwise the countAvailableVehicles was not used before.
	throw std::runtime_error("No available vehicle to return - class VehicleManager GetAvailableVehicle()\n");
}


size_t VehicleManager::countAvailableVehicles() {
	/** This function returns the number of vehicles that are not working
	*/
	size_t numberOfAvailableVehicles = 0;
	for (size_t currentVehicle = 0; currentVehicle < listOfVehicles.size(); currentVehicle++) {
		if (listOfVehicles[currentVehicle].checkIfWorking() == false) {
			numberOfAvailableVehicles++;
		}
	}
	return numberOfAvailableVehicles;
}


void VehicleManager::assignPathToVehicle( std::vector<Task> &currentTasks, Map &map) {
	/**
	this public function can be called in order to generate a path for a specific vehicle.

	*/
	/*
	this public function can be called in order to generate a path. it uses the private function
	"ListOfPaths" to generate a vector with 1 path from start to end, and with paths that dont lead
	to the right location. The function generatePath uses this list and returns only the correct path
	*/

	size_t numberOfAvailableVehicles = countAvailableVehicles();

	while (numberOfAvailableVehicles > 0 && currentTasks.size() > 0) {
		Vehicle availableVehicle;
		try {
			availableVehicle = getAvailableVehicle(); //first a vehicle that is not doing work is needed
		}
		catch (std::exception const& e) {
			std::cout << e.what();
		}

		std::vector<Position> generatedPath;

		if (availableVehicle.isAtTaskGoalPosition()) {
			//get new task en create path to start position
			getAvailableVehicle().setTask(currentTasks.front());

			if (getAvailableVehicle().hasStartPosition()) {
				generatedPath = sampleAlgorithm.createPath(availableVehicle.getPosition(), currentTasks.front().startPosition, map);
			}
			else{
				generatedPath = sampleAlgorithm.createPath(availableVehicle.getPosition(), currentTasks.front().goalPosition, map);
				std::cout << "has no start position\n";
			}
			currentTasks.erase(currentTasks.begin());
		}
		else if (availableVehicle.isAtTaskStartPosition()) {
			//move to goal position of current task
			generatedPath = sampleAlgorithm.createPath(availableVehicle.getPosition(), availableVehicle.getTask()->goalPosition, map);
		}
		else {
			//move to start position of current task
			generatedPath = sampleAlgorithm.createPath(availableVehicle.getPosition(), availableVehicle.getTask()->startPosition, map);
		}

		getAvailableVehicle().setPath(generatedPath);

		numberOfAvailableVehicles--;
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

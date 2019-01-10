#include "Vehicle.h"

/**
* Has a position on the Map, a maximum speed and contains a path that was generated 
* by the VehicleManager. A Path consists out of multiple Positions (vector of Positions)
* where the first element in the vector will be the start position and the last element 
* the end position. In the Editor view it is possible to add and edit multiple vehicles
* with each a different start and end position. Furthermore, it is possible to assign a
* maximum speed to a specific vehicle.
* @endcode
*/

Vehicle::Vehicle(Position pos, size_t maxSpeed) : position(pos), maxSpeed(maxSpeed) {
	task.startPosition = { NULL, NULL };
	task.goalPosition = { NULL, NULL };
}


void Vehicle::printCoords() {
	std::cout << "(" << position.x << "," << position.y << ")\n";
}


void Vehicle::setPosition(Position pos) {
	position = pos;
}


Position Vehicle::getPosition() {
	return position;
}


void Vehicle::printMaxSpeed() {
	std::cout << maxSpeed<< "\n";
}


void Vehicle::setMaxSpeed(size_t maxSpeed1) {
	maxSpeed = maxSpeed1;
}


size_t Vehicle::getMaxSpeed() {
	return maxSpeed;
}


bool Vehicle::checkIfWorking() {
	return working;
}


bool Vehicle::moveNextPathPosition() {
	/**
	A vehicle uses this function to change its position by usage of an assigned path
	*/
	if (!path.empty()) {
		if (path.at(0).x == position.x && path.at(0).y == position.y) { // Check if the vehicle is on the expected position
			if (path.size() > 2) { // Check if there is a next position to move to
				position.x = path.at(1).x; // move to the next position
				position.y = path.at(1).y;
				working = true;
			}
			else if(path.size() == 2) { // Check if there is a next position to move to
				position.x = path.at(1).x; // move to the next position
				position.y = path.at(1).y;
				working = false;
			}
			else if(path.size() == 1){
				working = false;
			}
			path.erase(path.begin());// delete the previous position of the path
		}
		else {
			throw std::runtime_error("Vehicle is not in the expected position of the path given. - class Vehicle moveNextPathPosition()\n");
			//This probably means the start position of the generated path was different than the vehicle position.
		}
	}
	else {
		working = false;
		std::cout << "Path is empty\n";
		return false;
	}
	return true;
}


void Vehicle::setPath(std::vector<Position> &generatedpath) {
	/**
	Pass generated path to vehicle
	*/
	path = generatedpath;
}


std::vector<Position>* Vehicle::getPath() {
	/**
	Returns path assigned to current vehicle
	*/
	return &path;
}


Task* Vehicle::getTask() {
	return &task;
}


void Vehicle::setTask(Task task1) {
	task = task1;
}


bool Vehicle::isAtTaskGoalPosition() {
	//no task assigned
	if (task.goalPosition.x == NULL && task.goalPosition.y == NULL) {
		return true;
	}
	//previous task completed
	if (task.goalPosition.x == position.x && task.goalPosition.y == position.y ) {
		return true;
	}
	return false;
}


bool Vehicle::isAtTaskStartPosition() {
	if (task.startPosition.x == position.x && task.startPosition.y == position.y) {
		return true;
	}
	return false;
}


bool Vehicle::hasStartPosition() {
	if (task.startPosition.x == NULL && task.startPosition.y == NULL) {
		return false;
	}
	return true;
}

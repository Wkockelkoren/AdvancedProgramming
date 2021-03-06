#include "Vehicle.h"

Vehicle::Vehicle(Position pos) : position(pos) {
	task.startPosition = { SIZE_MAX, SIZE_MAX };
	task.goalPosition = { SIZE_MAX, SIZE_MAX };
}

Position Vehicle::getPosition() {
	return position;
}

void Vehicle::setWorking(bool isWorking) {
	working = isWorking;
}

bool Vehicle::getWorking() {
	return working;
}

void Vehicle::moveNextPathPosition() {
	
	if (!path.empty()) {
		if (path.at(0).x == position.x && path.at(0).y == position.y) { // Check if the vehicle is on the expected position
			if (path.size() > 2) { // Check if there is a next position to move to
				position.x = path.at(1).x; // move to the next position
				position.y = path.at(1).y;
				setWorking(true);
			}
			else if(path.size() == 2) { // Check if there is a next position to move to
				position.x = path.at(1).x; // move to the next position
				position.y = path.at(1).y;
				setWorking(false);
			}
			else if(path.size() == 1){
				setWorking(false);
			}
			path.erase(path.begin());// delete the previous position of the path
		}
		else {
			throw std::runtime_error("Vehicle is not in the expected position of the path given. - class Vehicle moveNextPathPosition()\n");
			//This probably means the start position of the generated path was different than the vehicle position.
		}
	}
	else {
		setWorking(false);
		std::cout << "Path is empty\n";
	}
}

void Vehicle::setPath(std::vector<Position> &generatedpath) {
	
	path = generatedpath;
}

std::vector<Position>* Vehicle::getPath() {

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
	if (task.goalPosition.x == SIZE_MAX && task.goalPosition.y == SIZE_MAX) {
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
	if (task.startPosition.x == SIZE_MAX && task.startPosition.y == SIZE_MAX) {
		return false;
	}
	return true;
}

#include <iostream>
#include <vector>
#include "Vehicle.h"
#include "Map.h"

Vehicle::Vehicle(int x, int y, double maxSpeed) : x(x), y(y), maxSpeed(maxSpeed) {}

void Vehicle::printCoords() {
	std::cout << "(" << x << "," << y << ")\n";
}

void Vehicle::setPosition(int x1, int y1) {
	x = x1;
	y = y1;
}

Position Vehicle::getPosition() {
	Position pos;
	pos.x = x;
	pos.y = y;
	return pos;
}

void Vehicle::printMaxSpeed() {
	std::cout << maxSpeed<< "\n";
}

void Vehicle::setMaxSpeed(int maxSpeed1) {
	maxSpeed = maxSpeed1;
}

double Vehicle::getMaxSpeed() {
	return maxSpeed;
}

<<<<<<< HEAD
void Vehicle::moveNextPathPosition() {
=======
bool Vehicle::checkIfWorking() {
	return working;
}
void Vehicle::moveNextPathPosition(std::vector<Position> &path) {
>>>>>>> ft_pathplanning
	if (!path.empty()) {
		if (path.at(0).x == x && path.at(0).y == y) { // Check if the vehicle is on the expected position
			if (path.size() > 1) { // Check if there is a next position to move to
				x = path.at(1).x; // move to the next position
				y = path.at(1).y;
				working = true;
				path.erase(path.begin()); // delete the previous position of the path
			}
			else {
				path.erase(path.begin());
				//TODO: vehicle is in last position of the path and the path list is empty, but the path still exists. 
				//This needs to be fixed. 
			}
		}
		else {
			throw std::runtime_error("Vehicle is not in the expected position of the path given. - class Vehicle moveNextPathPosition()\n");
			//This probably means the start position of the generated path was different than the vehicle position.
		}
	}
	else {
		working = false;
		std::cout << "Path is empty\n";
	}
}

void Vehicle::setPath(std::vector<Position> &generatedpath) {
	path = generatedpath;
}

std::vector<Position>* Vehicle::getPath() {
	return &path;
}
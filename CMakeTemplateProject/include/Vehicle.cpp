#include <iostream>
#include <vector>
#include "Vehicle.h"
#include "Map.h"

/**
* Has a position on the Map, a maximum speed and contains a path that was generated 
* by the VehicleManager. A Path consists out of multiple Positions (vector of Positions)
* where the first element in the vector will be the start position and the last element 
* the end position. In the Editor view it is possible to add and edit multiple vehicles
* with each a different start and end position. Furthermore, it is possible to assign a
* maximum speed to a specific vehicle.
* @endcode
*/
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

bool Vehicle::checkIfWorking() {
	return working;
}

void Vehicle::moveNextPathPosition() {
	/**
	A vehicle uses this function to change its position by usage of an assigned path
	*/
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
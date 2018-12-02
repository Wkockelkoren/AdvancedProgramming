#include <iostream>
#include <vector>
#include "Vehicle.h"

Vehicle::Vehicle(int x, int y, double maxSpeed) : x(x), y(y), maxSpeed(maxSpeed) {

}

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

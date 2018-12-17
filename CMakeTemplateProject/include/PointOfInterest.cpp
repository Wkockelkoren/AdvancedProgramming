#include <iostream>
#include <vector>
#include "PointOfInterest.h"

PointOfInterest::PointOfInterest(int x, int y, pointOfInterestType type, bool obstacle) : x(x), y(y), type(type), isObstacle(obstacle) {
	/**
	Constructor for Point of Interest.
	*/
}

void PointOfInterest::printCoords() {
	/**
	Print position of current Point of Interest.
	*/
	std::cout << "(" << x << "," << y << ")\n";
}

bool PointOfInterest::getIsObstacle() {
	/**
	Check if Point of Interest is an obstacle.
	*/
	return isObstacle;
}

void PointOfInterest::setIsObstacle(bool obstacle) {
	/**
		Set if Point of Interest is an obstacle.
	*/
	isObstacle = obstacle;
}

pointOfInterestType PointOfInterest::getPointOfInterestType() {
	/**

	*/
	return type;
}

void PointOfInterest::setPointOfInterestType(pointOfInterestType pointType) {
	if (pointType == pointOfInterestType::Wall) {
		isObstacle = true;
	}
	else {
		isObstacle = false;
	}

	type = pointType;
}

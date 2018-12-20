#include <iostream>
#include <vector>
#include "PointOfInterest.h"
/**
Each position on the map is a point of interest. The point of interest type
could be: Floor, Wall of DropOff. Floor is the standard point of interest
type when the map is created. Vehicles are only able to drive over point of
interest type Floor and DropOff.
*/
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

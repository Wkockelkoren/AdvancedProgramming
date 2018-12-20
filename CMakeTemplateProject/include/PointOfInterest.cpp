#include <iostream>
#include <vector>
#include "PointOfInterest.h"

PointOfInterest::PointOfInterest(Position position, pointOfInterestType type, bool obstacle) : position(position), type(type), isObstacle(obstacle) {
	/**
	Constructor for Point of Interest.
	*/
}

void PointOfInterest::setPosition(Position pos) {
	position = pos;
}


void PointOfInterest::printCoords() {
	/**
	Print position of current Point of Interest.
	*/
	std::cout << "(" << position.x << "," << position.y << ")\n";
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

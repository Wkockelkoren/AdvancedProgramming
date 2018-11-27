#include <iostream>
#include <vector>
#include "PointOfInterest.h"

PointOfInterest::PointOfInterest(int x1, int y1, pointOfInterestType pointType , bool obstacle ) {
	x = x1;
	y = y1;
	type = pointType;
	isObstacle = obstacle;
}

void PointOfInterest::printCoords() {
	std::cout << "(" << x << "," << y << ")\n";
}

bool PointOfInterest::getIsObstacle() {
	return isObstacle;
}

void PointOfInterest::setIsObstacle(bool obstacle) {
	isObstacle = obstacle;
}

pointOfInterestType PointOfInterest::getPointOfInterestType() {
	return type;
}

void PointOfInterest::setPointOfInterestType(pointOfInterestType pointType) {
	type = pointType;
}

#include <iostream>
#include <vector>
#include "PointOfInterest.h"

PointOfInterest::PointOfInterest(int x, int y, pointOfInterestType type, bool obstacle) : x(x), y(y), type(type), isObstacle(obstacle) {

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

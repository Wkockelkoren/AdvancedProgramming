#include "PointOfInterest.h"

PointOfInterest::PointOfInterest(Position pos, pointOfInterestType type, bool obstacle) : position(pos), type(type), isObstacle(obstacle) {

}

void PointOfInterest::setPosition(Position pos) {
	position = pos;
}

pointOfInterestType PointOfInterest::getPointOfInterestType() {
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

bool PointOfInterest::getIsObstacle() {
	return isObstacle;
}
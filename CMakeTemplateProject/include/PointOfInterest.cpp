#include "PointOfInterest.h"

/**
Each position on the map is a point of interest. The point of interest type
could be: Floor, Wall of DropOff. Floor is the standard point of interest
type when the map is created. Vehicles are only able to drive over point of
interest type Floor and DropOff.
*/
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
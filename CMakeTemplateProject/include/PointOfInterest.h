#ifndef POINTOFINTEREST_H
#define POINTOFINTEREST_H

#include "Structures.h"

enum pointOfInterestType { Floor, Wall, DropOff };

class PointOfInterest {
private:
	bool isObstacle;
	pointOfInterestType type;
	Position position;

public:

	PointOfInterest(Position position = {0,0}, pointOfInterestType pointType = pointOfInterestType::Floor, bool obstacle = false);

	void setPosition(Position pos);

	void printCoords();

	bool getIsObstacle();

	void setIsObstacle(bool obstacle);

	pointOfInterestType getPointOfInterestType();

	void setPointOfInterestType(pointOfInterestType pointType);
};

#endif

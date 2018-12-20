#ifndef POINTOFINTEREST_H
#define POINTOFINTEREST_H

#include "Structures.h"

enum pointOfInterestType { Floor, Wall, DropOff };

class PointOfInterest {
private:

	Position position;
	bool isObstacle;
	pointOfInterestType type;

public:

	PointOfInterest(Position pos = {0,0}, pointOfInterestType pointType = pointOfInterestType::Floor, bool obstacle = false);

	void setPosition(Position pos);

	void printCoords();

	pointOfInterestType getPointOfInterestType();

	void setPointOfInterestType(pointOfInterestType pointType);

	bool getIsObstacle();

	void setIsObstacle(bool obstacle);
};

#endif

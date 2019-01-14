#ifndef POINTOFINTEREST_H
#define POINTOFINTEREST_H

#include <iostream>
#include <vector>
#include "Structures.h"

enum pointOfInterestType { Floor, Wall, DropOff };

/**
* Each position on the map is a point of interest. The point of interest type
* could be: Floor, Wall of DropOff. Floor is the standard point of interest
* type when the map is created. Vehicles are only able to drive over point of
* interest type Floor and DropOff.
*/
class PointOfInterest {
private:

	Position position;
	bool isObstacle;
	pointOfInterestType type;

public:
	/**
		Constructor for Point of Interest.
	*/
	PointOfInterest(Position pos = {0,0}, pointOfInterestType pointType = pointOfInterestType::Floor, bool obstacle = false);

	/**
		Gives PoIs a position, used in creation of the map
	*/
	void setPosition(Position pos);

	/**
		Returns the type of a point of interest
	*/
	pointOfInterestType getPointOfInterestType();

	/**
		Set the type of the point of interest
	*/
	void setPointOfInterestType(pointOfInterestType pointType);

	/**
		Get if the point of interest is an obstacle. If it is an obstacle, the vehicle can not drive here
	*/
	bool getIsObstacle();

};

#endif

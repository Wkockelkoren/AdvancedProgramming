#ifndef POINTOFINTEREST_H
#define POINTOFINTEREST_H

enum pointOfInterestType { Floor, Wall, DropOff };

class PointOfInterest {
private:
	bool isObstacle;
	pointOfInterestType type;

public:
	size_t x;
	size_t y;
	PointOfInterest(size_t x1 = 0, size_t y1 = 0, pointOfInterestType pointType = pointOfInterestType::Floor, bool obstacle = false);

	void printCoords();

	bool getIsObstacle();

	void setIsObstacle(bool obstacle);

	pointOfInterestType getPointOfInterestType();

	void setPointOfInterestType(pointOfInterestType pointType);
};

#endif

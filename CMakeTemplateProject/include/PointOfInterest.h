#ifndef POINTOFINTEREST_H
#define POINTOFINTEREST_H

enum pointOfInterestType { Floor, Wall, DropOff };

class PointOfInterest {
private:
	bool isObstacle;
	pointOfInterestType type;

public:
	int x;
	int y;
	PointOfInterest::PointOfInterest(int x1 = 0, int y1 = 0, pointOfInterestType pointType = pointOfInterestType::Floor, bool obstacle = false);

	void printCoords();

	bool getIsObstacle();

	void setIsObstacle(bool obstacle);

	pointOfInterestType getPointOfInterestType();

	void setPointOfInterestType(pointOfInterestType pointType);
};

#endif
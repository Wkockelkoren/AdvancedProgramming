#ifndef VEHICLE_H
#define VEHICLE_H

struct Position {
	int x = 0;
	int y = 0;
};

class Vehicle {
private:

public:
	int x;
	int y;
	double maxSpeed;
	Vehicle::Vehicle(int x1 = 0, int y1 = 0, double maxSpeed1 = 1);

	void Vehicle::printCoords();

	void Vehicle::setPosition(int x1, int y1);

	Position Vehicle::getPosition();

	void Vehicle::printMaxSpeed();

	void Vehicle::setMaxSpeed(int maxSpeed1);

	double Vehicle::getMaxSpeed();
};

#endif

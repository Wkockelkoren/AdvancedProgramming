#ifndef VEHICLE_H
#define VEHICLE_H

#include "Structures.h"



class Vehicle {
private:

public:
	int x;
	int y;
	double maxSpeed;
	Vehicle(int x1 = 0, int y1 = 0, double maxSpeed1 = 1);
	bool working = false;

	void printCoords();

	void setPosition(int x1, int y1);

	Position getPosition();

	void printMaxSpeed();

	void setMaxSpeed(int maxSpeed1);

	double getMaxSpeed();

	bool checkIfWorking();

	void moveNextPathPosition(std::vector<Position> &path);
};

#endif
